#include "./ApiRetrievalTest.h"

/**
 * @brief This test will attempt to search for a valid summoner but with a bad API key.
 * We should get a 403 error.
 * @return True or False: we got the expected boolean (False)
 */
bool ApiRetrievalTest::test_bad_api_key(){
    // Create a sample valid user.
    QString user_name = "Nindoge";
    QString tagline = "KEKW";

    // Retrieve the summoner data
    SummonerData summoner_data = api_processor.get_summoner_data();

    // Set the username, tagline, and region
    summoner_data.set_summoner_name(user_name);
    summoner_data.set_tagline(tagline);
    summoner_data.set_region("americas");

    // Generate a valid url, but with an invalid api key.
    QString riot_id_url;
    riot_id_url.append("https://");
    riot_id_url.append(summoner_data.get_region());
    riot_id_url.append(".api.riotgames.com/riot/account/v1/accounts/by-riot-id/");
    riot_id_url.append(summoner_data.get_summoner_name());
    riot_id_url.append("/");
    riot_id_url.append(summoner_data.get_tagline());
    riot_id_url.append("?api_key=xdd");                 // this is the bad api key

    // Process the data and ensure that it was a failure
    api_processor.process_api_data(riot_id_url, 7);
    //QCOMPARE(true, api_processor.get_summoner_lookup_status());
    return !api_processor.get_summoner_lookup_status();

}

/**
 * @brief This test will attempt to search for a valid summoner with the correct API key.
 * So long as the API key is correct, this should return true.
 * @return True or False: we got the expected boolean (True)
 */
bool ApiRetrievalTest::test_good_api_key(){
    // Create a sample valid user.
    QString user_name = "Nindoge";
    QString tagline = "KEKW";

    // Retrieve the summoner data
    SummonerData summoner_data = api_processor.get_summoner_data();

    // Set the username, tagline, and region
    summoner_data.set_summoner_name(user_name);
    summoner_data.set_tagline(tagline);
    summoner_data.set_region("americas");             // this is the bad api key

    // Process the data and ensure that it was a pass
    api_processor.process_api_data(summoner_data.generate_riot_id_url(), 7);
    //QCOMPARE(true, api_processor.get_summoner_lookup_status());
    return !api_processor.get_summoner_lookup_status();
}

//QTEST_MAIN(ApiRetrievalTest)
