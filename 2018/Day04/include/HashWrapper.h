using Guard_sleep_map = std::unordered_map<int, std::unique_ptr<Guard>>;

auto retrieve_guard(int key, Guard_sleep_map& gsm)
    // The Chandler Carruth unordered_map access pattern!
{
    auto& pg = gsm[key];
    if (pg)
        return pg.get();
    pg = std::make_unique<Guard>(key);
    return pg.get();
}

void calc_sleep_totals(const Guard_sleep_map& gsm)
{
    for (auto& g : gsm)
        g.second->calc_total_sleep();
}

void map_all_mins(const Guard_sleep_map& gsm)
{
    std::for_each(std::begin(gsm), std::end(gsm),
            [](auto& gp) { gp.second->map_minutes(); });
}

void set_all_sleepy_mins(const Guard_sleep_map& gsm)
{
    std::for_each(std::begin(gsm), std::end(gsm),
            [](auto& gp) { gp.second->set_sleepy_min(); });
}

auto map_sleep_data(const std::vector<std::string>& vs)
    // This is why I want to refactor Guard_sleep_map into its own class. This
    // function is more like a factory/builder function than whatever it is
    // right now.
{
    Guard_sleep_map gsm;

    static const std::regex id_pat {R"(Guard\s#(\d+))"};
    static const std::regex ts_pat {R"(:(\d{2}))"};
    std::smatch matches;
    
    for (auto it = std::begin(vs); it != std::end(vs); ) {
        int id, sleep, wake;
        std::regex_search(*it, matches, id_pat);
        id = std::stoi(matches[1]);
        auto pg = retrieve_guard(id, gsm);

        ++it;
        while (it != std::end(vs) && !std::regex_search(*it, matches, id_pat)) {
            std::regex_search(*it++, matches, ts_pat);
            sleep = std::stoi(matches[1]);
            std::regex_search(*it++, matches, ts_pat);
            wake = std::stoi(matches[1]);
            pg->add_sleep_record(sleep, wake);
        }
    }
    calc_sleep_totals(gsm);
    map_all_mins(gsm);
    set_all_sleepy_mins(gsm);
    return gsm;
}