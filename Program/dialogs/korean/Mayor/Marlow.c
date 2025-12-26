// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
int iMarlowTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 화났어, 꼬마야, 여기서 당장 꺼지는 게 좋을 거다...","미친 거 아니냐, 이놈. 몸 좀 풀고 싶었나? 기분 나쁘게 듣지 마라, 네가 여기 있을 자리는 아니야. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

			dialog.text = NPCStringReactionRepeat("나한테 할 말 있냐? 없어? 그럼 꺼져!",
						"내 말 알아들었지, 그만 귀찮게 해.","내가 분명히 말했는데도, 자꾸 성가시게 굴잖아!",
						"그래, 이 무례함에 슬슬 질린다.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나 이제 간다.",
						"그래, "+npchar.name+"...",
						"미안하다, "+npchar.name+"...",
						"아야...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "나는 샤크 도드슨을 찾고 있다. 마지막으로 그를 본 사람이 너라고 하던데. 좀 도와줄 수 있겠나?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "왜 이렇게 무례하게 구는 거지? 아니면 내가 가진 네가 원하는 책에는 관심이 없는 건가?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "네 죄수에 대해 얘기 좀 하자.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "안녕하세요, 목사님. 당신의 선교에 대해 이야기하고 싶소.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "네 죄수에 대해 얘기 좀 하자.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "스티븐 도드슨? 내 이야기가 네게 무슨 도움이 될지 모르겠군. 샤크는 지난 몇 달 동안 행방불명됐고, 아무도 그를 본 적이 없어. 뭐, 놀랄 일도 아니지. 그 자식이 블레이즈 샤프를 죽이고, 멍청한 짓으로 자기 이름까지 더럽혔으니까. 게다가 몇몇 힘 있는 코르세어들을 적으로 돌렸지.";
			link.l1 = "나는 샤크가 샤프의 죽음에 대해 결백하다고 믿을 만한 충분한 이유가 있다네. 내가 증명할 수는 없지만, 어쩌면 샤크 본인이 증명할 수 있을지도 모르지. 그에 대해 나한테 뭐라도 말해줄 생각 있나?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "몇 달 전에 스티븐이 내게 와서 아주 이상한 거래를 제안했지. 자기 프리깃 '포춘'을 한 달 동안 담보로 맡기고, 그 대가로 식량을 가득 실은 브리그 한 척을 달라는 거였어. 한 달 뒤에 브리그를 돌려주고 식량값을 치르든지, 아니면 내가 그의 프리깃을 가지게 되는 조건이었지. 한 달이 지났는데 샤크도, 내 브리그도, 돈도 전혀 소식이 없더군. 게다가 블레이즈가 살해당했고, 샤크가 용의자라는 소문까지 들었지. 내가 뭘 생각했겠어? 맞아! 스티븐이 최악의 상황에서 도망쳤다고 생각했지. 그래서 나는 그의 프리깃을 윌리엄 패터슨이라는 영국 놈에게 팔아넘겼어. 그 자식은 무척 좋아하면서 배값으로 두블룬을 산더미처럼 내놓더군. 덕분에 내 손해는 다 메꿨고, 스티븐한테 아무 원한도 없어. 샤프가 죽은 건 내 알 바 아니고, 나는 내 문제나 신경 써야 해.";
			link.l1 = "걔가 도망치고 싶었으면 네 브리그 따위 필요도 없었겠지? 자기 배가 있었고, 그 어떤 브리그보다 백 배는 나았어. 상어 녀석이 뭔가 계획이 있었던 것 같은데, 뭔가 꼬여서 제때 돌아오지 못한 거야.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "이미 말했듯이, 나는 Dodson의 문제 따위엔 관심 없어. 내 할 일은 이미 끝냈다. 그 배에 관해서라면, 왜 그 망할 브리그가 필요했는지 직접 그놈한테 물어봐. 내가 억지로 떠안기진 않았으니까.";
			link.l1 = "좋아, 더 이상 그 얘기는 하지 말자. 네 말이 맞아, 물론. 그런데 네 브리그에서 스티븐이 어디로 가고 있었는지 알고 있나?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "누가 확실히 알겠어. 하지만 나도 짐작은 있지. 그는 북서쪽, 메인 쪽으로 항해했어. 그러니 적대적인 인디언들로 유명한 페릴 만이거나, 아니면 교황파와 종교재판으로 악명 높은 누에바 에스파냐겠지.\n그가 이런 곳들로 갈 거라고는 의심스럽다. 하지만 쿠바 북서쪽에 '버려진 배들의 도시'라는 이상한 곳이 있다고들 하지. 많은 사람들이 그걸 신화라고 여기지만, 나는 아니야. 내가 로맨틱해서가 아니라, 실제로 거기까지 노를 저어간 사람들이 있었으니까. 적어도 예전에는 그랬지.";
			link.l1 = "그래서 그놈들이 누구지?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "쿠바에서 온 부커니어 놈들이다. 놈들은 바크에 소 사체를 실어 북서쪽으로 떠났지. 항상 조금 늦게 돌아오는데, 그때마다 주머니엔 돈이나 희귀하고 값진 물건이 가득했어.";
			link.l1 = "흥미롭군! 그 버커니어들은 어디서 찾을 수 있지?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "왜 나한테 묻는 거지? 쿠바 숲을 뒤져 봐. 설령 그놈들을 찾아낸다 해도 아무것도 안 알려줄 거다. 자기들 행운의 근원을 왜 남한테 밝히겠어? 그러니 시간 낭비하지 마라, 아무도 그놈들이 뭘 하는지 오래전에 본 적 없어.\n그리고 스페인 선원 알바라도가 직접 그 섬을 방문하고 쓴 기록이 있다는 얘기를 들었지. 그래서 궁금하군, 어쩌면 스티븐이 정말 거기로 항해했을지도 모르지.";
			link.l1 = "지도에 없는 미지의 섬이라... 흠. 그거 별로 희망적인 소식은 아니군.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "처음부터 내 얘기가 너한테 도움이 안 된다고 했잖아. 그리고 도드슨이 왜 필요하지?";
			link.l1 = "숲의 악마랑 나는 그를 해적 연맹의 두목으로 뽑고 싶다. 이미 말했듯이, 블레이즈가 누군가에게 살해당했다는 심각한 이유가 있다.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "헤! 얀 녀석이 저 자를 대신해서 나서는 거냐? 뭐, 법은 알겠지 - 도드슨은 각 바론한테서 표를 받아야 할 거다.";
			link.l1 = "나는 법을 안다. 두 번째 질문이다. 선거에서 도드슨에게 표를 줄 거냐?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "글쎄, 그 자가 먼저 돌아와야지. 사실, 그가 자기 일만 잘하고 나를 귀찮게 하지 않는다면 누가 해적단을 이끌든 상관없어. 말했듯이, 나도 내 문제로 바쁘거든. 우리 섬에 마녀랑 마법사가 몇 명이나 있는지 알아? 몰라? 내가 알려주지: 한 군단이나 돼! 게다가 산티아고랑 아바나에도 교황쟁이들이 잔뜩 있어.\n마법사 얘기가 나와서 말인데. '마녀를 위한 망치'라는 책이 있어. 난 그 책을 정말 갖고 싶어, 하지만 영어판만 필요해. 라틴어나 독일어, 스페인어 번역본은 필요 없어, 그런 언어는 모르거든. 그 책을 가져오면 도드슨에게 투표하지.\n잭맨도 그 책을 구해주겠다고 약속했으니까, 만약 그놈이 먼저 성공하면... 그땐 나한테 뭐라 하지 마라.";
			link.l1 = "좋아, 생각해 보지. 시간 내줘서 고맙다. 또 보자.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "책 말이냐? 네가 말하는 게 '마녀를 위한 망치' 그거지?";
			link.l1 = "당연하지. 네가 부탁한 대로 찾아냈다. 영어로 되어 있어.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "하, 이렇게 거칠게 맞이해서 미안하다, 친구. 다시는 안 그럴게... 그 신기한 걸 좀 보여줘!";
			link.l1 = "그래, 한번 봐.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "드디어다! 이제 벌벌 떨어라, 지옥의 하수인들아! 내 손이 더 이상 휘두를 수 없을 때까지 절대 가만두지 않겠다...";
			link.l1 = "기쁘군, 목사. 그래서, 표는 어떻게 할 건데?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "내가 말했듯이, '누가 우두머리가 되든 상관없다.' 스벤손이 형편없는 놈을 고르진 않겠지. 그러니 내 표를 가져가라. 마음대로 써. 여기 내 조각이다.";
			link.l1 = "고맙다, Zechariah. 거기서 보자!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 화났어, 꼬마야, 여기서 당장 꺼지는 게 좋을 거다...","미친 거 아니냐, 이놈. 몸 좀 풀고 싶었나? 기분 나쁘게 듣지 마라, 네가 여기 있을 자리는 아니야. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

			dialog.text = NPCStringReactionRepeat("나한테 할 말 있냐? 없어? 그럼 꺼져!",
						"내 말 알아들었지, 그만 귀찮게 해.","내가 분명히 말했는데도, 자꾸 성가시게 굴잖아!",
						"그래, 이 무례함에 슬슬 질린다.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나 이제 간다.",
						"그래, "+npchar.name+"...",
						"미안하다, "+npchar.name+"...",
						"아야...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "네 죄수에 관한 일이야.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "네 죄수에 관한 일이야.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "안녕하세요, 목사님, 당신의 임무 때문에 왔소.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "네가 죄수들과 관련된 일에 손을 대고 있다는 소문을 들었는데...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "하하. 내가 여기 죄수가 한 명뿐일 거라 생각하나? 이름 대봐.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". 그 자 여기 있나?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "그랬지. 내가 그를 바베이도스에서 온 그 플랜테이션 주인, 비숍 대령한테 팔아넘겼어 – 그가 여기 있었던 건 일주일 전이었지.";
				link.l1 = "젠장...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "아, 드디어 왔군. 난 그 녀석을 바베이도스의 플랜테이션 주인한테 팔까 생각하고 있었지, 그자가 일주일이나 이주일 안에 올 거거든... 몸값은 가져왔나?";
				link.l1 = "봐라, 약간 문제가 있어... 사실, 나 그렇게 많은 돈 없어. 하지만 일할 의지는 있지.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "그놈을 아직 안 팔아서 다행이군. 자, 네 돈이다 – 15만 페소. 그놈은 어디에 있지?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "너무 느렸군... 그리고 그 자식이 뭐가 그리 중요하지? 나는 그의 가족하고만 협상했어.";
			link.l1 = "여기 오라고 해서 왔다.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "그래, 너 늦었군. 내가 해줄 수 있는 건 없어.";
			link.l1 = "이봐, 그놈을 얼마에 팔았지, 비밀 아니라면?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "에이, 아니야. 하지만 말 안 해줄 거다... 말하면 네가 비웃을 테니까. 하하하하! 잘 가라.";
			link.l1 = "또 보자.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "그래, "+pchar.name+", 있잖아, 세상일이 그렇게 간단하지 않아. 돈 가지고 다시 오면 네 약골을 돌려주지, 하하.";
				link.l1 = "좋아. 또 보자.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "그래, 그래... 일이 좀 있지... 어디서부터 시작해야 할지 모르겠군. 선을 넘은 해적 하나를 바다에 수장시켜야 해.";
				link.l1 = "정글에서 그냥 죽이면 안 되나?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "장사는 그런 식으로 돌아가지 않아, 알겠어... 내가 그 자를 죽일 필요는 없어, 그냥 몇 놈한테 내 몫을 건드리면 어떻게 되는지 똑똑히 보여주면 돼. 그래도 그 자가 죽는다고 후회하진 않겠지.";
			link.l1 = "왜 네 놈 부하들을 직접 보내지 않지?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "흠... 그래, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 우리 은닉처 근처에 그들의 몫이 보관되어 있다고 몇몇 해적들을 설득했어\n "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". 그들의 두 척 배 '"+pchar.GenQuest.CaptainComission.ShipName1+"' 그리고 '"+pchar.GenQuest.CaptainComission.ShipName2+"'이 얼마 전에 닻을 올리고 항해를 떠났어 "+sLoc+". 이제 내가 왜 이 일은 내 부하들에게 맡길 수 없는지 알겠지?";
			link.l1 = "그래. 시간 얼마나 남았지?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12일에서 15일, 그 이상은 안 돼. 놈들이 은닉처에 도착하면 안 되거든, 귀한 화물을 싣고 있는데 가라앉혀 봤자 아무 소용 없지. 그런 경우라면 차라리 여기로 가져오게 하는 게 낫겠군...";
			link.l1 = "좋아, 나도 끼지. 놈들을 잡아보겠다.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "걱정하지 마라. 내 부하들이 그 놈을 네 배로 데려다 줄 거다. 그런데 넌 왜 그 놈을 신경 쓰는 거지?";
			link.l1 = "난 아니다. 그의 친척들이 나한테 그를 데려오라고 했지.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "아, 그거 괜찮군. 네 놈을 그렇게 헐값에 사려던 내가 좀 미안할 뻔했지. 하하하하. 잘 가라.";
			link.l1 = "또 보자.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "그래, , "+GetFullName(pchar)+", 내 놈들이 내 동료들을 침몰시켰나? 크크크...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "아니. 놈들을 잡지 못했다. 돌아오는 길에도 마주치지 못했지.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "내가 했다. 놈들은 상어밥으로 보냈지.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "젠장! 내가 그놈들을 만났든 안 만났든 이제 상관없어! 그리고 다음엔 뭘 제안할 건데?";
			link.l1 = "혹시 좀 더 쉬운 일 없냐?";
			link.l1.go = "CapComission4_1";
			link.l2 = "들어봐, "+NPChar.name+"...포로 값 좀 깎아라...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "아니.";
			link.l1 = "그럼 이만...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "값을 깎으라고?! 네놈들 무능함 때문에 내 물건 다 날렸잖아! 이제는 오히려 값을 올릴 수 있지! 원하면 20만 페소에 데려가든가, 아니면 당장 꺼져.";
			link.l1 = "너무 비싸군... 잘 있어라...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "젠장, 네 동전이나 가져가.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "이 약골은 네가 데려가도 돼...";
			link.l1 = "잘 가라.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "호호! 잘했군! 네 약골이나 데려가고, 행운을 빌지.";
			link.l1 = "고맙다. 잘 가라.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "몸값 가져왔나 "+GetSexPhrase("","라")+"? 내가 그 녀석을 플랜테이션 농장주들한테 팔겠다고 한 말, 농담 아니었어.";			
			link.l1 = "들어봐, "+NPChar.name+", 있잖아... 난 그런 돈 없어. 하지만 할 마음은 있어"+GetSexPhrase("","а")+" 처리해.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "그놈을 아직 팔지 않았다니 다행이군. 여기 네 돈이다 - 15만 페소. 그놈은 어디에 있지?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "돈 가져왔냐? 그 자를 플랜테이션에 팔겠다는 말, 농담 아니었어.";			
			link.l1 = "돈 없어, "+NPChar.name+", 하지만 지금 처리 중이다.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "그 자를 아직 팔지 않았다니 다행이군. 여기 네 돈이다 - 15만 페소다. 그놈은 어디에 있지?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "내가 뭘 하든 네가 왜 신경 쓰지? 이봐, 꺼지는 게 좋을 거다...";
			link.l1 = "쳇, 진정해라. 너랑 볼 일이 있다. 네가 잡아둔 죄수에 관한 거다.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "아, 좋아. 누구를 몸값 받고 풀어주길 원하지?";
			link.l1 = "기다려. 난 누구를 사러 온 게 아니고, 네놈한테 죄수 하나를 살 기회를 주러 왔다. 뭐, 그놈을 놓아주고 몸값도 챙길 수 있겠지.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "흠. 그런데 왜 내 도움이 필요한 거지? 왜 직접 돈을 챙기지 않는 거야?";
			link.l1 = "이건 나한테 꽤 위험한 일이야. 당국하고 문제가 생길 수도 있지.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "하... 좋아, 그럼 한번 보자. 네 포로가 누구냐?";
			link.l1 = "이거야 "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "그래... 네가 거짓말만 아니라면 공정한 거래겠지. 이놈에 대해선 값을 쳐줄 수 있겠다 "+iTemp+" 페소를 내거나, 아니면 흥미로운 정보를 내놓든가. 네가 선택해.";
			link.l1 = "페소나 챙기는 게 낫겠군. 이딴 장사는 이제 지긋지긋해...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "하! 더 말해 봐. 네가 나한테 흥미로운 얘기 하나쯤은 해주겠지.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "돈이면 되겠군. 가져가라. 이제 네 문제가 아니야. 팔 물건을 여기로 가져와.";
			link.l1 = "지금쯤이면 그 자식은 성문 근처에 있을 거야. 고맙다! 정말 큰 도움이 됐어.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "천만에, 더 가져와... 또 보자!";
			link.l1 = "행운을 빌지...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "똑똑한 놈이랑 거래하니 좋군. 이제 잘 들어라: 며칠 안에\n "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" 스페인 원정대가 본토에서 귀중한 물자를 싣고 올 거다. 그놈들은 화물을 실어갈 배를 기다릴 거야. 일주일 안에 도착하면 네가 그 화물을 차지할 기회가 있지.\n내가 너라면 벌써 내 배로 달려갔을 거다. 그리고 포로는 여기로 데려와.";
					link.l1 = "고맙다! 물건이면 내 고생에 딱 맞는 보상이겠지. 그리고 내 승객은 이미 마을 입구 근처에 있을 거다. 곧 네게 데려다 줄 거야.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "똑똑한 놈이랑 거래하는 건 괜찮지. 이제 잘 들어라: 대략 일주일 후에, 스페인 브리건틴 '"+pchar.GenQuest.Marginpassenger.ShipName1+"' 값진 물건을 실은 배가 출항할 거다 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" 에게 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". 서두르면 쉽게 잡을 수 있다.\n아직도 여기 있어? 내가 너라면 벌써 내 배로 갔을 거다. 그리고 죄수도 여기로 데려와.";
					link.l1 = "고맙군! 이 물건들이 내 수고에 대한 충분한 보상이 되겠지. 그리고 내 승객은 이미 마을 입구 근처에 있을 거다. 곧 네게 데려다 줄 거다.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("강도질이라니! 그건 용납 못 해! 각오해라, "+GetSexPhrase("놈","여자")+"...","이봐, 거기서 뭐 하는 거야, 이 자식아?! 나 털 수 있을 줄 알았냐? 이제 끝장이다...","잠깐, 이게 뭐야? 손 떼! 결국 도둑이었군! 여기서 끝이다, 이 자식아...");
			link.l1 = LinkRandPhrase("젠장!","카라암바!!","젠장!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("꺼져 ","꺼져")+" 여기서부터다!","내 집에서 꺼져!");
			link.l1 = "이런...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "시시한 말로 귀찮게 하지 마라. 다음엔 결과가 마음에 안 들 거다...";
        			link.l1 = "알겠어.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("끝났어, 말하지 마.","더 이상 너랑 얘기하고 싶지 않으니까, 귀찮게 하지 마라.");
			link.l1 = RandPhraseSimple("원하는 대로 해...","흠, 좋아...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "좀 더 예의를 갖추고 무례하게 굴지 않길 바란다?";
        			link.l1 = "확실히 하겠소, 목사님.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "문제를 해결하라고? 네가 무슨 짓을 저질렀는지 알기나 해? 어쨌든, 백만 페소를 가져와. 그러면 내가 놈들에게 네 짓을 잊으라고 설득해 주지. 그게 싫으면 지옥이나 꺼져.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "좋아, 돈 낼 준비 됐어.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "알겠다. 난 떠난다.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "좋아! 이제 다시 깨끗해졌다고 생각해라. 하지만 다시는 그런 역겨운 짓 하지 마라.";
			link.l1 = "안 해. 나한텐 너무 비싸. 잘 있어...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("오늘은 이미 그 얘길 했잖아.",
				                                      "내 말이 이해가 안 됐나?",
				                                      "너무 끈질기군.",
				                                      "더는 못 참겠다. 당장 꺼져!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("다음에 다시 이야기하지 뭐...",
				                                   "물론이지, "+npchar.name+"...",
				                                   "미안해, "+npchar.name+"...",
				                                   "아야...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "하! 우리 형제단이 널 괴롭히고 있나 보군, " + GetSexPhrase("친구", "아가씨") + "? 뭐, 잠시 동안은 그들을 진정시켜 줄 수 있지. 하지만 대가가 필요해. " + FindRussianDublonString(iBarbazonTotalTemp) + "만 내면, 그렇게 하지.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "좋아, 여기 네 돈이야.";
					else link.l0 = "어쩔 수 없지. 여기 있어.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "다음에 다시 올게...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "미쳤" + GetSexPhrase("니", "니") + "? 우리 녀석들은 널 마치 전염병처럼 피해 다녀. 그러니까 꺼지고 귀찮게 하지 마.";
				else
					dialog.text = "무슨 말이야, " + GetSexPhrase("친구", "아가씨") + "? 넌 골칫덩어리야 — 개들조차도 그걸 알아. 아무도 너랑 엮이고 싶어하지 않아.";
				link.l1 = "알겠어...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
