//Jason общий диалог мещан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
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
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
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
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("이 마을이 당신 소유라고들 하더군, "+GetSexPhrase("나리","아가씨")+".","이렇게 반가운 만남이라니, "+GetSexPhrase("나리","아가씨")+"!");
					link.l1 = RandPhraseSimple("생각이 바뀌었어. 행운을 빌어!","그냥 마을을 돌아다니는 중이야. 잘 가.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("너한테 물어볼 게 있어.","정보가 좀 필요해.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("재정 문제에 대해 논의하고 싶소.","재정에 관해서...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("경보! 무장한 미치광이가 여기 있다! 무기를 들어라!","무기를 들어라! 여기 미친놈이 무기를 들고 있다!");
						link.l1 = RandPhraseSimple("뭐라고?!","뭐 하는 거야?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("뭘 원해? 어서 가.","내 길 막지 말고, 꺼져.");
						link.l1 = RandPhraseSimple("있잖아? 짖지 마!","진정하시오. 아니면 내가 직접 진정시켜 주겠소!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("당신에게 묻고 싶은 게 있어.","잠시만 주목해 주십시오. 질문이 하나 있습니다.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("재정 문제에 대해 논의하고 싶소.","재정에 관해서...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "좋은 하루입니다, "+GetAddress_Form(NPChar)+". 보아하니 당신이 직접 배의 선장이군요. 부탁 하나 드리고 싶소...";
					link.l1 = "듣고 있소, "+GetAddress_FormToNPC(NPChar)+". 무엇을 원하지?";
					link.l1.go = "passenger";
					link.l2 = "미안하오, "+GetAddress_FormToNPC(NPChar)+", 하지만 나는 급하오.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("나는 ","내 이름은 ","나를 이렇게 불러도 된다 ")+GetFullName(npchar)+LinkRandPhrase(". 무엇을 원하지?",". 전에 본 적이 없군. 누구지?",". 너는 누구고, 나에게 무엇을 원하는가?"),LinkRandPhrase("안녕하시오, "+GetAddress_Form(NPChar)+". 내 이름은 "+GetFullName(npchar)+". 그런데 이름이 무엇이오?","안녕하세요, "+GetAddress_Form(NPChar)+"! 나는 "+GetFullName(npchar)+". 성함을 여쭤봐도 되겠습니까?","그래, "+GetAddress_Form(NPChar)+". 뭐 원하는 거야? 그리고 참고로, 내 이름은 "+GetFullName(npchar)+". 그런데 이름이 무엇이오?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("이런 젠장! ","젠장! ","젠장할 놈! ")+"그래, 내가 선장이야 "+GetFullName(Pchar)+LinkRandPhrase(", 들어본 적 없나 "+NPCharSexPhrase(NPChar,", 이 자식아?","?")," 그리고 "+GetSexPhrase("가장 유명한 해적","가장 유명한 여자 해적")+" 바다에서!"," 내가 틀렸다면 천벌을 받아도 좋아!"),LinkRandPhrase("나는 "+GetFullName(Pchar)+", 선장님.","내 이름은 "+GetFullName(Pchar)+".","나를 선장이라고 불러도 돼 "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("도시 전체가 긴장하고 있어 - 왕실 감찰관인 돈 페르난도 데 알라미다가 도착했거든. 있잖아, 여기서 별별 일을 다 봤지만, 이번 일은... 사람을 바꾸는 건 슬픔 그 자체가 아니라, 그걸 어떻게 받아들이느냐더군. 그의 아버지가 돌아가신 후 완전히 달라졌다고들 해. 이제 군도 전체를 뒤져도 그보다 더 청렴하고... 무자비한 왕실의 하수인은 없을 거야.","'홀리 머시'를 좀 봐! 왕께서 특별한 설계로 직접 건조를 명하셨다더군. 그리고 봐, 흠집 하나 없어. 마치 성모 마리아께서 직접 지켜주시는 것처럼 말이야. 하지만 소문을 들었어... 어쩌면 성모님이 아니라는 얘기도 있더군.","너, 돈 페르난도를 죽이려고 몇 번이나 시도한 줄 아나? 지난 1년 동안만 해도 공해상에서 열두 번이나 습격을 받았지!\n하지만 그렇게 충성스럽고 훈련된 선원들이 있고, 주님의 가호까지 있으니, 열세 번째 공격도 무사히 넘길 거야!"),LinkRandPhrase("들었어? 돈 페르난도 데 알라미다가 우리 도시에 도착했대. 지금 어딘가 거리에 있다고 하더라. 직접 내 눈으로 한번 보고 싶군...","복잡한 사내지, 이 돈 페르난도란 사람. 어떤 이들은 그가 조국을 더러운 것들로부터 정화하는 구세주라 말하지. 하지만 또 다른 이들은, 그의 아버지가 죽은 뒤로 뭔가 그 안에서 부서졌고 곧 우리 모두가 눈물을 흘리게 될 거라고 속삭여. 하지만 내가 한마디 하자면, 그를 두려워하지 마. 그를 그렇게 만든 자들을 두려워해야 해.","정말 잘생긴 남자야, 이 돈 페르난도! 그런데 이상한 게 뭔지 알아? 마치 아무도 눈에 들어오지 않는 것 같아. 오직 의무와 봉사뿐이지. 어떤 여자가 있었다고 들었는데... 어떤 신부를 만난 뒤로는 세속의 쾌락을 완전히 거부했대. 마치 서약이라도 한 것처럼."),RandPhraseSimple(RandPhraseSimple("젠장할 검사 놈! 저자가 있는 동안엔 도시가 죽은 듯이 조용해. 장사도, 재미도 없어. 숨 쉬는 것조차 조심해야 할 판이야. 그리고 제일 무서운 게 뭔지 알아? 모든 항구가 똑같다는 거야. 마치 기계처럼 말이지. 국왕 폐하께서 일부러 우리 모두를 괴롭히려고 이런 고문을 만든 게 아닐까 싶다니까!","돈 페르난도가 고아원을 또 방문했소. 아낌없이 기부하고, 몇 시간씩 기도하오. 저런 훌륭한 분을 저 빌어먹을 횡령꾼들에게 본보기로 삼아야 하오!"),RandPhraseSimple("하! '성자' 페르난도 녀석이 또다시 모든 사창가를 닫아버렸군. 뭐, 신경 쓸 거 없어. 곧 떠나면 다시 열릴 테니까.","감... 감찰관이 도착했지, 그거야! 돈 페르난도 데 알메이다, 아니면 뭐더라, 알라미다! 얼마나 대단한 인물인지 총독님조차도 그 앞에서는 조심조심 걷는다더군. 그 사람이 네 눈을 들여다보면 네 모든 죄를 한 번에 꿰뚫어본다잖아. 무섭지!")));
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = PCharRepPhrase("난 그냥 네가 '마을'이라고 부르는 이 구멍에 대해 좀 물어보고 싶을 뿐이야.","이 마을에 대해 물어보고 싶은 게 있어.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("너한테 물어볼 게 있어.","정보가 좀 필요해.");
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
						link.l3 = RandPhraseSimple("재정 문제에 대해 상의하고 싶소.","재정에 관해서...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "이봐, 네가 좀 도와줄 수 있길 바란다. 내가 하나 사고 싶은데\n "+pchar.GenQuest.Device.Shipyarder.Type+", 그리고 이 물건이 당신네 마을에서 팔렸다고 들었소. 누군가가 거리에서 팔고 있었다는데, 혹시 아는 것 있소?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("알고 있나 ","알고 있소 ","들어봤나 ")+" 최근에 이 지역 교회가 도둑맞았다는 사실을 알고 있소?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("아, 너였군 "+GetFullName(Pchar)+" "+GetSexPhrase("- 오랜 친구야!","- 예쁜이!")+"","다시 만나서 반갑소, "+GetSexPhrase("오랜 친구여!","예쁜이!")+" "+Pchar.name,"오, 그게 바로 "+GetSexPhrase("선장 본인","직접 선장")+" "+GetFullName(Pchar))+RandPhraseSimple(". 너 죽은 줄 알았어!",". 그리고 어쩌면 "+GetSexPhrase("늘 그렇듯이 취했군.","조금 취했어."))+LinkRandPhrase(" 계속해, 뭐가 필요하지?"," 이번엔 또 뭐야?"," 또 귀찮게 구는 거야?"),LinkRandPhrase(TimeGreeting()+", 선장님 ","좋은 하루 되십시오, "+GetAddress_Form(NPChar)+" ","인사드립니다, 선장님 ")+GetFullName(Pchar)+LinkRandPhrase(". 무엇을 도와드릴까요 "+GetSexPhrase("그렇게 훌륭한 남자","그렇게 훌륭한 아가씨")+", 너 같은 사람?",". 왜 여기 있소?",". 이번에는 무엇을 알고 싶은가?")),PCharRepPhrase(LinkRandPhrase("안녕하세요, 선장님 ","안녕, 아, 너였구나 "+GetAddress_Form(NPChar)+" ","아, 선장님 ")+GetFullName(Pchar)+LinkRandPhrase(", 다시는 못 만날 줄 알았는데, 그리고",", 널 다시 봐서 기쁘다고는 안 하겠지만",", 아직도 살아 있구나, 유감이군, 그리고")+LinkRandPhrase(" 뭘 원하지?"," 여기 왜 왔어?"," 무엇을 도와드릴까요?"),LinkRandPhrase(TimeGreeting()+", 선장님 "+GetFullName(Pchar)+". 무엇을 도와드릴까요?","오, 저 사람이 선장이군 "+GetFullName(Pchar)+"! 무엇을 도와드릴까요?","안녕하세요, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". 뭐 필요한 거라도 있어?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("네 귀가 너를 속인 거야. 나는 가봐야 해.","아니, 별일 아니오, 그냥 선술집에 가던 길이었소."),RandPhraseSimple("그래, 알겠어. 행운을 빌지!","그냥 도시를 돌아다니는 중이오. 안녕히 가시오."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "질문 있나?";
			link.l1 = "이 서류에 적힌 이름이 당신에게 의미가 있소?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("나는 그런 종이쪼가리엔 신경도 안 써, 게다가 난 글도 못 읽어. 고리대금업자한테 가 봐, 그 양반이 글자 다룰 줄 안다더라, 하!","무슨 말씀인지 모르겠소, 다른 사람에게 물어보시오, 선장님"+GetFullName(Pchar)+".","어떻게 도와드려야 할지 모르겠습니다, 선장님 "+GetFullName(Pchar)+" 고리대금업자에게 한번 말 걸어 봐, 뭔가 알 수도 있어.");
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("거짓말하는 거 아니오, 선장 "+GetFullName(Pchar)+"?","그래서 뭐\n "+PChar.name+"?","나는 너를 기억할 거야, "+GetFullName(Pchar)+".")+" 이제 말해 봐, 뭘 원하는 거지?",LinkRandPhrase("만나서 반갑소, 선장님 "+PChar.name,"만나서 반갑군, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"반갑습니다, 선장님 "+PChar.name)+". 하지만 내 이름만 알고 싶었던 건 아니겠지?");
            link.l1 = PCharRepPhrase("네가 '마을'이라고 부르는 이 구린 곳에 대해 좀 물어보고 싶을 뿐이야.","이 마을에 대해 물어보고 싶은 게 있어.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("너에게 물어볼 게 있어.","정보가 좀 필요해.");
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
					link.l3 = RandPhraseSimple("재정 문제에 대해 상의하고 싶소.","재정에 관해서...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "이봐, 네가 나 좀 도와줄 수 있길 바란다. 나는 하나 사고 싶은데 "+pchar.GenQuest.Device.Shipyarder.Type+", 그리고 이 물건이 당신네 마을에서 팔렸다고 들었소. 누군가가 거리에서 팔고 있었다는데, 혹시 아는 게 있소?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("알고 있나 ","알고 있소 ","들어봤나 ")+" 최근에 이 지역 교회가 도둑맞았다는 소식 들었소?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("네 귀가 잘못 들린 거야. 나는 가봐야 해.","아니, 별일 아니오, 나는 선술집에 가던 중이었소."),RandPhraseSimple("뭐, 별거 아니야. 행운을 빌어!","그냥 도시를 돌아다니는 중이야. 안녕."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("아, 그리고 널 보니 술 한잔 하는 것만큼이나 반갑군. 원하는 거 뭐든 물어봐.","말하는 거 좋아하시오, 선장? 나도 그렇소... 특히 럼 한 잔 곁들이면 더 좋지.","그래, "+PChar.name+"?"),LinkRandPhrase("또 뭐 원하는 거야?","제가 받겠습니다, 선장님 "+PChar.name+", 말이 많다는 건가?")),PCharRepPhrase(LinkRandPhrase("또 뭘 원하지, "+GetAddress_Form(NPChar)+"?","듣고 있소, 선장님.","가야 하니, 빨리 물어보시오, 선장."),LinkRandPhrase("유쾌한 동무가 있어 늘 기쁘지. "+GetAddress_Form(NPChar)+" "+PChar.lastname+". 말해라.","그래, "+GetAddress_Form(NPChar)+"?","말하는 거 좋아하시오, 선장? 나도 그렇소... ")));
			link.l1 = LinkRandPhrase("이 마을에선 무슨 소문이 돌고 있지?","이 근처에 소식 있나?","육지 생활은 어떤가?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("길을 알려줄 수 있소?","어딘가로 가는 길을 못 찾겠어...","한 군데로 데려다줘...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("나는 사람들이 어떤 사람에 대해 뭐라고 말하는지 알고 싶어.","누군가에 대해 사람들이 뭐라고 하는지 아시오?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("현지인들에 대해 더 알고 싶어.","이곳 주민들에 대해 뭐든 아는 게 있소?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("네 귀가 너를 속였어. 나는 가봐야 해.","아니, 별일 아니야, 나는 선술집에 가는 길이야."),RandPhraseSimple("뭐, 별거 아니야. 행운을 빌어!","그냥 마을을 돌아다니는 중이야. 안녕."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "누구에게 관심이 있소?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "총독에 대해 더 알고 싶어.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "이 동네 선술집 주인에 대해 더 알고 싶어.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "이곳 조선소장에 대해 더 알고 싶어.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "이 지역 상점 주인에 대해 더 알고 싶어.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "별거 아니야. 신경 쓰지 마.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "흠, "+pchar.GenQuest.Device.Shipyarder.Type+"? 들어본 적 없어... 나 여기서 오래 살았지만 그런 건 한 번도 본 적 없어.";
			link.l1 = "그래, 그건 조선 도구야, "+pchar.GenQuest.Device.Shipyarder.Describe+". 그런 걸 이 마을에서 파는 사람을 본 적 있나? 아니면 누가 들고 다니는 걸 본 적이라도 있나?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "흠... 그래, 몇 시간 전에 그 물건을 가진 남자를 봤어. 거리를 따라 걷고 있었지. 꽤 흥미로운 도구였어.";
				link.l1 = "그 자는 어떻게 생겼고, 어디로 가고 있었지? 나한테 꼭 그런 정보가 필요하네.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "아니, 그런 건 본 적 없어.";
				link.l1 = "알겠어. 그럼 계속 물어볼게.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("아니, 나는 그 일에 대해 아무것도 몰라.","아니, 내가 가야겠어.","아무것도 몰라.");
					link.l1 = LinkRandPhrase("좋아, 고마워.","알겠습니다, 감사합니다.","알겠소, 실례하겠소.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("그건 나도 잘 모르겠어. 하지만 선술집 단골들에게 한번 물어봐, 분명히 더 많은 걸 알려줄 거야.","나는 아무것도 말해줄 수 없어, 선술집에서 다른 사람에게 물어봐.");
				link.l1 = "고맙다.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "선장님, 저는 '라고 불리는 식민지로 가야 합니다 "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", 가능한 한 빨리, 시작이야 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", 에서 "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". 여기 떠다니는 작은 배들에 비하면 당신 배가 훨씬 튼튼해 보이네요. 당신에게 돈을 지불할 수 있습니다 "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". 뭐라고 하겠나?";
			}
			else
			{
				dialog.text = "선장님, 식민지로 가야 합니다 "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", 그건 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", 에 "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". 이건 정말 위험하게 들릴 수 있다는 거 알아요, 하지만\n "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+" 너한테 좋은 도움이 되겠지?";
			}
			link.l1 = "흠. 나도 이쪽으로 가는 길이니, 이런 조건이라면 태워 줄 준비가 되어 있다네.";
			link.l1.go = "passenger_1";
			link.l2 = "미안하오,  "+GetAddress_FormToNPC(NPChar)+", 하지만 나는 다른 방향으로 항해 중이오. 도와줄 수 없소.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "안타깝군. 뭐, 다른 배를 기다리지. 잘 가.";
			link.l1 = "또 보자.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "좋아, 기다리는 것도 지겨워. 우리가 도착하면 네 보수를 줄 거야.";
			link.l1 = "내 배로 가라, "+GetAddress_FormToNPC(NPChar)+". 곧 떠날 거야.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "여기에 도착했군요, 훌륭합니다! 당신 배에서의 이번 항해는 꽤 만족스러웠소. 고맙소. 자, 돈을 받으시오, 나리.";
			link.l1 = "행운을 빌어, "+GetAddress_FormToNPC(NPChar)+"! 안녕히 가시오.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 마을 시민으로서 자네에게 검을 거두라고 부탁하네.","이봐, 이 마을 시민으로서 부탁하네, 검을 집어넣어 주게.");
				link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","말씀대로 하겠습니다...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"무기를 들고 뛰지 마라. 나까지 불안해지잖아...","나는 어떤 낯선 사람이 내 앞에서 칼을 뽑고 돌아다니는 게 마음에 안 들어...");
				link.l1 = RandPhraseSimple("알겠어.","걱정하지 마.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}
