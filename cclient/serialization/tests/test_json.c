/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdlib.h>
#include <string.h>
#include <unity/unity.h>

#include "serializer/json/json_serializer.h"

void test_serialize_find_transactions(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text =
      "{\"command\":\"findTransactions\",\"addresses\":["
      "\"RVORZ9SIIP9RCYMREUIXXVPQIPHVCNPQ9HZWYKFWYWZRE9JQKG9REPKIASHUUECPSQO9JT"
      "9XNMVKWYGVAZETAIRPTM\"],\"approvees\":["
      "\"LCIKYSBE9IHXLIKCEJTTIQOTTAWSQCCQQ9A9VOKIWRBWVPXMCGUENWVVMQAMPEIVHEQ9JX"
      "LCNZOORVZTZ\"],\"bundles\":["
      "\"VUDHGOXOYEVRPUHAWOUEPHUXVTTUTDUJFFJNBFGWISXQSNRVBUHKETTMEPBXYXEPJAVVX9"
      "LKUSJNAECEW\"],\"tags\":[\"MINEIOTADOTCOM9999999999999\"]}";

  find_transactions_req_t* find_tran = find_transactions_req_new();
  char_buffer_t* serializer_out = char_buffer_new();

  find_transactions_req_add_tag(find_tran, "MINEIOTADOTCOM9999999999999");
  find_transactions_req_add_approvee(
      find_tran,
      "LCIKYSBE9IHXLIKCEJTTIQOTTAWSQCCQQ9A9VOKIWRBWVPXMCGUENWVVMQAMPEIVHEQ9JXLC"
      "NZOORVZTZ");
  find_transactions_req_add_address(
      find_tran,
      "RVORZ9SIIP9RCYMREUIXXVPQIPHVCNPQ9HZWYKFWYWZRE9JQKG9REPKIASHUUECPSQO9JT9X"
      "NMVKWYGVAZETAIRPTM");
  find_transactions_req_add_bundle(find_tran,
                                   "VUDHGOXOYEVRPUHAWOUEPHUXVTTUTDUJFFJNBFGWISX"
                                   "QSNRVBUHKETTMEPBXYXEPJAVVX9LKUSJNAECEW");

  serializer.vtable.find_transactions_serialize_request(&serializer, find_tran,
                                                        serializer_out);

  TEST_ASSERT_EQUAL_STRING(json_text, serializer_out->data);

  char_buffer_free(serializer_out);
  find_transactions_req_free(find_tran);
}

void test_deserialize_find_transactions(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text =
      "{\"hashes\": "
      "[\"ZJVYUGTDRPDYFGFXMKOTV9ZWSGFK9CFPXTITQLQNLPPG9YNAARMKNKYQO9GSCSBIOTGML"
      "JUFLZWSY9999\", "
      "\"9CZ9KJZCDJIKWARATSNPHNWPUM9WHNTCQLZKYQBZIWMXIQXFFKMMHLXIBYXZBALCUVD9X9"
      "NTNVAGNWGUW\", "
      "\"ZJVYUGTDRPDYF9999KOTV9ZWSGFK9CFPXTITQLQNLPPG9YNAARMKNKYQO9GSCSBIOTGMLJ"
      "UFLZWSY9999\"]}";

  find_transactions_res_t* deserialize_find_tran = find_transactions_res_new();

  serializer.vtable.find_transactions_deserialize_response(
      &serializer, json_text, deserialize_find_tran);
  TEST_ASSERT_EQUAL_STRING(
      "ZJVYUGTDRPDYFGFXMKOTV9ZWSGFK9CFPXTITQLQNLPPG9YNAARMKNKYQO9GSCSBIOTGMLJUF"
      "LZWSY9999",
      find_transactions_res_hash_at(deserialize_find_tran, 0));
  TEST_ASSERT_EQUAL_STRING(
      "9CZ9KJZCDJIKWARATSNPHNWPUM9WHNTCQLZKYQBZIWMXIQXFFKMMHLXIBYXZBALCUVD9X9NT"
      "NVAGNWGUW",
      find_transactions_res_hash_at(deserialize_find_tran, 1));
  TEST_ASSERT_EQUAL_STRING(
      NULL, find_transactions_res_hash_at(deserialize_find_tran, 3));
  find_transactions_res_free(deserialize_find_tran);
}

void test_serialize_get_node_info(void) {
  serializer_t serializer;
  const char* json_text = "{\"command\":\"getNodeInfo\"}";

  char_buffer_t* serializer_out = char_buffer_new();
  init_json_serializer(&serializer);

  serializer.vtable.get_node_info_serialize_request(&serializer,
                                                    serializer_out);

  TEST_ASSERT_EQUAL_STRING(json_text, serializer_out->data);

  char_buffer_free(serializer_out);
}

void test_deserialize_get_node_info(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text =
      "{\"appName\":\"IRI\",\"appVersion\":\"1.0.8.nu\",\"duration\":1,"
      "\"jreAvailableProcessors\":4,\"jreFreeMemory\":91707424,"
      "\"jreMaxMemory\":1908932608,\"jreTotalMemory\":122683392,"
      "\"latestMilestone\":"
      "\"VBVEUQYE99LFWHDZRFKTGFHYGDFEAMAEBGUBTTJRFKHCFBRTXFAJQ9XIUEZQCJOQTZNOOH"
      "KUQIKOY9999\",\"latestMilestoneIndex\":107,"
      "\"latestSolidSubtangleMilestone\":"
      "\"VBVEUQYE99LFWHDZRFKTGFHYGDFEAMAEBGUBTTJRFKHCFBRTXFAJQ9XIUEZQCJOQTZNOOH"
      "KUQIKOY9999\",\"latestSolidSubtangleMilestoneIndex\":107,\"neighbors\":"
      "2,\"packetsQueueSize\":0,\"time\":1477037811737,\"tips\":3,"
      "\"transactionsToRequest\":0}";

  get_node_info_res_t* node_info = get_node_info_res_new();

  serializer.vtable.get_node_info_deserialize_response(&serializer, json_text,
                                                       node_info);

  TEST_ASSERT_EQUAL_STRING("IRI", node_info->app_name->data);
  TEST_ASSERT_EQUAL_STRING("1.0.8.nu", node_info->app_version->data);
  TEST_ASSERT_EQUAL_INT(4, node_info->jre_available_processors);
  TEST_ASSERT_EQUAL_INT8(91707424, node_info->jre_free_memory);
  TEST_ASSERT_EQUAL_INT8(1908932608, node_info->jre_max_memory);
  TEST_ASSERT_EQUAL_INT8(122683392, node_info->jre_total_memory);
  TEST_ASSERT_EQUAL_STRING(
      "VBVEUQYE99LFWHDZRFKTGFHYGDFEAMAEBGUBTTJRFKHCFBRTXFAJQ9XIUEZQCJOQTZNOOHKU"
      "QIKOY9999",
      node_info->latest_milestone->data);
  TEST_ASSERT_EQUAL_INT8(107, node_info->latest_milestone_index);
  TEST_ASSERT_EQUAL_STRING(
      "VBVEUQYE99LFWHDZRFKTGFHYGDFEAMAEBGUBTTJRFKHCFBRTXFAJQ9XIUEZQCJOQTZNOOHKU"
      "QIKOY9999",
      node_info->latest_solid_subtangle_milestone->data);
  TEST_ASSERT_EQUAL_INT8(107,
                         node_info->latest_solid_subtangle_milestone_index);
  TEST_ASSERT_EQUAL_INT(2, node_info->neighbors);
  TEST_ASSERT_EQUAL_INT(0, node_info->packets_queue_size);
  TEST_ASSERT_EQUAL_INT8(1477037811737, node_info->time);
  TEST_ASSERT_EQUAL_INT(3, node_info->tips);
  TEST_ASSERT_EQUAL_INT(0, node_info->trans_to_request);

  get_node_info_res_free(node_info);
}

void test_serialize_get_neighbors(void) {
  serializer_t serializer;
  const char* json_text = "{\"command\":\"getNeighbors\"}";

  char_buffer_t* serializer_out = char_buffer_new();
  init_json_serializer(&serializer);

  serializer.vtable.get_neighbors_serialize_request(&serializer,
                                                    serializer_out);

  TEST_ASSERT_EQUAL_STRING(json_text, serializer_out->data);

  char_buffer_free(serializer_out);
}

void test_deserialize_get_neighbors(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text =
      "{\"duration\":37,\"neighbors\":[{\"address\":\"/"
      "8.8.8.8:14265\",\"numberOfAllTransactions\":922,"
      "\"numberOfInvalidTransactions\":0,\"numberOfNewTransactions\":92},{"
      "\"address\":\"/"
      "8.8.8.8:5000\",\"numberOfAllTransactions\":925,"
      "\"numberOfInvalidTransactions\":0,\"numberOfNewTransactions\":20}]}";

  get_neighbors_res_t* nbors = get_neighbors_res_new();

  serializer.vtable.get_neighbors_deserialize_response(&serializer, json_text,
                                                       nbors);

  neighbor_info_t* nb = get_neighbors_res_neighbor_at(nbors, 0);
  TEST_ASSERT_EQUAL_STRING("/8.8.8.8:14265", nb->address->data);
  TEST_ASSERT_EQUAL_INT(922, nb->all_trans_num);
  TEST_ASSERT_EQUAL_INT(0, nb->invalid_trans_num);
  TEST_ASSERT_EQUAL_INT(92, nb->new_trans_num);
  nb = get_neighbors_res_neighbor_at(nbors, 1);
  TEST_ASSERT_EQUAL_STRING("/8.8.8.8:5000", nb->address->data);
  TEST_ASSERT_EQUAL_INT(925, nb->all_trans_num);
  TEST_ASSERT_EQUAL_INT(0, nb->invalid_trans_num);
  TEST_ASSERT_EQUAL_INT(20, nb->new_trans_num);
  nb = get_neighbors_res_neighbor_at(nbors, 2);
  TEST_ASSERT_NULL(nb);
  get_neighbors_res_free(nbors);
}

void test_serialize_add_neighbors(void) {
  serializer_t serializer;
  const char* json_text =
      "{\"command\":\"addNeighbors\",\"uris\":[\"udp://8.8.8.8:14265\",\"udp://"
      "9.9.9.9:443\"]}";

  char_buffer_t* serializer_out = char_buffer_new();
  init_json_serializer(&serializer);
  add_neighbors_req_t* req = add_neighbors_req_new();
  add_neighbors_req_add(req, "udp://8.8.8.8:14265");
  add_neighbors_req_add(req, "udp://9.9.9.9:443");

  serializer.vtable.add_neighbors_serialize_request(&serializer, req,
                                                    serializer_out);

  TEST_ASSERT_EQUAL_STRING(json_text, serializer_out->data);

  char_buffer_free(serializer_out);
  add_neighbors_req_free(req);
}

void test_deserialize_add_neighbors(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text = "{\"addedNeighbors\":3,\"duration\":2}";

  add_neighbors_res_t res = 0;

  serializer.vtable.add_neighbors_deserialize_response(&serializer, json_text,
                                                       &res);

  TEST_ASSERT_EQUAL_INT(3, res);
}

void test_serialize_remove_neighbors(void) {
  serializer_t serializer;
  const char* json_text =
      "{\"command\":\"removeNeighbors\",\"uris\":[\"udp://"
      "8.8.8.8:14265\",\"udp://"
      "9.9.9.9:443\"]}";

  char_buffer_t* serializer_out = char_buffer_new();
  init_json_serializer(&serializer);
  remove_neighbors_req_t* req = remove_neighbors_req_new();
  remove_neighbors_req_add(req, "udp://8.8.8.8:14265");
  remove_neighbors_req_add(req, "udp://9.9.9.9:443");

  serializer.vtable.remove_neighbors_serialize_request(&serializer, req,
                                                       serializer_out);

  TEST_ASSERT_EQUAL_STRING(json_text, serializer_out->data);

  char_buffer_free(serializer_out);
  remove_neighbors_req_free(req);
}

void test_deserialize_remove_neighbors(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text = "{\"removedNeighbors\":1,\"duration\":2}";

  remove_neighbors_res_t res = 0;

  serializer.vtable.remove_neighbors_deserialize_response(&serializer,
                                                          json_text, &res);

  TEST_ASSERT_EQUAL_INT(1, res);
}

void test_serialize_get_trytes(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text =
      "{\"command\":\"getTrytes\",\"hashes\":["
      "\"OAATQS9VQLSXCLDJVJJVYUGONXAXOFMJOZNSYWRZSWECMXAQQURHQBJNLD9"
      "IOFEPGZEPEMPXCIVRX9999\"]}";

  get_trytes_req_t* get_tyt = get_trytes_req_new();
  char_buffer_t* serializer_out = char_buffer_new();

  get_trytes_req_add_hash(get_tyt,
                          "OAATQS9VQLSXCLDJVJJVYUGONXAXOFMJOZNSYWRZS"
                          "WECMXAQQURHQBJNLD9IOFEPGZEPEMPXCIVRX9999");

  serializer.vtable.get_trytes_serialize_request(&serializer, get_tyt,
                                                 serializer_out);

  TEST_ASSERT_EQUAL_STRING(json_text, serializer_out->data);

  char_buffer_free(serializer_out);
  get_trytes_req_free(get_tyt);
}

void test_deserialize_get_trytes(void) {
  serializer_t serializer;
  init_json_serializer(&serializer);
  const char* json_text =
      "{\"trytes\": "
      "[\"BYSWEAUTWXHXZ9YBZISEK9LUHWGMHXCGEVNZHRLUWQFCUSDXZHOFHW"
      "HL9MQPVJXXZLIXPXPXF9KYEREFSKCPKYIIKPZVLHUTDFQKKVVBBN9ATTL"
      "PCNPJDWDEVIYYLGPZGCWXOBDXMLJC9VO9QXTTBLAXTTBFUAROYEGQIVB9"
      "MJWJKXJMCUPTWAUGFZBTZCSJVRBGMYXTVBDDS9MYUJCPZ9YDWWQNIPUAI"
      "JXXSNLKUBSCOIJPCLEFPOXFJREXQCUVUMKSDOVQGGHRNILCO9GNCLWFM9"
      "APMNMWYASHXQAYBEXF9QRIHIBHYEJOYHRQJAOKAQ9AJJFQ9WEIWIJOTZA"
      "TIBOXQLBMIJU9PCGBLVDDVFP9CFFSXTDUXMEGOOFXWRTLFGV9XXMYWEMG"
      "QEEEDBTIJ9OJOXFAPFQXCDAXOUDMLVYRMRLUDBETOLRJQAEDDLNVIRQJU"
      "BZBO9CCFDHIX9MSQCWYAXJVWHCUPTRSXJDESISQPRKZAFKFRULCGVRSBL"
      "VFOPEYLEE99JD9SEBALQINPDAZHFAB9RNBH9AZWIJOTLBZVIEJIAYGMC9"
      "AZGNFWGRSWAXTYSXVROVNKCOQQIWGPNQZKHUNODGYADPYLZZZUQRTJRTO"
      "DOUKAOITNOMWNGHJBBA99QUMBHRENGBHTH9KHUAOXBVIVDVYYZMSEYSJW"
      "IOGGXZVRGN999EEGQMCOYVJQRIRROMPCQBLDYIGQO9AMORPYFSSUGACOJ"
      "XGAQSPDY9YWRRPESNXXBDQ9OZOXVIOMLGTSWAMKMTDRSPGJKGBXQIVNRJ"
      "RFRYEZ9VJDLHIKPSKMYC9YEGHFDS9SGVDHRIXBEMLFIINOHVPXIFAZCJK"
      "BHVMQZEVWCOSNWQRDYWVAIBLSCBGESJUIBWZECPUCAYAWMTQKRMCHONIP"
      "KJYYTEGZCJYCT9ABRWTJLRQXKMWY9GWZMHYZNWPXULNZAPVQLPMYQZCYN"
      "EPOCGOHBJUZLZDPIXVHLDMQYJUUBEDXXPXFLNRGIPWBRNQQZJSGSJTTYH"
      "IGGFAWJVXWL9THTPWOOHTNQWCNYOYZXALHAZXVMIZE9WMQUDCHDJMIBWK"
      "TYH9AC9AFOT9DPCADCV9ZWUTE9QNOMSZPTZDJLJZCJGHXUNBJFUBJWQUE"
      "ZDMHXGBPTNSPZBR9TGSKVOHMOQSWPGFLSWNESFKSAZY9HHERAXALZCABF"
      "YPOVLAHMIHVDBGKUMDXC9WHHTIRYHZVWNXSVQUWCR9M9RAGMFEZZKZ9XE"
      "OQGOSLFQCHHOKLDSA9QCMDGCGMRYJZLBVIFOLBIJPROKMHOYTBTJIWUZW"
      "JMCTKCJKKTR9LCVYPVJI9AHGI9JOWMIWZAGMLDFJA9WU9QAMEFGABIBEZ"
      "NNAL9OXSBFLOEHKDGHWFQSHMPLYFCNXAAZYJLMQDEYRGL9QKCEUEJ9LLV"
      "UOINVSZZQHCIKPAGMT9CAYIIMTTBCPKWTYHOJIIY9GYNPAJNUJ9BKYYXS"
      "V9JSPEXYMCFAIKTGNRSQGUNIYZCRT9FOWENSZQPD9ALUPYYAVICHVYELY"
      "FPUYDTWUSWNIYFXPX9MICCCOOZIWRNJIDALWGWRATGLJXNAYTNIZWQ9YT"
      "VDBOFZRKO9CFWRPAQQRXTPACOWCPRLYRYSJARRKSQPR9TCFXDVIXLP9XV"
      "L99ERRDSOHBFJDJQQGGGCZNDQ9NYCTQJWVZIAELCRBJJFDMCNZU9FIZRP"
      "GNURTXOCDSQGXTQHKHUECGWFUUYS9J9NYQ9U9P9UUP9YMZHWWWCIASCFL"
      "CMSKTELZWUGCDE9YOKVOVKTAYPHDF9ZCCQAYPJIJNGSHUIHHCOSSOOBUD"
      "OKE9CJZGYSSGNCQJVBEFTZFJ9SQUHOASKRRGBSHWKBCBWBTJHOGQ9WOMQ"
      "FHWJVEG9NYX9KWBTCAIXNXHEBDIOFO9ALYMFGRICLCKKLG9FOBOX9PDWN"
      "QRGHBKHGKKRLWTBEQMCWQRLHAVYYZDIIPKVQTHYTWQMTOACXZOQCDTJTB"
      "AAUWXSGJF9PNQIJ9AJRUMUVCPWYVYVARKR9RKGOUHHNKNVGGPDDLGKPQN"
      "OYHNKAVVKCXWXOQPZNSLATUJT9AUWRMPPSWHSTTYDFAQDXOCYTZHOYYGA"
      "IM9CELMZ9AZPWB9MJXGHOKDNNSZVUDAGXTJJSSZCPZVPZBYNNTUQABSXQ"
      "WZCHDQSLGK9UOHCFKBIBNETK999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999NOXDXXKUD"
      "WLOFJLIPQIBRBMGDYCPGDNLQOLQS99EQYKBIU9VHCJVIPFUYCQDNY9APG"
      "EVYLCENJIOBLWNB999999999XKBRHUD99C99999999NKZKEKWLDKMJCI9"
      "N9XQOLWEPAYWSH9999999999999999999999999KDDTGZLIPBNZKMLTOL"
      "OXQVNGLASESDQVPTXALEKRMIOHQLUHD9ELQDBQETS9QFGTYOYWLNTSKKM"
      "VJAUXSIROUICDOXKSYZTDPEDKOQENTJOWJONDEWROCEJIEWFWLUAACVSJ"
      "FTMCHHXJBJRKAAPUDXXVXFWP9X9999IROUICDOXKSYZTDPEDKOQENTJOW"
      "JONDEWROCEJIEWFWLUAACVSJFTMCHHXJBJRKAAPUDXXVXFWP9X9999\"]}";

  get_trytes_res_t* deserialize_get_tyt = get_trytes_res_new();

  serializer.vtable.get_trytes_deserialize_response(&serializer, json_text,
                                                    deserialize_get_tyt);
  TEST_ASSERT_EQUAL_STRING(
      "BYSWEAUTWXHXZ9YBZISEK9LUHWGMHXCGEVNZHRLUWQFCUSDXZHOFHW"
      "HL9MQPVJXXZLIXPXPXF9KYEREFSKCPKYIIKPZVLHUTDFQKKVVBBN9ATTL"
      "PCNPJDWDEVIYYLGPZGCWXOBDXMLJC9VO9QXTTBLAXTTBFUAROYEGQIVB9"
      "MJWJKXJMCUPTWAUGFZBTZCSJVRBGMYXTVBDDS9MYUJCPZ9YDWWQNIPUAI"
      "JXXSNLKUBSCOIJPCLEFPOXFJREXQCUVUMKSDOVQGGHRNILCO9GNCLWFM9"
      "APMNMWYASHXQAYBEXF9QRIHIBHYEJOYHRQJAOKAQ9AJJFQ9WEIWIJOTZA"
      "TIBOXQLBMIJU9PCGBLVDDVFP9CFFSXTDUXMEGOOFXWRTLFGV9XXMYWEMG"
      "QEEEDBTIJ9OJOXFAPFQXCDAXOUDMLVYRMRLUDBETOLRJQAEDDLNVIRQJU"
      "BZBO9CCFDHIX9MSQCWYAXJVWHCUPTRSXJDESISQPRKZAFKFRULCGVRSBL"
      "VFOPEYLEE99JD9SEBALQINPDAZHFAB9RNBH9AZWIJOTLBZVIEJIAYGMC9"
      "AZGNFWGRSWAXTYSXVROVNKCOQQIWGPNQZKHUNODGYADPYLZZZUQRTJRTO"
      "DOUKAOITNOMWNGHJBBA99QUMBHRENGBHTH9KHUAOXBVIVDVYYZMSEYSJW"
      "IOGGXZVRGN999EEGQMCOYVJQRIRROMPCQBLDYIGQO9AMORPYFSSUGACOJ"
      "XGAQSPDY9YWRRPESNXXBDQ9OZOXVIOMLGTSWAMKMTDRSPGJKGBXQIVNRJ"
      "RFRYEZ9VJDLHIKPSKMYC9YEGHFDS9SGVDHRIXBEMLFIINOHVPXIFAZCJK"
      "BHVMQZEVWCOSNWQRDYWVAIBLSCBGESJUIBWZECPUCAYAWMTQKRMCHONIP"
      "KJYYTEGZCJYCT9ABRWTJLRQXKMWY9GWZMHYZNWPXULNZAPVQLPMYQZCYN"
      "EPOCGOHBJUZLZDPIXVHLDMQYJUUBEDXXPXFLNRGIPWBRNQQZJSGSJTTYH"
      "IGGFAWJVXWL9THTPWOOHTNQWCNYOYZXALHAZXVMIZE9WMQUDCHDJMIBWK"
      "TYH9AC9AFOT9DPCADCV9ZWUTE9QNOMSZPTZDJLJZCJGHXUNBJFUBJWQUE"
      "ZDMHXGBPTNSPZBR9TGSKVOHMOQSWPGFLSWNESFKSAZY9HHERAXALZCABF"
      "YPOVLAHMIHVDBGKUMDXC9WHHTIRYHZVWNXSVQUWCR9M9RAGMFEZZKZ9XE"
      "OQGOSLFQCHHOKLDSA9QCMDGCGMRYJZLBVIFOLBIJPROKMHOYTBTJIWUZW"
      "JMCTKCJKKTR9LCVYPVJI9AHGI9JOWMIWZAGMLDFJA9WU9QAMEFGABIBEZ"
      "NNAL9OXSBFLOEHKDGHWFQSHMPLYFCNXAAZYJLMQDEYRGL9QKCEUEJ9LLV"
      "UOINVSZZQHCIKPAGMT9CAYIIMTTBCPKWTYHOJIIY9GYNPAJNUJ9BKYYXS"
      "V9JSPEXYMCFAIKTGNRSQGUNIYZCRT9FOWENSZQPD9ALUPYYAVICHVYELY"
      "FPUYDTWUSWNIYFXPX9MICCCOOZIWRNJIDALWGWRATGLJXNAYTNIZWQ9YT"
      "VDBOFZRKO9CFWRPAQQRXTPACOWCPRLYRYSJARRKSQPR9TCFXDVIXLP9XV"
      "L99ERRDSOHBFJDJQQGGGCZNDQ9NYCTQJWVZIAELCRBJJFDMCNZU9FIZRP"
      "GNURTXOCDSQGXTQHKHUECGWFUUYS9J9NYQ9U9P9UUP9YMZHWWWCIASCFL"
      "CMSKTELZWUGCDE9YOKVOVKTAYPHDF9ZCCQAYPJIJNGSHUIHHCOSSOOBUD"
      "OKE9CJZGYSSGNCQJVBEFTZFJ9SQUHOASKRRGBSHWKBCBWBTJHOGQ9WOMQ"
      "FHWJVEG9NYX9KWBTCAIXNXHEBDIOFO9ALYMFGRICLCKKLG9FOBOX9PDWN"
      "QRGHBKHGKKRLWTBEQMCWQRLHAVYYZDIIPKVQTHYTWQMTOACXZOQCDTJTB"
      "AAUWXSGJF9PNQIJ9AJRUMUVCPWYVYVARKR9RKGOUHHNKNVGGPDDLGKPQN"
      "OYHNKAVVKCXWXOQPZNSLATUJT9AUWRMPPSWHSTTYDFAQDXOCYTZHOYYGA"
      "IM9CELMZ9AZPWB9MJXGHOKDNNSZVUDAGXTJJSSZCPZVPZBYNNTUQABSXQ"
      "WZCHDQSLGK9UOHCFKBIBNETK999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999NOXDXXKUD"
      "WLOFJLIPQIBRBMGDYCPGDNLQOLQS99EQYKBIU9VHCJVIPFUYCQDNY9APG"
      "EVYLCENJIOBLWNB999999999XKBRHUD99C99999999NKZKEKWLDKMJCI9"
      "N9XQOLWEPAYWSH9999999999999999999999999KDDTGZLIPBNZKMLTOL"
      "OXQVNGLASESDQVPTXALEKRMIOHQLUHD9ELQDBQETS9QFGTYOYWLNTSKKM"
      "VJAUXSIROUICDOXKSYZTDPEDKOQENTJOWJONDEWROCEJIEWFWLUAACVSJ"
      "FTMCHHXJBJRKAAPUDXXVXFWP9X9999IROUICDOXKSYZTDPEDKOQENTJOW"
      "JONDEWROCEJIEWFWLUAACVSJFTMCHHXJBJRKAAPUDXXVXFWP9X9999",
      get_trytes_res_tryte_at(deserialize_get_tyt, 0));
  TEST_ASSERT_EQUAL_STRING(NULL,
                           get_trytes_res_tryte_at(deserialize_get_tyt, 2));
  get_trytes_res_free(deserialize_get_tyt);
}

int main(void) {
  UNITY_BEGIN();

  // find_transactions
  RUN_TEST(test_serialize_find_transactions);
  RUN_TEST(test_deserialize_find_transactions);

  // get_node_info
  RUN_TEST(test_serialize_get_node_info);
  RUN_TEST(test_deserialize_get_node_info);

  // get_neighbors
  RUN_TEST(test_serialize_get_neighbors);
  RUN_TEST(test_deserialize_get_neighbors);

  // add_neighbors
  RUN_TEST(test_serialize_add_neighbors);
  RUN_TEST(test_deserialize_add_neighbors);

  // remove_neighbors
  RUN_TEST(test_serialize_remove_neighbors);
  RUN_TEST(test_deserialize_remove_neighbors);

  // get_trytes
  RUN_TEST(test_serialize_get_trytes);
  RUN_TEST(test_deserialize_get_trytes);

  return UNITY_END();
}
