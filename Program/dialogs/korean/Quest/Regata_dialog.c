void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "안녕하시오. 그대가 선장인가 "+GetFullName(pchar)+"?";
			link.l1 = "그래, 나야. 그래서 뭐 어쩌라고?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "자메이카 총독 에드워드 도일리 나리께서 당신에게 보내신 편지가 있소.";
			link.l1 = "이런! 이럴 줄은 몰랐는데... 그리고 총독이 나한테 무슨 볼일이 있지?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "편지를 읽으시오, 나리. 간단히 말해, 당신은 군도 전체를 가로지르는 레가타, 즉 경주에 초대받았습니다.\n당신의 해상 실력과 놀라운 속도에 대한 소문이 이미 퍼졌습니다.";
			link.l1 = "믿을 수가 없군! 음, 나... 한번 생각해 보지.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "또한, 포트 로열 항구에 무료로 출입할 수 있도록 허가해 주겠소. 여기 30일간 유효한 허가증이 있소. 이제 내 임무는 끝났소. 안녕히 가시오, 선장.";
				link.l1 = "감사합니다. 면허장이 정말 반갑군요. 안녕히 가십시오!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "좋아. 이제 내 임무는 끝났어. 안녕히 계시오, 선장.";
				link.l1 = "잘 가라!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "좋은 하루요. 경주에 참가하는 거지?";
				link.l1 = "정확합니다, 나리. 제 이름은 "+GetFullName(pchar)+". 초대를 받았소.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "뭘 원하시오, 나리?";
				link.l1 = "아니, 아무것도 아니야. 난 이제 간다.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "만나서 반갑소, 선장 "+GetFullName(pchar)+". 그럼 시작하지. 편지에서 기본적인 내용은 이미 알지? 러거만 가능하고, 네 함대에 그 배 한 척만 있어야 레가타에 참가할 수 있어. 이 조건들 다 맞췄나?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "아직 아니야. 지금 할 테니 곧 돌아올게.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "그래, 있다.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "경주에 참가하러 왔다면서, 선장, 네 배는 어디 있지?";
				link.l1 = "실례합니다, 나리. 곧바로 제 배를 항구로 가져오겠습니다.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "아, 또 왔군. 레가타 조건을 다 충족했나?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "아직 아니야. 지금 할 테니 곧 돌아올게.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "그래, 있다.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "선장, 당신의 배가 정박한 걸 보기 전까지는 더 이상 할 얘기가 없어. 알아들었나, 아니면 다시 말해줘야겠나?";
					link.l1 = "실례합니다, 나리. 곧바로 제 배를 항구로 가져오겠습니다.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "뭐 필요한 거라도 있나, 나리?";
				link.l1 = "아니... 아무것도 아니야. 난 벌써 간다.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "좋아. 이제 다음 항목이다. 네 배 이름이 뭐지?";
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "영국 당국이 주최하고 규정이 정해져 있기 때문에, 대회 기간 동안 당신의 배 이름을 변경해야 하오. 걱정 마시오, 모든 참가자에게 해당되는 일이오.";
			link.l1 = "배 이름을 바꾸면 불운이 따른다고들 하지.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "경주가 끝나면 이름을 다시 바꿔도 된다네. 그러니 자네의 루거는 '성 캐서린'이라는 이름을 달게 될 걸세.";
			link.l1 = "알겠습니다, 나리. 이름을 바꾸겠습니다.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "이제 레가타 자체에 대해 이야기하자. 잘 들어라. 규칙이 적힌 종이도 줄 테니 참고해라.\n레가타는 포트 로얄에서 시작해서 포트 로얄에서 끝난다. 네가 도달해야 할 지점은 다섯 군데다.\n첫 번째는 포트 로얄에서 벨리즈, 웨스트 메인까지\n두 번째는 벨리즈에서 포르토프랭스, 히스파니올라까지\n세 번째는 포르토프랭스에서 세인트 존스, 앤티가까지\n네 번째는 세인트 존스에서 브리지타운, 바베이도스까지\n마지막은 브리지타운에서 포트 로얄까지다\n알겠나?";
			link.l1 = "명확합니다, 나리.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "훌륭하오. 다음 도시들 각각의 항구 사무소에 반드시 들러야 하오: 벨리즈, 포르토프랭스, 세인트 존스, 브리지타운. 이 도시들 중 하나라도 빠뜨리거나 정해진 순서를 어기면 실격이오\n경기 기간 동안 사무소는 24시간 열려 있을 것이니, 문을 두드리면 들어갈 수 있을 것이오.";
			link.l1 = "알겠소.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "함대를 변경하거나 함선 수를 늘리는 것은 금지되어 있다. \n이것은 모든 도시에서 확인될 것이니, 명심해라.";
			link.l1 = "생각해 보지. 보통 누가 이긴 걸로 치나, 그리고 상에 대해 이야기할 수 있겠나?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "레가타에서 승자는 단 한 명뿐이오. 포트 로얄에 가장 먼저 도착한 선장의 배가 이기지. 상품은 매우 귀중하오. 승자는 거액인 25만 페소를 받게 될 것이오. 또한 값진 선물 세트도 증정받게 되오.";
			link.l1 = "그래서, 진 놈들은 아무것도 못 받는 거야?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "맞아. 게다가 영국 식민지의 부자든 가난한 시민들이든 모두 레가타 우승자에게 돈을 걸지. 너도... 자기 자신에게 걸 수 있어. 보통 모든 선장들이 그렇게 하지. 네가 이기면 더 많은 돈을 벌 수 있고, 동기부여도 되지. 원래 내가 내기를 받아주고 있어. 네 승리에 걸겠나?";
			link.l1 = "하! 그래, 맞아. 얼마까지 걸 수 있는데?";
			link.l1.go = "Regata_rate";
			link.l2 = "생각해 보지. 어쩌면 내기라도 할까.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "생각해 봐. 레가타가 시작되기 전까지는 시간이 좀 있으니까.";
				link.l1 = "좋아. 언제 시작하지?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "생각해 봐. 레가타가 시작되기 전까지는 시간이 좀 있으니까.";
				link.l1 = "좋아.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "사흘 뒤, 정오 열두 시에. 부두로 와라, 늦지 말고. 경쟁자가 다섯 명 있을 거다.\n"+pchar.questTemp.Regata.AdversaryName.a+", 의 "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", 의 "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", 의 "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", 의 "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", 의 "+pchar.questTemp.Regata.AdversaryShipName.e+"\n전부 노련한 선장들이야. 뭐, 대충 이게 다인 것 같군. 혹시 모르니 규칙표도 가져가. 출발할 때 보자!";
			link.l1 = "안녕히 가십시오, 나리.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "잠깐! 영국과 프랑스 항구를 방문할 수 있는 30일짜리 허가증을 줄게. 레가타는 한 달 이상 가지 않을 거야. 자, 받아.";
			link.l1 = "고마워!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "얼마나 걸겠나?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "아직은 좀 더 생각할 시간이 필요한 것 같아.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "나리, 이건 재미도 없고 농담도 아닙니다. 그렇게 적은 돈으론 일하지 않겠습니다.";
				link.l1 = "실례지만... 판돈을 다시 생각해보자.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "나리, 레가타 규정상 그런 내기는 받아들일 수 없습니다. 합리적인 금액으로 줄이십시오.";
				link.l1 = "안타깝군. 금액을 다시 생각해 보자.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? 훌륭한 판돈이군. 받아들이지. 돈은 어디 있나, 나리?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "부디, 이것을 받아주십시오.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "지금은 돈이 충분하지 않아. 나중에 다시 올게, 그때 내기하자. 그리고 좀 더 생각해볼 테니, 금액을 다시 고려할지도 몰라.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "훌륭해! 이제 네가 가장 먼저 도착하기만 하면, 상은 네 것이야. 최종 상금은 달라질 수 있어. 결국 얼마나 많은 사람들이 네게 걸었느냐에 달렸으니까.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "알겠소. 레가타는 언제 시작하오?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "알겠어. 시작할 때까지 기다릴게. 또 보자!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "아, 또 오셨군요, 선장님 "+GetFullName(pchar)+"? 뭘 원하지?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "내 승리에 걸고 싶어.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "아니, 별일 아니야. 그냥 인사나 하려고 했지.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("선장, 처음이오? 조심해야 하오. 경쟁자들이 아주 불쾌한 놀라움을 준비하고 있을지도 모르니...","선장님, 나는 당신에게 내 운명을 걸었소. 실망시키지 마시오!","선장님, 레가타 항구의 현지인들이 뭔가를 팔겠다고 제안할 수도 있습니다. 종종 정말 쓸모 있는 것들이니, 참고하십시오."),LinkRandPhrase("안전한 항해 되시길, 선장님!","선장님, 조심하십시오. 카스티야 놈들이 스페인 해역을 항해하는 사람들의 루거선을 자주 사냥합니다.","어떤 수상한 놈들이 종종 레가타 선장들에게 자기 '서비스'를 제안한다는 소문을 들었어. 그 제안을 받아들일지 말지는 네가 결정할 일이야."));
			link.l1 = "그래, 그래, 물론이지... 고맙다고 해야겠군.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("선장님, 제 남편과 저는 당신의 승리에 만 달러를 걸었어요. 우리를 실망시키지 마세요! 당신을 위해 기도할게요!","선장님! 행운을 빕니다!","음... 당신은 정말 용감하고 대담한 선장이군요...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("이봐, 선원! 미인한테 손 한번 흔들어 봐! 네가 돌아오길 기다릴게!","이봐, 짠내 나는 선원! 마님이 이번 경주에서 이기는 사람한테 날 상으로 그냥 준다고 했어... 꼭 이겨 봐, 너 정말 잘생겼으니까!","돌아오면 꼭 들러, 잘생긴 친구. 우리가 최고의 방식으로 널 즐겁게 해줄 테니까!");
			link.l1 = "음, 하하... 생각해 볼게, 고마워!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "선장님, 레가타는 열두 시에 시작합니다. 지금은 쉬셔도 됩니다, 저희가 축제를 준비하고 있으니. 정오에 다시 오십시오, 경쟁자들도 그렇게 할 것입니다.";
				link.l1 = "알겠습니다, 나리! 시작을 기다리고 있겠습니다...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "여기 있습니다, 선장님.";
				link.l1 = "내 선원들과 나는 준비됐소, 나리! 신호만 기다리고 있소...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "자, 신사 여러분, 우리가 여기 모였소. 내가 지금부터 레가타를 시작한다고 선언하오. 규칙은 이미 알고 있겠지. 가장 먼저 이곳으로 돌아오는 사람이 우승자로 칭송받을 것이오. 숙녀 여러분과 신사 여러분, 우리 용감한 선장들에게 행운을 빌어줍시다!\n신사 여러분! 준비됐소? 준비! 대기! 출발!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "안녕하십니까, 선장님! 당신이 카리브 해역 레가타에 참가한다고 들었습니다.";
			link.l1 = "사실이오. 소문이 정말로 군도 전체에 바람보다 빠르게 퍼지는구려.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "그렇습니다, 선장님. 제안이 하나 있습니다. 당신의 배와 레가타에 관한 일이오.";
			link.l1 = "헤! 흥미로운데. 듣고 있지, 나리.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "루거선에 딱 맞는 완벽한 돛이 한 벌 있소. 가장 좋은 면으로 만들었지. 이 돛을 달면 배의 가속이 빨라지고, 상대보다 시간을 벌 수 있을 거요\n원한다면 당신에게 팔 준비가 되어 있소. 물론, 살 생각이 있다면 말이오.";
			link.l1 = "이 돛들, 얼마에 팔 생각이냐?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "고작 15,000페소야. 이런... 상황치고는 아주 적당한 값이라고 인정해야지.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "동의하오. 나는 내 러거선에 쓸 새 돛을 사는 중이오. 자, 돈을 받으시오, 나리. 내가 체크인하는 동안 내 배로 돛을 가져다줄 수 있겠소?";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "나한테 그런 돈 없어. 그러니까 네 돛을 살 수 없겠군.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "알겠습니다, 나리. 제 부하들은 신호만 기다리고 있습니다. 약속드리건대, 후회하지 않으실 겁니다. 게다가 이 돛은 파란색으로 멋지게 칠해져 있지요. 당신의 미인도 분명히 마음에 들어 할 겁니다.";
			link.l1 = "좋아! 그럼, 나는 가야 하니까 너는 돛을 맡아.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "안타깝군. 뭐, 그건 네 선택이지. 잘 가라, 선장.";
			link.l1 = "잘 가라!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "안녕하세요, 선장님 "+GetFullName(pchar)+"... 당신과 얘기 좀 해야겠소... 사실, 그냥... 사업 제안이오.";
			link.l1 = "흠. 흥미로운데, 그런데 네가 내가 누군지 어떻게 아는 거지?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "뭐라고 할까, 예전부터 내가 재능 있다고들 했지... 하하, 자, 레가타가 한창인데 너도 참가하고 있잖아, 넌 유명한 선장이니까!";
			link.l1 = "알겠다. 자, 할 말 있으면 해봐.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "우리는 당신 앞에 한 명의 참가자가 더 있다는 것을 알고 있습니다 - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" ~의 "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". 그는 얼마 전에 항구를 떠났고, 곧 고나이브 곶을 지나 항해할 거야.";
			}
			else
			{
				dialog.text = "우리는 당신 바로 뒤에 참가자가 한 명 더 있다는 걸 알고 있소 - "+pchar.questTemp.Regata.AdversaryName.b+" ~의 "+pchar.questTemp.Regata.AdversaryShipName.b+". 그는 몇 시간 후에 여기 올 거야.";
			}
			link.l1 = "흠... 너 제법 잘 알고 있구나.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "물론이지. 이제 본론으로 들어가자. 우리는 네 돈을 받고 도움을 주겠다. 우리 배에서 가져온 대포 네 문을 고나이브 만 뒤쪽 곶에 배치해 뒀다. 어떤 경주 배든 그 곶을 돌아야 하지.\n대포에는 쇠사슬탄을 장전해 두었다. 우리가 거래를 하면, 내 대포 친구들에게 네 경쟁자의 돛을 박살내라고 지시할 거다. 그러면 그 놈은 돛을 고치느라 시간 낭비하게 될 거야. "+sTemp+".";
			link.l1 = "이 일에 얼마를 원하지?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "아니. 나는 그런 방법으로 이기지 않을 거야. 넌 나를 잘못 봤어. 작별이오, 신사 여러분.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "그래, 선장님, 선택은 당신 몫이오. 잘 가시오.";
			link.l1 = "곶에 대한 정보 고맙다. 그 근처는 멀리 떨어져 다니겠다.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "별거 없어. 단지 "+iTemp+" 페소지. 그리고 네 경쟁자 중 한 명은... 사고 때문에 거의 이틀을 날릴 거야, 하하!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "헤헤! 네 말이 맞아, 친구! 내가 돈을 내지. 하지만 네가 제대로 일을 할 거란 보장은 뭐지? 그리고 내가 곶을 지나갈 때 내 배에 대고 총을 쏘지 않을 거란 보장은 또 뭐고?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "나한텐 그런 돈 없어. 그러니까 네 서비스를 쓸 수 없겠군.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "선장님, 제발요, 우리는 밀수꾼이지 해적이 아닙니다. 우리 모두 나름대로는 정직한 사람들이오... 선장님도 전에 우리 서비스를 이용해 본 적 있지 않으십니까? 제 말을 믿으셔도 됩니다. 믿고 맡기십시오.";
			link.l1 = "좋아, 알겠다, 돈 가져가라.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "이 거래, 분명히 만족하실 겁니다, 선장님. 그리고 곧바로 내 포수들에게도 알리겠소. 행운을 빕니다!";
			link.l1 = "너도 마찬가지야...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "좋은 하루구나, 아들아. 너를 맞이하며 겸손히 묻고 싶구나. 영국과 우리 위대한 주님의 충실한 종으로서 본당 금고에 헌금할 생각이 있느냐?";
			link.l1 = "신부님, 사람들은 영혼이 시켜서 자선을 베푸는 것이지, 강요받아서 하는 게 아닙니다. 이제는 군도에 있는 모두가 레가타의 선장들을 털기로 마음먹은 것 같다는 생각이 들기 시작하네요...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "물론이지, 신부님. 얼마나 드리면 되겠소?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "네 소원과 형편이 허락하는 만큼만 내거라, 아들아. 우리 교구는 아주 작은 금액이라도 고맙게 여길 것이다.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "이런 태도는 옳지 않다, 아들아. 우리 모두 죄를 지었으니, 네 영혼을 잊지 마라. 언젠가 우리 창조주 앞에 서야 할 것이니... 어쩌면 머지않아 그럴지도 모른다.";
				link.l1 = "네 설교는 필요 없어, 신부님. 잘 있어.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "우리 본당과 나는 이 소박한 선물에 감사드립니다.";
				link.l1 = "어서 오십시오, 신부님.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "우리 교구와 나는 이 선물에 감사하네. 그리고 아들아, 몇몇 죄 많은 자들이 그대를 해치려 한다는 것을 경고하고 싶네. 바다에서 조심하게!";
				link.l1 = "신부님, 매일 누군가가 저를 해치려고 음모를 꾸미고 있습니다... 그래도 제 운명을 걱정해 주셔서 감사합니다.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "우리 본당을 대표하여 이 귀중한 선물에 감사드립니다. 답례로, 정말 사악한 자들이 당신을 해치려 음모를 꾸미고 있다는 경고를 드리고 싶소. 이 악독한 배교자들이 바로 이 항구에서 당신의 배를 침몰시키려 한다는 소문을 들었소\n그들은 이미 이 악행을 위해 화약으로 가득 찬 배까지 준비해 두었소. 조심하거라, 아들아, 이 타락한 영혼들은 정말로 사악한 의도를 품고 있단다... 신의 가호가 함께하길!";
				link.l1 = "감사합니다, 신부님. 주의하겠습니다.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "너무 관대하구나, 아들아. 하나님의 겸손한 종으로서 교회를 위해 네가 내어주려는 모든 돈을 받을 수는 없단다. 1만 페소만 받겠네\n대신 경고 하나 하겠네. 사악한 자들이 너를 해치려고 음모를 꾸미고 있네. 그 비열한 배교자들이 바로 이 항구에서 네 배를 침몰시키려 한다는 소문을 들었네\n그들은 화약으로 가득 찬 루거선 한 척을 준비했는데, 이름은 '"+pchar.questTemp.Regata.BranderName+"', 그녀는 의심을 사지 않으려고 영국 깃발 아래 항해하고 있다. 조심하거라, 아들아, 이 타락한 영혼들은 사악한 의도를 진심으로 품고 있느니라.\n그들을 처단하거라, 이 죄에 대한 사면을 내리노라. 축복이 있기를! 기도하겠다, 아들아.'";
				link.l1 = "감사합니다, 신부님. 저 놈들이 감히 못된 짓이라도 하면, 내가 곧장 지옥으로 보내버리겠습니다!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "화내지 마라, 아들아. 분노는 죄이니라. 자선을 하지 않는 것도 네 권리다. 평안히 가거라, 아들아.";
			link.l1 = "안녕히 계십시오, 신부님.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "안녕하십니까, 선장님! 제 이름은 "+npchar.name+" 그리고 나는...";
			link.l1 = "... 나에게 뭔가를 제안하려는 거지... 맞나, 아가씨?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "물론이지, 선장! 그런데 왜 그렇게 놀라는 거야? 너는 잘생긴 선원이자 레가타에 참가하고 있으니, 다들 너한테 쓸만한 해상 물품을 기꺼이 팔려고 하지.";
			link.l1 = "좋아, 미인아, 네 말이 맞아. 나한테 뭐 줄 건데?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "여기, 한번 봐. 이건 아버지에게서 물려받은 거야. 아버지도 너처럼 뱃사람이었고, 항해 도구도 많이 가지고 계셨지. 나는 필요 없으니, 네게 분명 쓸모가 있을 거야. 내가 바라는 건 단 하나야\n "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" 그걸 위해서.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "그래, 그래..."+sTemp+"! 흥미로운데! 내가 말하는데, 네 예쁜 눈을 위해 내가 그걸 사주지. 그래서, 너는\n "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" 그 값으로? 자, 돈을 가져가시오.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "흠..."+sTemp+"아니, 아가씨, 미안하지만 난 필요 없어. 이미 내 멋진 망원경이 있거든. 그러니... 유감이야!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "감사합니다, 선장님. 잘 쓰시길 바랍니다. 유용하게 쓰셨다니 기쁩니다. 레가타에서 행운을 빕니다!";
			link.l1 = "감사합니다, "+npchar.name+"! 잘 가라.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "안타깝군요, 선장님. 당신에게 도움이 될 거라 기대했는데. 뭐, 다른 사람에게 팔아보도록 하지. 안녕히 가시오!";
			link.l1 = "안녕히 가십시오, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "안녕하시오, 선장. 자네, 혹시 레가타 참가자 아니오? 내가 맞게 짚은 건가?";
			link.l1 = "그래. 그런데 무슨 일이지, 경관?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "우리 식민지가 이미 스페인군의 포위 공격을 받고 있다는 사실은 알고 계실 겁니다.\n그래서 우리 총독께서 당신과 이야기하고 싶어 하십니다.\n부디 총독을 한 번 찾아뵈어 주시겠습니까? 일이 매우 급합니다.";
			link.l1 = "흠... 알겠소, 곧바로 각하를 뵈러 가겠소. 다만 내가 군사 작전에 어떻게 연루될 수 있는지는 잘 모르겠군.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "당신도 연루됐소, 선장. 시간 낭비 말고 관저로 가십시다. 나를 따라오시오.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "나리! 민간인들을 당신 배로 보내도록 준비됐습니다. 지금 출발합니까?";
			link.l1 = "그래, 물론이지. 우리는 곧바로 출항할 거다. 사람들에게 장선에 타라고 전해라.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "해냈어... 이 슬루프는 분명 전대의 정찰선이었고, 저 카스티야 놈들이 주변을 기웃거리고 있었던 것 같아. 선장님, 제발 여자들을 동굴로 옮기는 걸 도와주십시오. 아직 더 많은 스페인 분견대가 있을 가능성이 있습니다.";
			link.l1 = "좋아. 가자!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "도움을 주셔서 감사하오, 선장님! 당신과 당신의 용기가 아니었다면... 당신은 진정한 영웅이오. 모든 위험과 자신의 이익에도 불구하고 이 작전을 완수했으니. 어떻게 보답해야 할지 고민했소... 그리고 레가타에서 당신의 승산을 높일 방법이 있소.";
			link.l1 = "흥미롭군. 그런데 그 방법이 뭐지?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "안녕하십니까, 선장님 "+GetFullName(pchar)+". 와 주어서 다행이오. 우리 마을이 그대의 도움이 필요하오.";
			link.l1 = "나리, 지금 당신 식민지를 공격하고 있는 스페인 함대에 대해 말씀하신다면, 제가 어떻게 도와드릴 수 있을지 전혀 모르겠습니다. 저는 전열함이 아니라 러거선의 선장일 뿐이오...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "내 말 잘 들어, 선장. 그러면 이해할 거야. 우리 지금 큰일이야. 도시가 스페인군에게 포위당했어. 요새를 두고 결정적인 전투가 곧 벌어질 거다. 게다가 이미 수백 명의 스페인군이 상륙해서 도시의 모든 출구를 막아버렸지. 이제 그들은 바다와 육지 양쪽에서 우리를 공격할 수 있어\n요새 주둔군은 함대의 공격에 맞서 도시를 방어할 준비를 하고 있지만, 정작 정착지 안에는 병력이 부족해. 무기를 다룰 수 있는 남자들은 모두 동원됐지만, 나머지는 어쩌지?\n브리지타운에는 여자만 백 명이 넘게 있어. 우리가 식민지를 지키지 못하면 그들에게 무슨 일이 닥칠지 상상할 수 있겠나? 자네라면 이해할 거라 믿네.";
			link.l1 = "나리, 말씀은 이해하오. 하지만 다시 묻겠소, 내가 어떻게 도울 수 있겠소? 내게 무엇을 원하시오? 전열함과 싸우라는 것이오, 아니면 내 선원들을 마을 민병대에 들이란 말이오?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "아니오. 나는 단 한 가지만 부탁하오. 당신의 배로 여기 있는 여자들과 아이들을 데려가 주시오. 그리 많지 않소, 대략 백 명쯤 되오. 마호니 중위와 함께 해리슨 곶으로 데려가 주시오. 그가 동굴에서 그들이 안전하게 있도록 할 것이오\n스페인 놈들이 그들을 찾으러 오지는 않을 거라 확신하오. 나는 남은 배가 없소; 우리가 가진 모든 배는 스페인 함대에게 침몰당했소. 당신이 내 마지막 희망이오. 비록 배가 과적되겠지만, 한 번에 곶까지 데려갈 수 있을 것이오. 전열함들은 당신을 따라오지 않을 거요.\n이 일을 부탁할 다른 사람이 없소. "+sTemp+"";
			link.l1 = "나리, 죄송하지만 제 배는 이미 너무 과적되어 있어서 두 번 왕복한다 해도 그 많은 사람을 태울 수 없습니다.\n근처에 아무 포탄이라도 떨어지면 제 배와 당신의 여자들은 바다 밑으로 가라앉게 될 겁니다.\n용서하십시오만, 도와드릴 수 없습니다.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "알겠소, 나리. 도와드리겠소. 선원의 명예가 나를 그렇게 하게 하오.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "동의해 주셔서 기쁩니다. 당신은 진정한 군인입니다. 마호니 중위가 여자들과 아이들을 당신 배로 데려올 것입니다. 행운을 빕니다, 선장님!";
			link.l1 = "감사합니다, 나리. 시간 낭비하지 맙시다!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "서두르시오, 선장님. 시간이 얼마 남지 않았소.";
			link.l1 = "나는 이미 항해 중이야!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "이건 믿을 수가 없군. 시도조차 안 하겠다는 건가? 뭐, 그건 네 권리지. 내가 너한테 뭘 요구할 수도 없지. 네가 그냥 평범한 선장이었다면 백 명의 여인을 위해 네 배를 압수했겠지만, 넌 지금 레가타에 참가 중이니 영국 식민지 총독의 보호를 받고 있지\n양심이 널 이기길 바랐는데, 내가 틀렸군. 가라, 그리고 신의 자비가 네 영혼에 있기를!";
			link.l1 = "안녕히 가십시오, 나리.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "스페인 놈들이 우리를 눈치챘어! 신이시여, 도와주소서!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "마호니 중위가 죽었어... 이건 악몽이겠지. 그는 용감한 장교였어. 선장님, 우리를 동굴로 데려다 주시겠소? 거기까지만 데려다 주시면 우린 알아서 하겠소.";
			link.l1 = "알겠어. 따라와!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "여기 도착했군요... 고마워요, 선장님! 당신 덕분에 우리 모두가 살았어요! 어떻게 보답해야 할지 생각해 봤는데... 레가타에서 승산을 높일 방법이 있어요.";
			link.l1 = "계속해.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "포트 로얄로 가는 중인가? 가장 짧은 길은 퀴라소를 거치는 거야. 브리지타운으로 돌아가. 우드로 도허티라는 남자를 찾아. 그는 노련한 선원이자 경험 많은 항해사야. 바베이도스와 자메이카 사이 지역을 완벽하게 알고 있으니, 네게 큰 도움이 될 거다\n이렇게 하면 네가 승리하는 데 절실히 필요한 소중한 시간을 많이 아낄 수 있을 거야. 그 남자를 현지 교회에서 찾아가서 이렇게 전해라 "+GetFullName(npchar)+" - 그가 너를 보냈으니, 널 내치지 않을 거야. 그를 포트 로얄로 데려가. 어차피 거기로 갈 생각이었으니까.";
			link.l1 = "좋아! 훌륭한 항해사는 내게 쓸모가 있지. 잘 가라.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "안녕히 가시오, 선장님! 행운을 빕니다!";
			link.l1 = "어쩌면, 우리 다시 만날지도 모르겠군...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "안녕하세요. 뭐 필요하십니까?";
			link.l1 = "네 이름이 Woodrow Dougherty 맞지?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "맞아요. 무엇을 도와드릴까요?";
			link.l1 = "나는 그대가 노련한 항해사이며 바베이도스와 퀴라소 사이의 바다를 잘 안다는 것을 알고 있소. 또한 그대가 포트 로열에 가고 싶어 한다는 것도 알고 있지. 나는 이번 레가타의 참가자이며 마지막 정거장은 바로 포트 로열이오. 마지막 항해에 항해사로 내 선원에 합류해 주길 부탁하고 싶소.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "재미있군... 그런데 내가 왜 네 선원으로 들어가야 한다고 생각하지?";
			link.l1 = "음, 내가 당신에 대해 들었거든 "+pchar.questTemp.Regata.Name+" 네가 거절하지 못할 모든 보증과 함께 말이야. 그리고 내가 이 중대한 순간에 브리지타운을 도운 덕분에...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "From "+pchar.questTemp.Regata.Name+"? 이제 알겠소, 물론이지. 좋아, 선장님, 포트 로열까지 가장 빠른 항로로 안내해 드리겠소. 지금 출항하실 건가요?";
				link.l1 = "그래.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? 그렇군요. 하지만, 선장님, 이렇게 위험한 시기에 제 도시를 떠날 수는 없습니다. 우리에게 사심 없는 도움을 준 군인으로서 저를 이해해 주셔야 합니다\n사람들이 제 등 뒤에서 늙은 우드로우가 스페인과의 마지막 전투 앞에서 도망쳤다고 수군거리는 건 원치 않습니다. 저는 남겠습니다. 미워하지 마십시오, 선장님.";
				link.l1 = "이게 마지막 대답인가? 하지만 내가 너희 식민지를 도왔는데...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "그럼 시간 낭비하지 말자. 짐만 챙기고 바로 네가 시키는 대로 하겠다.";
			link.l1 = "내 선원들이 부두에서 기다리고 있다가 너를 '세인트 캐서린'호로 데려갈 거야. 고마워, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "선장, 레가타는 스포츠일 뿐이지만, 내 고향을 포위한 스페인군은 생사가 걸린 문제요. 나는 당신과 어디도 가지 않을 거요. 그리고 다시 한 번 말하겠소, 내 말을 이해해야 하오 – 이 세상에는 아직도 명예와 의무가 의미를 가지오. 이것이 내 마지막 말이니, 바꿀 생각 없소. 하지만, 가장 안전한 길로 빨리 가는 방법에 대해 조언은 해줄 수 있소: 북서쪽 도미니카를 향해 항해하시오, 거기서 마르티니크나 과들루프로 가면 되오, 당신과 바람이 결정하는 대로. 그 다음 포트 로열로 바로 가거나, 큐라소를 경유할 수도 있소 – 나는 추천하지 않지만 – 네덜란드인들과 사이가 좋다면 그렇게 하시오.";
			link.l1 = "음, 고맙군... 하지만 실망이야. 잘 가라, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "경기 마지막 단계에서 레가타 규칙을 어겼소. 결과는 실격 처리됐소. 더 이상 할 말 없네, 선장.";
				link.l1 = "에이... 젠장! 뭐, 어쩔 수 없지, 네가 너무 눈치가 빨랐으니까. 잘 가라!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Captain "+GetFullName(pchar)+", 축하하오! 걸린 시간은 "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" 네가 레가타를 마치기까지 몇 시간 남지 않았는데, 모든 상대를 멀찌감치 따돌렸구나. 정말 대단한 결과다!";
					link.l1 = "친절한 말씀 감사합니다, 나리!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "선장님, 유감스럽게도 결과가 최악입니다, 당신은 이미 써버렸군요 "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" 시간이야. 너무 슬퍼하지 마, 정말 강한 상대들이었잖아.";
						link.l1 = "나는 슬프지 않소, 나리. 내가 레가타에 참가해서 내 실력을 시험해 본 것이 기쁘오.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "선장님, 당신은 지금 "+n+"번째 장소입니다. 성공적인 결과를 축하합니다, 훌륭한 기록을 보여주셨군요 - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" 몇 시간. 손실에도 불구하고 축하하오!";
						link.l1 = "괜찮습니다, 나리. 이런 치열한 경쟁에서 좋은 결과를 보여드릴 수 있어 기쁩니다.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "나리, 한 가지 여쭤봐도 되겠습니까 - 배가 어디 있습니까? 보이지 않는데요...";
			link.l1 = "죄송합니다, 나리. 제가 그녀를 곧바로 항구로 데려가겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "내일 총독에게 찾아가면 25만 페소와 귀중한 선물을 받을 수 있을 거야. "+sTemp+" 마을을 떠나지 마시오. 전통에 따르면, 일주일 안에 우승자가 상을 받지 않으면 그 상은 마을 금고로 들어가게 되어 있소.";
			link.l1 = "알겠습니다, 나리. 내일 그를 찾아가겠습니다!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "고결한 대답을 들으니 기쁘군. 행운을 빌겠소, 선장!";
			link.l1 = "안녕히 가십시오, 나리.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "다른 거 필요한가, 선장?";
			link.l1 = "아니... 아무것도 아니야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "아, 거기 있었군요, 나리 "+GetFullName(pchar)+". 만나서 반갑소. 상을 받으러 왔나? 준비되어 있소.";
			link.l1 = "그거 듣기 좋군! 내 추가 보상의 크기는 얼마지?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "모든 것을 감안하면, 당신의 최종 보상은 "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". 자, 받아요. 축하합니다!";
			link.l1 = "고마워!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "물론이오, 포트 로얄 시민들 사이에서 그대의 인기가 높아졌소. 그대도 느낄 수 있을 것이오... 하지만 유감스럽게도, 사람들의 기억은 짧소. 그러니 이 영광이 아직 찬란할 때 마음껏 누리시오!";
			link.l1 = "가장 훌륭한 것들에 대해 이야기하고 있군, 나리... 좋아, 영광 속에 몸을 담그는 게 어떤지 한번 보자고. 잘 가라! 즐거웠다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "승리를 축하합니다, 선장님! 훌륭한 결과군요!";
						link.l1 = "고마워!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "슬퍼하지 마시오, 선장님. 레가타에서 우승하는 건 결코 쉬운 일이 아니오; 참가하는 것만으로도 영광이오!";
						link.l1 = "나에 대해 걱정하지 마. 내 성과에 만족하고 있으니까.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "뵙게 되어 반갑습니다, 선장님! 스티븐슨 나리에게 가서 등록부터 하셔야 합니다.";
					link.l1 = "알겠소. 지금 그에게 가는 중이오!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "아, 선장님, 어떻게 그렇게 실패할 수가 있습니까, 그것도 마지막 단계에서!";
				link.l1 = "그래, 내가 참 어리석었지...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "승리를 축하합니다, 선장님! 훌륭한 결과군요!";
						link.l1 = "감사합니다!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "슬퍼하지 마시오, 선장님. 레가타에서 이기는 건 결코 쉬운 일이 아니오; 참가하는 것만으로도 영광이지!";
						link.l1 = "나에 대해 걱정하지 마. 내 결과에 만족하고 있으니까.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "만나서 반갑습니다, 선장님! 스티븐슨 나리에게 가서 등록부터 하셔야 합니다.";
					link.l1 = "알겠어. 지금 가는 중이야!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "아, 선장님, 어째서 그렇게 실패하셨소, 그것도 마지막 단계에서!";
				link.l1 = "그래, 내가 정말 멍청했지...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "승리를 축하합니다, 선장님! 훌륭한 결과군요!";
						link.l1 = "고마워!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "슬퍼하지 마시오, 선장님. 레가타에서 이기는 건 쉽지 않으니, 참가하는 것만으로도 영광이오!";
						link.l1 = "나에 대해 걱정하지 마. 내 결과에 만족하고 있으니까.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "만나서 반갑습니다, 선장님! 스티븐슨 나리와 이야기해서 등록부터 하셔야 합니다.";
					link.l1 = "알겠소. 지금 가는 중이오!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "아, 선장님, 어떻게 그렇게 실패할 수가 있습니까, 그것도 마지막 단계에서!";
				link.l1 = "그래, 내가 참 어리석었지...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
