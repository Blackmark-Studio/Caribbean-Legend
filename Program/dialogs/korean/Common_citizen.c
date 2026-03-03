// boal 25/04/04 общий диалог горожан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("간첩이다! 경비병들!","경보! 침입자가 있다!");
				link.l1 = "닥쳐. 나 간다.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("이 마을을 다스리는 사람이 바로 당신이라고들 하더군, "+GetSexPhrase("나리","아가씨")+".","참 반가운 만남이군, 도시 책임자가 내게 질문을 하러 다가왔어.");
					link.l1 = RandPhraseSimple("내 마음이 바뀌었어.","나는 그냥 이 마을을 둘러보고 있을 뿐이야. 안녕.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("너에게 물어볼 게 있어.","정보가 필요해.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("사업 이야기를 하고 싶소.","재정에 관해서...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("뭐야? 얼른 가.","길 막지 말고, 꺼져!");
					link.l1 = RandPhraseSimple("이봐, 짖는 소리 그만해, 알겠어?","진정해, 아니면 후회하게 될 거야!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("너에게 물어볼 게 있어.","잠시만 주목해 주십시오. 질문이 있습니다.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("사업 이야기를 하고 싶어.","재정에 관해서...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("내 이름은 ","내 이름은 ","나를 이렇게 불러도 된다 ")+GetFullName(npchar)+LinkRandPhrase(". 무엇이 필요하지?",". 나는 못 봤어 "+NPCharSexPhrase(NPChar,"전에 여기서 본 적 있어","전에 거기서 본 적 있어")+", 너 누구야?",". 너는 누구고, 나한테서 뭘 원하는 거지?"),LinkRandPhrase("안녕하시오, "+GetAddress_Form(NPChar)+". 내 이름은 "+GetFullName(npchar)+". 너는 이름이 뭐지?","안녕하세요, "+GetAddress_Form(NPChar)+"! 나는 "+GetFullName(npchar)+". 성함을 여쭤봐도 되겠습니까?","그래, "+GetAddress_Form(NPChar)+". 무슨 일이야? 그런데 내 이름은 "+GetFullName(npchar)+". 그런데 너는 누구냐?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("천둥이여! ","지옥에 종이 울리네! ","재수 없는 놈! ")+"그래, 내가 선장이야 "+GetFullName(Pchar)+LinkRandPhrase(", 너 정말 나에 대해 들어본 적 없구나"+NPCharSexPhrase(NPChar,", 이 녀석?","?")," 그리고 "+GetSexPhrase("가장 악명 높은 해적","가장 악명 높은 여자 해적")+" 이 바다에서! "," 그게 사실이 아니라면 지옥불에 타 죽어도 좋아!"),LinkRandPhrase("나는 선장이오"+GetFullName(Pchar)+".","내 이름은 "+GetFullName(Pchar)+".","나를 선장이라 불러도 된다 "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "선장님, 저 좀 도와주실 수 있습니까?";
					link.l1 = LinkRandPhrase("미안하지만, 안 되겠소. 내가 내어줄 시간이 별로 없네.","미안하지만, 안 돼. 너무 바빠.","아니, 못 하겠소. 내가 당장 처리해야 할 급한 일이 있소.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("물론이지. 무슨 문제야?","그래, 도와줄게. 네 일에 대해 좀 더 말해 봐.","네 사업에 대해 좀 더 말해 봐...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "예, 선장님, 듣고 있습니다.";
					link.l1 = NPChar.name+", 당신의 결혼반지를 찾았소.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("이 마을에 대해 더 알고 싶어.","이 마을에 대해 말해 줘.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("너에게 물어볼 게 있어.","정보가 필요해.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("사업 이야기를 하고 싶소.","재정에 관해서...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("잠깐! 지금 당장 네가 누구인지 말해! 나는 총독의 요청으로 적 스파이를 찾고 있다. "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","멈춰라! 나는 이 마을의 이익을 위해 행동한다 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 총독의 명령으로 왔다. 나는 적대적인 첩자를 찾아 도시를 수색 중이다.","멈춰라, 친구! 이곳 총독이 "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 마을에서 첩자를 찾으려고 한다."),LinkRandPhrase("잠깐만요, 아가씨! 지금 당장 당신이 누구인지 말해! 나는 총독의 부탁으로 적 스파이를 찾고 있어 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","여인, 당신을 억류해야겠소! 나는 마을의 이익을 위해 행동하는 것이오 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 총독의 명령으로 왔다. 나는 적대적인 첩자를 찾으려고 이 도시를 수색 중이다","가만히 있어, 미녀야! 이곳 총독이 "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 마을에 첩자가 있는지 찾고 싶어 하네..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "혹시 조언 좀 해줄 수 있겠나. 나는 구입하고 싶은 게 있어 "+pchar.GenQuest.Device.Shipyarder.Type+", 그리고 그게 당신네 마을에서 팔리고 있다고 들었소. 누군가가 거리에서 그걸 팔고 있었다는데, 혹시 아는 게 있소?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("알고 있나","알고 있었나","들었어")+" 최근에 이 지역 교회가 습격당했다는 소식 들었나?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("오, 너였군, "+GetFullName(Pchar)+" "+GetSexPhrase(", 이 늙은 악당아","- 잘나가는 아가씨")+"","다시 만나서 반갑군, "+GetSexPhrase("늙은 친구","아름다움")+" "+Pchar.name,"오, 이거 반가운 "+GetSexPhrase("Captain","아가씨")+" "+GetFullName(Pchar))+LinkRandPhrase(". 너 죽은 줄 알았어!",". 그리고 분명히, "+GetSexPhrase("늘 그렇듯이 취했군.","이미 몸이 안 좋아.")+"",". 그리고 보아하니, 아직도 자유롭군!")+LinkRandPhrase(" 그래, 할 말 있으면 해봐라 – 뭐가 필요하지?"," 이번에는 무슨 일이야?"," 또 쓸데없이 나한테 시비 거는 거야?"),LinkRandPhrase(TimeGreeting()+", 선장 ","안녕하세요, "+GetAddress_Form(NPChar)+" ","환영합니다, 선장님 ")+GetFullName(Pchar)+LinkRandPhrase(". 무엇이 "+GetSexPhrase("그렇게 용감한 신사","참으로 멋진 숙녀")+", 좋아? 나한테 필요한 거라도 있어?",". 무슨 일로 여기 왔소?",". 이번에는 뭘 알고 싶은데?")),PCharRepPhrase(LinkRandPhrase("안녕하십니까, 선장님 ","안녕하세요. 아, 당신이었군 "+GetAddress_Form(NPChar)+" ","오, 선장님 ")+GetFullName(Pchar)+LinkRandPhrase(", 라고 생각했지"+NPCharSexPhrase(NPChar," "," ")+"우리는 다시는 만나지 않을 거라고,",", 반갑다고는 못 하겠군"+NPCharSexPhrase(NPChar," "," ")+"당신을 보게 되어, 하지만",", 그렇군, 아직 살아 있었군. 유감이야. 그래서,")+LinkRandPhrase(" 뭐가 필요하지?"," 무슨 일로 왔지?"," 내가 무엇을 할 수 있지 "+NPCharSexPhrase(NPChar,"무엇을 도와드릴까요?","무엇을 도와드릴까요?")),LinkRandPhrase(TimeGreeting()+", 선장님 "+GetFullName(Pchar)+". 무엇을 도와드릴까요?","오, 이게 누구야"+GetSexPhrase("","")+" Captain "+GetFullName(Pchar)+"! 이번에는 무엇을 알고 싶으신가요?","안녕하세요, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". 무슨 일이라도 있나?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("아니, 네가 잘못 들은 거야. 난 이제 가볼게.","아니, 아무것도 아니야 – 그냥 가던 중이었어"+GetSexPhrase("","")+" 술집으로."),RandPhraseSimple("아니, 아무것도 아니야. 행운을 빌어!","그냥 둘러보고 있어. 잘 가."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "무슨 질문?";
			link.l1 = "이 서류에 적힌 이름이 익숙한가?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("나는 낯선 문서 따위엔 관심 없어. 게다가 나는 글도 못 읽거든. 고리대금업자한테 가 봐, 그 악마는 분명히 읽고 쓸 줄 알 거야.","무슨 말인지 전혀 모르겠소. 마을 사람들에게 물어보시오, 선장 "+GetFullName(Pchar)+".","정말 어떻게 도와드려야 할지 모르겠습니다, 선장님 "+GetFullName(Pchar)+". 고리대금업자에게 한번 물어보시오 – 혹시 뭔가 알지도 모르니까.");
			link.l1 = "기꺼이 당신의 조언을 따르겠습니다!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("하지만 거짓말하는 거 아니오, 선장 "+GetFullName(Pchar)+"?","그래서 뭐, "+PChar.name+"?","나는 너를 기억할 거야, "+GetFullName(Pchar)+".")+"그래서, 이제 무엇이 필요하시오?",LinkRandPhrase("만나서 반갑소, 선장님 "+PChar.name,"Glad"+NPCharSexPhrase(NPChar," "," ")+" 만나서 "+GetAddress_Form(NPChar)+" "+PChar.lastname,"만나서 반갑소, 선장 "+PChar.name)+". 하지만 내 이름만 알려고 여기 온 건 아니겠지?");

            link.l1 = PCharRepPhrase("하고 싶었어"+GetSexPhrase("","")+" 네가 이 구멍 같은 마을에 대해 뭘 좀 안다고?","하고 싶었어"+GetSexPhrase("","")+" 이 마을에 대해 뭔가를 알고 싶어.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("너에게 물어볼 게 있어.","정보가 필요해.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("사업 이야기를 하고 싶소.","재정에 관해서...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "혹시 조언 좀 해줄 수 있겠나. 나는 구매하고 싶은데\n "+pchar.GenQuest.Device.Shipyarder.Type+", 그리고 그게 당신네 마을에서 팔리고 있다는 얘기를 들었소. 누군가가 거리에서 그것을 팔고 있었다더군. 혹시 그 일에 대해 아는 게 있소?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("잠깐! 지금 당장 네가 누구인지 말해라! 나는 총독의 요청으로 적 스파이를 찾고 있다 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","멈춰라! 나는 ~의 이익을 위해 행동한다"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 총독의 명령으로 왔다. 적대적인 첩자를 찾아 도시를 수색 중이다.","멈춰, 친구! 이 지역 총독이 "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 도시에 있는 스파이를 찾고 싶어 한다."),LinkRandPhrase("잠깐, 아가씨! 지금 당장 네가 누구인지 말해! 나는 총독의 요청으로 적 스파이를 찾고 있다 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","여인, 당신을 체포해야겠소! 나는 도시의 이익을 위해 행동하는 것이오 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 총독의 명령으로 왔다. 나는 적대적인 첩자를 찾아 도시를 수색 중이다.","멈춰라, 아름다운 여인! 이곳 총독이 "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 도시에 있는 첩자를 찾아내고 싶어 하는군..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("알고 있나","들었어","들었어")+" 근처 교회가 최근에 습격당했다는 소식 들었어?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("아니야, 네가 착각하고 있는 거야. 이제 가볼게.","아니, 아무것도 아니야 - 그냥 선술집에 가던 중이었어."),RandPhraseSimple("아니, 아무것도 아니야. 행운을 빌어!","그냥 둘러보는 중이야. 안녕."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("아, 그래, 나도 거의 그만큼 기쁘다"+NPCharSexPhrase(NPChar," "," ")+" 술 한 잔처럼 반갑군. 뭐든 물어봐.","말하는 거 좋아하시오, 선장? 나도 그렇지... 특히 럼 한 잔 하면서 말이야.","그래, "+PChar.name+"?"),LinkRandPhrase("무슨 일이야?","알겠습니다, 선장님 "+PChar.name+". 당신은"+GetSexPhrase("","")+" 말이 많군. ","너 때문에 진이 다 빠졌어"+GetSexPhrase("","")+" 질문은 그만하시고, 선장님. 럼주나 좀 도와주시는 게 좋겠소.")),PCharRepPhrase(LinkRandPhrase("무엇을 알고 싶은가 "+GetAddress_Form(NPChar)+"?","듣고 있소, 선장님.","가야 하니, 서둘러 주십시오, 선장님."),LinkRandPhrase("언제나 반갑지"+NPCharSexPhrase(NPChar," "," ")+"  좋은 동료들과 함께하는 것, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". 할 말 있으면 해.","그래, "+GetAddress_Form(NPChar)+"?","잡담 좋아하시오, 선장? 나도 그렇지...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("이 근처 선술집에서 무슨 소문이 돌고 있지?","이 땅에서는 무슨 일이 벌어지고 있지?","여기 육지에선 무슨 새로운 소식이 있지?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("거기로 가는 길을 알려줄 수 있나?","어딘가로 가는 길을 못 찾겠어...","길을 알려줄 수 있겠소...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("나는 어떤 사람에 대해 사람들이 무슨 말을 하는지 알고 싶어.","어떤 사람에 대해 사람들이 뭐라고들 하는지 모르겠어?","현지인들에 대해 좀 배우고 싶어.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "당신네 식민지에 대해 좀 더 말씀해 주십시오.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("중요한 일이 있어!","너와 볼 일이 있다.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("아니야, 네가 착각하는 거야. 이제 가볼게.","아니, 아무것도 아니야 - 그냥 선술집에 가던 중이었어."),RandPhraseSimple("아니, 아무것도 아니야. 행운을 빌어!","그냥 둘러보고 있어. 잘 가."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "누구에 대해 알고 싶으십니까?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "총독에 대해서.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "이곳 선술집 주인에 대해서.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "항만 관리자에 대해.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "이 동네 상점 주인에 대해서.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "신경 쓰지 마, 잊어버려.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "고맙다.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("솔직히 잘 아는 건 아니지만, 그래도 몇 가지는 말해줄 수 있어.","우리 식민지에서 뭐가 그렇게 궁금한가?","물론이지. 무엇이 궁금한가?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "여긴 어떤 마을이지?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "그 마을을 지키는 요새에 대해 무엇을 알고 있지?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "화제를 바꿔보자.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "장난해? 농담하는 거야? 화면 오른쪽 위를 봐.";
			link.l1 = "그래, 내 잘못이야.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "난 그 일에 대해 아무것도 몰라.";
			link.l1 = "안됐군.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "흠, "+pchar.GenQuest.Device.Shipyarder.Type+"? 처음 들어보는데... 그게 대체 뭐야? 내가 살아오면서 그런 건 한 번도 들어본 적 없어"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "글쎄, 그건 조선공의 도구야, "+pchar.GenQuest.Device.Shipyarder.Describe+". 이런 걸 파는 사람이 마을에 있었나? 어쩌면 있었을지도. 이런 걸 들고 다니는 사람을 본 적 있나?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "흠... 그래, 나도 그런 걸 가진 사람을 본 적이 있는 것 같아. 몇 시간 전에 저쪽을 그걸 들고 돌아다니더군. 확실히 흥미로운 장치였어.";
				link.l1 = "그 사람은 어떻게 생겼고, 어디로 갔지? 그 도구가 정말 필요하거든.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "아니, 그런 건 본 적 없어.";
				link.l1 = "알겠어. 자, 이제 사람들에게 물어볼 시간이군!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"그게 나랑 무슨 상관이야? 나는 여기 토박이야!","그래, 그런데 왜 나한테 이런 걸로 귀찮게 구나? 나는 이 도시에 살고 있을 뿐이고, 그런 일에 대해선 아무것도 모르네!"),NPCharSexPhrase(npchar,"또 나한테 뭘 원하는 거야? 내가 첩자가 아니라고 이미 말했잖아?!","내가 이미 여기 토박이라고 말하지 않았어?!"),NPCharSexPhrase(npchar,"내 사랑, 또 너구나! 나 좀 내버려 둬 – 나는 이 동네 사람이야!","왜 또 멍청한 질문으로 귀찮게 하는 거야?"),NPCharSexPhrase(npchar,"또야! 이건 정말 말도 안 돼!","이봐, 그냥 나 좀 내버려 둬, 알았지? 제발!"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("누가 당신의 말을 증명할 수 있지?","아, 미안해 - 이미 너한테 물어봤었지...","죄송합니다, 사람이 너무 많아서...","알겠어, 알겠어...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "누구나 할 수 있어! 이봐, 왜 자꾸 나한테 귀찮게 구는 거야?! 문제가 있으면 총독한테 가서 다 해결해!",link.l1 ="흠... 이런 사소한 일로 그를 귀찮게 하지 않는 게 좋겠군. 나는 자네를 믿네.";}
			dialog.text = "이 마을에 있는 누구든지! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" 이를 할 수 있어, 예를 들어, 지금이라면\n "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"그","그녀")+" 바로 저기 서 있어.","오, 주님, 글쎄요, 예를 들면, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" 내가 할 수 있어.");				
			link.l1 = "좋아, 그럼 한번 보자.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "그래, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," 확실히 이곳 사람이야.","그녀는 정말 이곳 출신이야.");
			link.l1 = RandPhraseSimple("알겠어"+GetSexPhrase("","")+". 도와주셔서 감사합니다.","모두 이상 없어. 도와줘서 고마워.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "있잖아, 어제 나는 마을 밖을 산책하다가 결혼반지를 잃어버렸어... "+GetSexPhrase("선장님, 그것을 찾아주실 수 있겠습니까?","부인, 제발, 그것을 찾는 걸 도와주십시오!")+"";
			link.l1 = "물론이지 "+GetSexPhrase("할 수 있지! 너처럼 고운 아가씨를 위해서라면 뭐든지 할 수 있어!","도와드리겠습니다. 교회는 도움이 필요한 이들을 돕도록 가르칩니다.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("아니, 못 하겠어. 미안해. 할 일이 너무 많아.","미안하지만, 못 하겠어. 방금 생각났거든."+GetSexPhrase("","")+", 아직 끝내지 못한 일이 있어서...","나는 시간이 아주 없으니, 아무것도 도와줄 수 없어...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Captain","Lady")+", 정말 훌륭해요! 이 반지를 찾아 주세요, 제 남편이 곧 도착하거든요 "+sti(NPChar.LifeDay)+" 며칠이나 지났는데, 내 결혼반지 없이 그가 나를 보는 건 원치 않아.";
			link.l1 = RandPhraseSimple("어디서 잃어버렸다고 했지?","그래서 도대체 어디에서 잃어버린 거야?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "도시 성문 바로 지나서...";
			link.l1 = "그럼, 이제 그걸 찾으러 가야겠군...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "네, 그렇게 하시오. 그리고 서두르시오 – 아직 시간이 얼마 남지 않았다는 걸 기억하시오\n "+sti(NPChar.LifeDay)+" 일.";
			link.l1 = "기억나.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Captain","아가씨")+"! 정말 기뻐요! 어떻게 감사드려야 할까요?";
			link.l1 = "아, 고맙다는 말은 필요 없소 - 정말 아무런 대가 없이 한 일이오.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "몇 백 페소쯤은 나쁠 게 없지...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "오, "+GetSexPhrase("선장님, 참으로 고귀하신 분이십니다","아가씨, 참 고귀하시군요")+"! 내가 교회에서 반드시 당신을 위해 기도하겠소! 안녕히 가시오...";
			link.l1 = "안녕히 가시오, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "아, 물론이지. 여기 -"+FindRussianMoneyString(iTemp)+". 내가 가진 건 이게 전부야. 이 돈을 받아 주시오... 그리고 안녕히 가시오.";
			link.l1 = "안녕히 가십시오, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("아니, 나는 그 일에 대해 아무것도 몰라.","이 일에 대해 나는 아무것도 몰라.","나는 아무것도 몰라.");
					link.l1 = LinkRandPhrase("알겠어, 고마워.","알겠소, 고맙소.","좋아요, 실례하겠습니다.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("나는 그 일에 대해 아무것도 몰라. 하지만 선술집에 있는 손님들에게 물어봐. 분명 뭔가 알려줄 거야.","아무것도 말해줄 수 없어. 선술집에서 물어봐.","나는 특별히 아는 건 없지만, 선술집에서 소문이 돌았다는 얘기는 들었어.");
				link.l1 = "그래도 이 정도면 다행이지.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 이 마을 시민으로서 부탁하네. 칼집에서 칼을 뽑은 채로 돌아다니는 건 삼가주게.","이봐, 이 마을 시민으로서 말하는데, 칼집에서 뽑은 칼을 들고 다니는 건 삼가주게.");
				link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"진정해 "+GetSexPhrase("동료","아가씨")+" 무기를 들고 돌아다니면 말이야. 그게 나를 불안하게 만들어...","나는 ~할 때가 싫어 "+GetSexPhrase("남자들","아무나")+" 무기를 꺼내 들고 돌아다니잖아. 무서워서 말이야...");
				link.l1 = RandPhraseSimple("알겠어.","내가 치워둘게.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
