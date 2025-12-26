// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "휴... 정말 끔찍한 기후군... 내 이름은 "+GetFullName(npchar)+", 그리고 이 신께 버림받은 섬들에서 내가 최고의 조선공이 아니면 신이 나를 벌하시길. 하지만 이 습기는 정말 나를 녹초로 만드는군...";
				Link.l1 = pcharrepphrase("천 마리 상어라니, 내가 딱 필요했던 게 늙은이의 중얼거림이라니. 내 이름은 "+GetFullName(pchar)+", 내 소문은 들었겠지.","습기 때문이 아니라 나이 탓이오, 나리. 내 이름은 "+GetFullName(pchar)+", 내 소문은 들었겠지.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "아, 또 당신이군, 맨날 자기 문제만 늘어놓고... (기침하며).";
				link.l1 = pcharrepphrase("맞아, 또 나야. 하지만 아직 신께 영혼을 바치지 않은 김에 일 얘기나 하자고.","기억력이 좋으시군요. 이제 괜찮으시다면, 좀 더 구체적인 질문으로 들어가겠습니다.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("네 투덜거림에 질렸어. 이만 가라.","이제 가봐야겠소. 귀찮게 해서 미안하오");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "아하, 선장님 "+GetFullName(pchar)+"! 들러 줘서 정말 반갑구나!";
				Link.l1 = "뭔가 내 도움이 필요한 것 같군, 안 그래? 평소엔 그렇게 공손하지 않잖아.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "빈손으로 다시 돌아왔군, 선장! 그... 손님들은 어떻게 된 거지?";
				Link.l1 = "그들은 갔어. 내가 물어봤고, 그들은 떠났지.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "아, 또 당신이군, 맨날 자기 문제만 들먹이고... (콜록콜록)";
			link.l1 = pcharrepphrase("맞아, 또 나야. 하지만 아직 신께 영혼을 바치지 않았다면, 일 얘기나 하자.","기억력이 좋으시군요. 이제 허락하신다면, 좀 더 구체적인 질문으로 들어가겠습니다.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("네 투덜거림에 질렸어. 잘 가라.","이제 가봐야겠소. 귀찮게 해서 미안하오.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "요즘 젊은 것들 말이야... 예의라고는 눈곱만큼도 없구만. 머리는 뜨겁고 손은 거칠고, 도대체 뭐 하러 온 거냐?";
			link.l1 = pcharrepphrase("그래, 맞아. 하지만 언젠가는 모든 것이 끝나기 마련이지, 그리고 네 시간도 곧 다가오는 것 같군...","뭔가 느낌이 오는데, 젊었을 때도 꼭 어른들한테 존경심이 많았던 건 아니었던 것 같은데? 내가 맞지?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "어른들한테 말대꾸하지 마라, 꼬맹이.";
			link.l1 = pcharrepphrase("진정하게. 흥분하지 말고. 너무 무리하지 마, 괜히 심장마비라도 오면 곤란하니까. 내가 카리브 최고의 조선공을 죽게 했다는 소문 듣긴 싫거든. 이제 본론으로 들어가자.","네 무례함은 나이가 있으니 봐주겠소. 이제 할 말 다 했으면, 본론으로 들어가세.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("좋아, 내 잔소리는 이쯤에서 끝내지! 잘 가라!","우리가 서로 뜻이 맞지 않는 것 같군. 잘 가라.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(콜록콜록)... 사람들은 늙은이 좀 내버려 두질 않는구먼. 이번엔 나한테 뭘 원하는 거냐, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("조선소의 서비스를 이용해야겠소.","조선소의 서비스를 이용하고 싶소.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "질문이 있소.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "재정에 대해 이야기하고 싶소.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("젠장, 급한 일이 몇 가지 있어서 가봐야겠다. 잘 있어라.","이제 가야겠어. 미안하다.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			dialog.Text = "어서, 뭐 원하는 거냐? 늙은이 귀찮게 하지 마라...";
			link.l2 = "난 그냥 조선소의 서비스를 이용하고 싶을 뿐이야.";
			link.l2.go = "shipyard";
			link.l3 = "배에 쓸 무기가 필요하다.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "내 돛의 외형을 바꾸고 싶어.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "내 배는 꽤... 특별하지. 몇 가지 수정을 하고 싶어.";
					link.l50.go = "FDM";
			}
			/*if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_cabin") && npchar.quest.FDM_cabin == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "선실 복구를 위해 상자를 더 가져왔소.";
					link.l50.go = "FDM_cabin_pay";
			}*/
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "배 수리 건으로 왔소.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "배 수리 건으로 왔소.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("젠장, 급한 일이 좀 있어서 가봐야겠다, 안녕.","이제 가야겠어. 미안해.");
			Link.l9.go = "ship_tunning_not_now";
		break;	
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했지...","내 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없어.","질문이 왜 이렇게 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","음, 글쎄...","좋아, 그럼...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "이봐, 나 좀 지나가고 싶은데, 저 문이 잠겨 있네...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "거래를 제안하고 싶소.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "프리깃함 자재 때문에 왔소.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "들어봐, "+npchar.name+", 요즘 Isla Tesoro에서 Miguel Dichoso를 본 적 있나?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "조건을 말해라.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "진정한 왕의 관대함이군! 물론 동의하지!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "아니, 그렇게 생각하지 않아.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "맞아. 이 문을 통과하고 싶으면 나한테 2만 페소를 내야 해. 돈 안 내면 문 안 열어줄 거야. 여긴 자선소가 아니거든. 그리고 어차피 거기 가는 건 추천하지 않아. 안 가는 게 너한테 더 나을 거야...\n";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "여기 돈이다. 문 열어.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "나는 그만한 돈이 없어.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "말도 안 돼! 내가 문값을 낼 리 없지.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "들어가. 문 열려 있어. 고맙다는 말은 필요 없어!";
			link.l1 = "아니, 왜 안 되겠소. 고맙소. "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "그래, 그걸 구하면 다시 오라구. 아니면 나를 설득하려 들지 마. 소용없으니까...";
			link.l1 = "아으, 완전히 말이 안 나오는군!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "자, 너무 엄격하게 굴지 마시오, 늙은이한테... 정말로 당신의 도움이 필요하오, 선장.";
			link.l1 = "말해 보시오, 주인장. 무슨 일이 있었소?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "우리 해적 연맹의 새 지도자, "+sTotalTemp+", 새 배, 즉 프리깃을 주문했소. 게다가 꽤 까다로운 조건도 내걸었지. 강화된 선체, 높은 속도와 우수한 기동성, 그리고 가능한 한 가장 큰 구경의 대포까지\n제독의 배, 아니, 형제단의 수장의 배라면 특별해야 한다는 건 이해하오. 하지만 그러려면 특별한 재료가 필요하오. 당신도 들어봤을 거요. 철목, 송진, 선박용 비단, 그리고 밧줄...";
			link.l1 = "그럼 이 말을 해적단의 우두머리에게 전하지 그래. 아니면 네가 걱정되는 건가\n "+sTotalTemp+" 그 일로 네 목이 잘릴 수도 있겠지?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "내가 그에게 말했지... 문제는, 우리 새 지도자에게는 그 재료들을 찾고 가져올 시간도 여유도 없다는 거야. 그게 얼마나 귀한 건지 알아야 해. 그리고 그 재료 없이는 말씀하신 조건의 프리깃함을 절대 만들 수 없어.";
			link.l1 = "그리고 내가 배에 쓸 자재도 직접 구해오길 바라는 거요?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "그래, 맞아. 너는 우리 우두머리의 좋은 친구지. "+sTotalTemp+" 자신이 당신에게 큰 빚을 졌다고 하면서 당신이 모든 존경을 받을 자격이 있다고 하더군요... 그래서 생각했지요. 당신이 그의 친구라면, 그를 좀 도와주는 게 괜찮지 않겠냐고요? 그리고 동시에, 내가 얼마나 곤란한 처지에 있는지 이해하시겠죠? 모든 자재비는 지급될 겁니다,\n "+sTotalTemp+" 자기 금화를 아끼지 않는 놈이지.";
			link.l1 = "정말 죄송합니다, 나리, 저도 그 못지않게 바쁩니다만 "+sTotalTemp+". 재료를 모으는 데 영원히 걸릴지도 모르겠군. 그러니 다른 사람에게 부탁하는 게 좋겠어.";
			link.l1.go = "clock_exit";
			link.l2 = "글쎄, 만약\n "+sTotalTemp+" 당신에게 배를 주문했으니, 당연히 도와주려고 하지. 우리는 정말 친구니까, 친구끼리는 서로 도와야 하잖아. 자재가 얼마나 필요하지?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "정말 안타깝군. 정말 유감이야. 나는 너를 믿고 있었는데. 뭐, 거절은 거절이지...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "철목 100단위, 송진 150통, 선박용 비단 110필, 삼줄 90타래가 부족하네. 어떻게 생각하나? 넉 달 안에 이 모든 걸 구해줄 수 있겠나? 더 이상 시간은 없는 것 같네.";
			link.l1 = "적어도 시도는 해볼 수 있지. 그런데 보수는 어떻게 하지?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "내 요금은 이렇소: 철목은 한 조각에 4000페소, 수지는 한 통에 1400페소, 비단은 한 필에 2500페소, 밧줄은 한 타래에 1500페소라네. 그리고 이 모든 걸 나에게 가져오면, 아주 좋은 선물을 줄 것이오.";
			link.l1 = "무엇일까, 궁금하군?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "먼저 자재부터 가져오시오. 하지만 장담하는데, 이건 분명히 자네에게 쓸모가 있을 거요, 그리고 이건 유일무이한 물건이오. 카리브 해는 물론이고, 세상 어디에도 아직 이런 건 없지. 자네의 호기심이 조금이라도 자극되어 내게 자재를 모아줄 마음이 생겼길 바라오.";
			link.l1 = "그래, 주인장, 너 정말 요물 같구나! 좋아, 거래 성사다.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "매우 기쁩니다. 당신이 돌아오기를 기다리겠습니다.";
			link.l1 = "너무 오래 걸리지 않길 바라는데...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "훌륭하군! 오늘은 뭘 가져왔나?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "철목, 수량: "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "송진, 수량: "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "선박용 비단, 수량은 "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "삼베 밧줄, 수량은 "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "지금은 아무 일도 없소. 다만 우리 계약이 여전히 유효한지 확인하고 싶었을 뿐이오.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "훌륭하군! 필요한 자재는 전부 모였어. 정말 고마워, 선장. 네 덕분에 큰 도움 받았어.";
				link.l1 = "예, 언제든지요, 주인님. 저도 꽤 기쁩니다. 친구를 도와주고 좋은 돈도 벌었으니까요. 이제, 당신이 약속한 그 신비한 물건에 대한 이야기로 돌아가 봅시다.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "또 무슨 놀라운 일이 있나, 선장?";
				link.l1 = "아쉽지만, 지금은 여기까지요. 그냥 계속 기다리시오.";
				link.l1.go = "exit";
				link.l2 = "그래, 한 가지 더 있지...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "좋아, 알겠어. 나는 필요해 "+FindRussianQtyString(amount)+" 철목으로군. 네가 나에게 가져왔구나 "+FindRussianQtyString(iSan)+". . 그러니까, 이제 나한테 가져올 게 남은 건 "+FindRussianQtyString(iTemp)+". 좋아, 한 척당 4,000페소로 계산해서 보상금은 총 "+FindRussianMoneyString(iSum)+". 자, 가져가시오.";
				link.l1 = "고마워! 나머지도 곧 줄게.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "좋아, 알겠다. 나도 필요해\n "+FindRussianQtyString(amount)+"  철목으로군. 네가 나에게 가져왔구나 "+FindRussianQtyString(iSan)+". 자, 이제 철목 문제는 해결됐군! 좋아, 한 조각당 4000페소씩 계산해서, 네 보상은 총 "+FindRussianMoneyString(iSum)+". 자, 받아가시오.";
				link.l1 = "감사합니다!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "좋아, 알겠어. 나도 필요해\n "+FindRussianQtyString(amount)+" 수지군. 네가 가져왔구나 "+FindRussianQtyString(iOil)+". 그러니 이제 네가 나한테 가져올 것은 "+FindRussianQtyString(iTemp)+". 좋아, 컨테이너당 1400페소 기준으로 보상금은 총 "+FindRussianMoneyString(iSum)+". 자, 가져가시오.";
				link.l1 = "고마워! 나머지도 곧 줄게.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "좋아, 알겠어. 나도 필요해\n "+FindRussianQtyString(amount)+" 송진이군. 나에게 가져왔구나 "+FindRussianQtyString(iOil)+". 자, 이제 송진 처리는 끝났군! 좋아, 컨테이너당 1400페소로 계산해서, 네 보상은 총 "+FindRussianMoneyString(iSum)+". 자, 받아가시오.";
				link.l1 = "감사합니다!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "좋아, 알겠어. 나도 필요해\n "+FindRussianQtyString(amount)+" 비단이군. 나한테 가져왔구나 "+FindRussianQtyString(iSil)+". 그러니 이제 네가 나한테 가져올 것은 "+FindRussianQtyString(iTemp)+". 좋아, 한 척당 2,600페소씩 계산해서, 네 보상은 총 "+FindRussianMoneyString(iSum)+". 자, 가져가시오.";
				link.l1 = "고마워! 나머지도 곧 줄게.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "좋아, 알겠어. 나도 필요해\n "+FindRussianQtyString(amount)+" 비단이군. 네가 가져왔구나 "+FindRussianQtyString(iSil)+". 자, 이제 비단 문제는 해결됐군! 그러니 한 조각당 2600페소씩 계산해서, 당신의 보상은 총 "+FindRussianMoneyString(iSum)+". 자, 이것을 가져가시오.";
				link.l1 = "감사합니다!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "좋아, 알겠어. 나도 필요해\n "+FindRussianQtyString(amount)+" 밧줄이군. 네가 가져왔구나 "+FindRussianQtyString(iRop)+". 그러니 아직 나한테 가져와야 할 것은 "+FindRussianQtyString(iTemp)+". 그러니 한 척당 1500페소로 계산해서, 당신의 보상 총액은 "+FindRussianMoneyString(iSum)+". 자, 가져가시오.";
				link.l1 = "고마워! 나머지도 곧 줄게.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "좋아, 알겠어. 내가 필요로 하는 건 "+FindRussianQtyString(amount)+" 밧줄이군. 네가 가져왔구나 "+FindRussianQtyString(iRop)+". 자, 밧줄은 이미 처리했소. 좋아, 한 개당 1500페소씩 계산해서, 당신의 보상은 총 "+FindRussianMoneyString(iSum)+". 자, 가져가시오.";
				link.l1 = "감사합니다!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "그래, 그래... 내 일 말이지, 물론이지. 음-음-음... 흠... 어디에 뒀더라... 아아...";
			link.l1 = "무슨 일이십니까, 주인장? 꽤 걱정스러워 보이시네요. 무슨 문제라도 있습니까? 무슨 곤란한 일이라도 생겼나요?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "정확히 그렇소. 문제들이 있지. 최근에 생긴 문제들이오. 젠장할 보물 사냥꾼들...";
			link.l1 = "진정하게, 진정하게. 그 나이에 그렇게 걱정하면 몸에 안 좋아. 자칫하면 하늘나라 갈 수도 있지 않겠어. 그럼 해적단 우두머리의 프리깃을 누가 만들어 주겠나? 진정하고, 설명해 봐. 그 보물 사냥꾼들이 누구지?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "저기 내 탁자 옆에 문이 있지. 그 문은 곧장 오래된 금고로 이어져. 그 금고 안, 보물 상자들 중 하나에 내가 금속 상자를 보관하고 있어. 그 상자 안에는 이십 년 전 그 빌어먹을 소용돌이에 휘말려 이곳에 오게 됐을 때 내 곁에 있던 물건들이 들어 있지...\n";
			link.l1 = "무슨 깔때기? 무슨 소리를 하는 거야?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "아, 내 잡담을 용서하게. 나이 드는 게 쉽지 않구나, 젊은이. 미안하네. 하지만 그건 중요한 게 아니야. 중요한 건, 자네를 위한 선물이 담긴 상자가 지금 지하 감옥에 있는 궤짝 안에 있다는 거지. 그 감옥엔 지금 악당들이 들어와 있네. 우리 사람들도 아니고, Isla Tesoro 출신도 아니야.\n보물 사냥꾼들이지—누가 이곳에 보물이 많다고 귀띔이라도 해줬나 보네. 겁이 많아서 여기 얼굴도 못 내밀 텐데, 내가 직접 가보기엔 너무 두렵구나, 알겠나? 그놈들 얼굴이...";
			link.l1 = "알겠소. 문을 열어. 네 집에 들이닥친 불청객들을 내가 쫓아내주지.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "그렇게 그냥? 혼자서 그놈들을 쫓아내겠다고? 두렵지 않아? 부탁만 하면 우리 정착지 전체가 널 위해 싸워줄 텐데...";
			link.l1 = "말은 그만하고 행동이나 해, 주인장. 이 문 열고 나머지는 나한테 맡겨. 네 물건은 어느 상자에 넣어뒀지?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "복도 끝에는 텅 빈 나무통들이 잔뜩 쌓여 있네. 그 뒤, 구석진 바닥에 작은 궤짝이 하나 있지. 내가 자물쇠를 박아놔서, 침입자들이 그걸 찾아낸다 해도 더러운 손으로 열진 못할 거야. 자, 여기 열쇠를 가져가.";
			link.l1 = "미리 생각해 줘서 기쁘군. 여기서 기다리고 아무 데도 가지 마.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "그냥 당신 말만 듣고 떠났다고?";
			link.l1 = "맞아요. 그 녀석들, 의외로 꽤 예의 바르더군요. 내가 그들에게 당신 같은 명망 높은 노련한 조선공이 겁을 먹고 있다고 설명했더니, 연배를 존중해서 조용히 자리를 떴소. 이제 걱정 말고 내려가도 됩니다.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "아하, 늙은이를 놀리는군! 좋아. 내 상자를 가져오면 열어서 네가 정당하게 얻은 장치를 주겠다.";
			link.l1 = "제발, 가져가시오...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "고맙소! 자, 열어봅시다. 여기, 이걸 받으시오. 자동 기계식 타이머요—이런 장치는 이곳에서 아무도 만들지 못하고 앞으로 삼백 년 동안도 못 만들 거요... 아, 미안하오, 늙은이의 실례를 용서하시오. 내 말은, 이 물건이 그만큼 특별하다는 거요.\n이 타이머는 알아서 모든 일을 해주니, 멍청한 모래시계 따위는 필요 없소. 오차도 없지! 다만, 충격이나 물에만 조심해서 보관하시오, 잃어버릴 테니. 원숭이도 쓸 수 있을 만큼 쉬운 타이머요.";
			link.l1 = "이것 좀 봐! 내 평생 이런 기적은 처음이야! 감사합니다, 주인님.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "천만에. 이제 언제든 정확한 시간을 알 수 있을 거야. 어디서 구했냐고 묻지 마. 절대 안 알려줄 거니까.";
			link.l1 = "모두들 비밀 하나쯤은 있지, 그렇지 않소, 나리? 좋아... 비밀은 지키시오, 내가 괜히 캐묻진 않겠소. 선물 고맙소!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "도와주셔서 감사합니다, 선장님. 가끔 들러 주십시오. 늙은 조선공을 잊지 마시고요.";
			link.l1 = "널 어떻게 잊겠어... 아무튼, 꼭 그렇게 할게, 명장 Alexus. 잘 가!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "아하, 미겔! 내 오랜 지인이지. 기억나네. 그는 사소한 것까지 계속 물어봤었지. 하지만 간단한 전신기도 본 적 없는 그에게 라디오 내부 구조를 어떻게 설명하란 말인가?";
			link.l1 = "뭐?.. 무슨 말씀이십니까, 주인장?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "아, 미안하구나, 젊은이. 내 말은 너무 신경 쓰지 마라... 우리 호기심 많은 미셸이 궁금증을 풀고는 사라져버렸지. 불과 사흘 전에만 해도 같이 이야기했었는데.";
			link.l1 = "실례가 안 된다면, 지금 미겔은 어디 있소?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "누가 알겠어. 샤프타운에서 자기 일이나 보고 있을 수도 있고, 아니면 이미 이슬라 테소로에서 떠났을 수도 있지.";
			link.l1 = "알겠습니다. 감사합니다, 주인님!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "또 그 '유령선' 이야기냐... 알아둬라, 나는 그게 언젠가 쓸 만한 배로 바뀔 거라는 희망으로만 손대는 거다. 아니면 아예 건드리지도 않았지. 바다에 있는 놈들 다 비슷하게 생각할 거다. 이번엔 그 배로 뭘 하려고?";
			else	
				dialog.text = "아, 그 '유령선' 말이군! 엄마들이 말 안 듣는 아이들 겁줄 때 네 갈레온을 쓴다더라. 그런데도 그 빌어먹을 배를 침몰시키지 않고 남겨두기로 했구나! 뱃사람들은 네 배가 수평선에 나타나기만 해도 벌벌 떤다지... 그래서, 그 배로 뭘 할 생각이냐?";
			/*if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "겁먹은 작은 겁쟁이들이란 생각은 맘에 드는데, 내부를 보니 우울해지네. 선실 봤어? 관 같아. 곰팡이랑 먼지투성이야. 고치고 싶어. 할 수 있겠어, 장인?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "이 찢어진 검은 누더기들, 이제 진절머리가 나. 인정하지, 바람은 일반 돛만큼이나 잘 받긴 해. 하지만 이 꼴이란... 역겹지. 난 평범한 새하얀 돛이 갖고 싶어. 같이 할 건가, 대장장이?";
				link.l2.go = "FDM_sails";
			}*/
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "그래, 이제 이 배를 제대로 된 배로 바꿀 때가 온 것 같아. 배는 좋고, 선원들도 익숙해졌지만, 어른들도 기겁할 만한 이런 배를 타고 다니는 건 존경받는 선장으로서 체면이 안 서지. 아이들은 말할 것도 없고 말이야. 완전히 새롭게 개조해서, 내 배를 본 다른 선장들이 십자가를 긋는 대신 부러워하게 만들고 싶어. 이런 일이라면 군도 최고의 조선공인 자네에게 맡기는 게 당연하지 않겠나?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "왜 안 되겠어? 내 손은 아직도 흔들림 없으니까.";
			link.l1 = "...";
			link.l1.go = "FDM_cabin_s";
			//link.l2 = "지나친 사치는 필요 없어. 기준만 지켜.";
			//link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "좋소. 더블룬 열 상자면 다섯 날 안에 끝내주지.";
			link.l1 = "거래 성사!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "상자 열 개? 1,500 두블룬? 흠, 그런 지출은 좀 생각해볼 시간이 필요하군...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "도블론 일곱 상자면 다섯 날 안에 끝내주지.";
			link.l1 = "거래 성사!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "상자 일곱 개? 두블룬이 천 개가 넘는다고? 흠, 그런 지출은 좀 생각할 시간이 필요하군...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "좋아, 돈을 기다리고 있겠다.";
			if (iTemp > 0)
			{
				link.l1 = "내게 상자가 있네. 어디 보자. 자, 여기, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "난 가서 상자에 동전을 넣어야 해.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin.chest = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "좋소, 나는 대금을 기다리겠소.";
			if (iTemp > 0)
			{
				link.l1 = "내게 상자들이 있네. 어디 보자. 자, 여기, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "난 가서 상자에 동전을 넣어야 해.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin.chest)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin.chest));
				dialog.text = "그래서 나한테 데려와야 했군 "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" 네가 가져온 궤짝들 "+FindRussianQtyString(iTemp)+". 내가 대금을 준비했어. 이제 내 차례야. 가서 좀 돌아다녀. 걱정 마, 최선을 다할 테니까.";
				link.l1 = "좋군...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "그래서 나한테 데려와야 했군 "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" 상자들, 네가 가져왔군 "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" 상자가 남았다.";
				link.l1 = "알겠습니다, 주인장.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin.chest = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
			npchar.quest.FDM_cabin = "done";
		break;
		
		case "FDM_sails":
			dialog.text = "물론이지, 내가 해줄 수 있어! 자, 자... 이 말은 더러운 낡은 천은 전부 버리고 새로 깨끗한 면 돛을 달아야 한다는 뜻이군. 할 일이 아주 많아. 인건비랑 자재비로 10만 페소야. 어때, 거래할래?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "그래, 나 그거 괜찮아. 거래 성사다!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "흠. 생각 좀 해봐야겠군...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "좋아. 돈은 받았으니 이제 내 일만 하면 돼. 일이 끝날 때까지 돌아다니면서 신경 쓰지 마.";
			link.l1 = "좋군...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "그래, 드디어 그런 말을 듣게 되어 반갑군. 그리고 사실이야 - 자네는 괜찮은 녀석 같아 보이지만, 도대체 무슨 배를 타고 다니는 건지 알 수가 없군. 하지만 미리 경고해두지, 이 일은 몇 시간 만에 끝날 일이 아니고, 돈도 꽤나 들 거야. ";
			link.l1 = "좋아, 좀 더 구체적으로 말해줄 수 있겠나?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "좋아, 계산해 보자... 선체를 완전히 재건하려면 바카우트, 밧줄, 선박용 비단, 송진 각각 150단위씩과 금 더블룬 10,000개가 필요해. 그렇게 쳐다보지 마, 대부분의 돈은 자재비로 들어가니까. 이 일은 배를 완전히 분해해서 처음부터 다시 짓는 거나 마찬가지야.";
			link.l1 = "아니, 그렇게 생각하지 않아. 그만큼 자원을 가져오고 재건을 위해 금덩이를 넘길 준비는 안 됐어. 지금 가진 걸로 만족하겠어.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "에이, 우리 배를 위해서라면 못할 게 없지... 좋아, 거래하자.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "좋아, 말은 그만하고 행동으로 옮기자고. 내가 필요한 걸 다 사려면 네가 돈을 가져와야 해. 돈을 받으면 자재를 가져오기 시작해도 돼. 그러면 네 배 작업에 들어가겠다.";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l1 = "그래, 돈은 문제 없어. 지금 가지고 있지. 자, 여기 있어, 주인장.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "지금은 그런 돈이 없어. 조금만 기다려, 내가 가져올게.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			RemoveDublonsFromPCharTotal(10000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "해적 정착지에서 그렇게 많은 돈을 들고 다니는 게 두렵지 않아, 헤헤? 농담이야, 여기 있는 사람들 다 자기 나름대로는 정직한 사람들이지. 이제 자재만 기다리고 있어. 다시 말하지만, 총 150개의 철목, 150타의 밧줄, 150필의 선박용 비단, 150통의 송진을 가져와야 해.";
			link.l1 = "버텨, 내가 자재 가져다줄게.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "아주 좋아! 오늘은 뭘 가져왔나?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "철목 \n "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 150)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "수지, 수량: "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 150)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "비단을 다음 수량만큼 선적하시오 "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 150)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "밧줄 수량 "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "아직 아무것도 없어. 그냥 거래가 아직 유효한지 확인하고 싶었을 뿐이야.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 149 && sti(npchar.quest.FDMshipsilk) > 149 && sti(npchar.quest.FDMropes) > 149)
			{
				dialog.text = "훌륭하군! 모든 자재가 제대로 확인됐소. 이제 그 괴물을 내가 맡겠소. 드디어 제대로 된 모습을 갖추게 되겠군.";
				link.l1 = "알겠소, 이제 그만 투덜대시오, 주인장. 결과를 손꼽아 기다리고 있소.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "내 기분을 더 좋게 해줄 만한 게 또 있나, 선장?";
				link.l1 = "아쉽지만, 지금은 이게 전부요.";
				link.l1.go = "exit";
				link.l2 = "그래, 너한테 줄 게 또 있어...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "보자... 내가 필요한 건 "+FindRussianQtyString(amount)+" 철목으로 만든 것. 네가 가져왔군 "+FindRussianQtyString(iSan)+". 철목이오. 그러니 아직도 나에게 가져와야 하오 "+FindRussianQtyString(iTemp)+".";
				link.l1 = "고마워! 나머지도 곧 가져다줄게.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "보자... 아직 필요한 게 있어 "+FindRussianQtyString(amount)+" 철목으로 만든 것이군. 네가 나에게 가져왔구나  "+FindRussianQtyString(iSan)+"그러므로, 이제 철목은 끝이오!";
				link.l1 = "고마워!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 150 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "보자... 나는 필요하다 "+FindRussianQtyString(amount)+" 송진을. 당신이 가져왔군 "+FindRussianQtyString(iOil)+"그러므로, 너는 아직도 나에게 가져와야 해 "+FindRussianQtyString(iTemp)+".";
				link.l1 = "고마워! 나머지도 곧 가져다줄게.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "보자... 아직 필요한 게 있어 "+FindRussianQtyString(amount)+" 송진을. 네가 가져왔군 "+FindRussianQtyString(iOil)+"그러므로, 이제 송진 일은 끝났소!";
				link.l1 = "고마워!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 150 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "보자... 나는 필요하다 "+FindRussianQtyString(amount)+" 배의 비단을. 당신이 가져왔군 "+FindRussianQtyString(iSil)+". 그러므로 아직 나에게 가져와야 하오 "+FindRussianQtyString(iTemp)+".";
				link.l1 = "고마워! 나머지도 곧 가져다줄게";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "자, 어디 보자... 아직 필요한 게 있어 "+FindRussianQtyString(amount)+" 배 견직물의. 그러니 아직도 나에게 가져와야 해\n "+FindRussianQtyString(iSil)+"그러므로, 이제 선박용 비단 일은 끝났소";
				link.l1 = "고마워!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 150 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "보자... 내가 필요한 것은 "+FindRussianQtyString(amount)+" 밧줄 말이오. 당신이 가져왔군 "+FindRussianQtyString(iRop)+"그러므로, 아직도 나에게 가져와야 해 "+FindRussianQtyString(iTemp)+".";
				link.l1 = "고마워! 나머지도 곧 가져다줄게";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "보자... 내가 필요한 것은  "+FindRussianQtyString(amount)+" 밧줄 말이오. 당신이 가져왔군 "+FindRussianQtyString(iRop)+"그러므로, 밧줄 일은 끝났소!";
				link.l1 = "고마워!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "그래, 돈 가져왔나\n";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l2 = "그래, 가져왔지. 약속한 대로 무게를 다 갖춘 두블룬 1만 개야.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "아직 아니오, 잠시만 기다리시오, 주인장.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			
			shTo = &RealShips[sti(pchar.Ship.Type)];
			object newShip;
			aref arTuning;
			CopyAttributes(&newShip, shTo);
			
			pchar.Ship.Type = GenerateShipExt(SHIP_RENOVATED_FDM, 0, pchar);
			
			if(CheckAttribute(newShip, "Tuning"))
			{
				makearef(arTuning, newShip.tuning);
				for (int iQty = 0; iQty < GetAttributesNum(arTuning); iQty++)
				{
					aref realTuning = GetAttributeN(arTuning, iQty);
					string tuningName = GetAttributeName(realTuning);
					UpgradeShipParameter(pchar, tuningName);
				}
			}
			if(CheckAttribute(newShip, "Traits")) RealShips[sti(pchar.Ship.Type)].Traits = newShip.Traits;
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			pchar.ship.hp = GetCharacterShipMaxHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
			Achievment_Set("ach_CL_178");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
