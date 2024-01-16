#include "Archiver.h"
#include "TestRunner.h"
#include <memory>

void Empty() {
    std::istringstream src("");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
    ASSERT_EQUAL(request->SizeAdditional(), 5);
    ASSERT_EQUAL(request1->SizeAdditional(), 5);

}

void OneCharacter() {
    std::istringstream src("aaa");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
    ASSERT_EQUAL(request->SizeAdditional(), 10);
    ASSERT_EQUAL(request1->SizeAdditional(), 10);
}

void TwoCharacter() {
    std::istringstream src("aaabbbbb");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
    ASSERT_EQUAL(request->SizeAdditional(), 15);
    ASSERT_EQUAL(request1->SizeAdditional(), 15);
}

void ThreeCharacter(){
    std::istringstream src("aaabbbbbcc");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
    ASSERT_EQUAL(request->SizeAdditional(), 20);
    ASSERT_EQUAL(request1->SizeAdditional(), 20);
}

void SameFrequency(){
    std::istringstream src("abcabc");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void SimpleTest1() {
    std::istringstream src("abbccc");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void SimpleTest2() {
    std::istringstream src("abbcccddddddd");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void LineFeed() {
    std::istringstream src("abbcccddddddd\nffffff");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void Register() {
    std::istringstream src("AAAAbBBBBbcccCCCCddddDDDDddd\nfffffFFFF");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void EnglishAlphabet() {
    std::istringstream src("a b c d e f g h i j k l m n o p q r s t u v w x y z Z Y X W V U T S R Q P O N M L K J I H G F E D C B A");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void RussianAlphabet() {
    std::istringstream src("� � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void EnglishText() {
    std::istringstream src("About a thousand years ago, people known as the Vikings were known and feared throughout Europe. The Vikings were the people of the northern part of Europe, called Scandinavia, which includes the modern countries of Denmark, Norway, and Sweden. The Vikings made their living by farming and fishing. However, by about the year 700, they began making attacks, or raids, upon towns along the coasts of Europe in order to steal the wealth of those towns.\n"
                           "\n"
                           " \n"
                           "\n"
                           "The Vikings made their attacks very quickly and without any warning. They were very cruel to the people of the towns they attacked, and they sometimes destroyed the towns by burning down the buildings. In some parts of Europe, the local kings would often fight against the Vikings. Sometimes, however, the kings would pay the Vikings in order to persuade them not to attack.\n"
                           "\n"
                           " \n"
                           "\n"
                           "Although the Vikings were known as fierce warriors, they also built excellent ships. The wooden Viking ships, called longboats, were able to sail even in very bad weather. Many Viking longboats were about 20 metres long, but some were nearly 90 metres long. The Viking sailors used both sails and oars to move their ships.\n"
                           "\n"
                           " \n"
                           "\n"
                           "The Vikings travelled across a large area. They made many of their attacks in Britain, France, and Germany, but sometimes sailed south, into the Mediterranean Sea. Other Vikings moved to the east, and then south along the rivers of Russia. Some even went as far as the area that is now the country of Turkey. In some places, the Vikings decided to stay. Many Vikings settled in England and in France, and eventually they mixed with the local people. Other Vikings settled in Russia and also mixed with the people there. The most famous travels of the Vikings were in the Atlantic Ocean. Vikings sailed westward to the island of Iceland where many of them stayed.\n"
                           "\n"
                           " \n"
                           "\n"
                           "Today, the people of Iceland are descended from the Vikings. Some Vikings sailed farther west to the cold island of Greenland. Vikings lived in Greenland for several generations, but eventually they died out. Some Vikings had gone even further west and reached the Canadian island of Newfoundland. The Vikings only stayed for a few years, but they had reached North America about 500 years before Christopher Columbus!\n"
                           "\n"
                           " \n"
                           "\n"
                           "Gradually, the Vikings became converted to the Christian religion. They also stopped raiding the towns of Europe, and instead of fighting, they began trading with their neighbors. Today, the Scandinavian countries are known as very peace-loving nations.");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void RussianText() {
    std::istringstream src("����� ������ ��� ����� �����, ��������� ��� �������, ����� � ������� �� ���� ������. ������� ���� ������� �������� ����� ������, ���������� ������������, � ������� ������ ����������� ������ �����, �������� � ������. ������� ������������ �� ����� ����������� � ��������. ������ �������� � 700 ���� ��� ������ ��������� ��������� ��� ������ �� ������ ����� ������� ������, ����� ������� ��������� ���� �������.\n"
                           "\n"
                           " \n"
                           "\n"
                           "������� ��������� ����� ������������ � ��� ��������������. ��� ���� ����� ������� � ������� �������, ������� ��� ���������, � ������ ��� ��������� ������, ������ ������. � ��������� ������ ������ ������� ������ ����� ��������� ������ ��������. ������ ������ ������ ������� ��������, ����� ������� �� �� ��������.\n"
                           "\n"
                           " \n"
                           "\n"
                           "���� ������� ���� �������� ��� �������� �����, ��� ����� ������� ���������� �������. ���������� ������� ��������, ���������� ����������, ����� ������� ���� � ����� ������ ������. ����� ������ ��������� �������� ���������� ����� 20 ������, � ���������-����� 90 ������. �������, ���������� �� ��������, ������������ ������ � ����� ��� ����������� ����� ��������.\n"
                           "\n"
                           " \n"
                           "\n"
                           "������� �������������� �� ������� ����������. ��� ��������� ����� ��������� � ��������������, ������� � ��������, �� ������ ����� �� ��, � ����������� ����. ������ ������� ��������� �� ������, � ����� � �� �� �� ������� �����. ��������� ���� ����� �� ����������, ������� ������ �������� ������� ������. � ��������� ������, ������� ������ ��������. ������ ������� �������� � ������ � �� �������, � � ����� ������ ��� ��������� � ������� ����������. ������ ������� ���������� � ������ � ���� ��������� � �������. ����� ��������� ����������� �������� ���� � ������������� ������. ������� ����� �� ����� � ������� ��������, ��� ������ �� ��� ���������������.\n"
                           "\n"
                           " \n"
                           "\n"
                           "������� ����� �������� ���������� �� ��������. ��������� ������� ����� ������ �� �����, � ��������� ������� ����������. ������� ���� � ���������� ��������� ���������, �� � ����� ������ �������. ��������� ������� ���� ��� ������ �� ����� � �������� ���������� ������� ������������. ������� ���������� ����� ����� ��������� ���, �� ��� �������� �������� ������� �������� �� 500 ��� �� ���������� �������!\n"
                           "\n"
                           " \n"
                           "\n"
                           "����������, ������� ������� ������������. ��� ����� ���������� ������ �� ������ ������ � ������ ����, ����� �������, ������ ��������� �� ������ ��������. ������� ������������� ������ �������� ��� ����� ����������� ������.");
    std::ostringstream os;

    std::unique_ptr<Request> request = std::make_unique<EncodeRequest>(src, os);
    request->Read();
    request->Process();
    request->Write();

    std::istringstream is(os.str());
    std::ostringstream dist;

    std::unique_ptr<Request> request1 = std::make_unique<DecodeRequest>(is, dist);
    request1->Read();
    request1->Process();
    request1->Write();

    ASSERT_EQUAL(src.str(), dist.str());
}

void AllTests() {
    TestRunner tr;
    tr.RunTest(Empty, "Empty");
    tr.RunTest(OneCharacter, "OneCharacter");
    tr.RunTest(TwoCharacter, "TwoCharacter");
    tr.RunTest(ThreeCharacter, "ThreeCharacter");
    tr.RunTest(SameFrequency, "SameFrequency");
    tr.RunTest(SimpleTest1, "SimpleTest1");
    tr.RunTest(SimpleTest2, "SimpleTest2");
    tr.RunTest(LineFeed, "LineFeed");
    tr.RunTest(Register, "Register");
    tr.RunTest(EnglishAlphabet, "EnglishAlphabet");
    tr.RunTest(RussianAlphabet, "RussianAlphabet");
    tr.RunTest(EnglishText, "EnglishText");
    tr.RunTest(RussianText, "RussianText");
}