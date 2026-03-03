void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "버그입니다. 알려주십시오.";
			link.l1 = "그래!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "안녕하시오, 선장... 음... 크흠! 젠장할 광산들... 내 소개를 하지. 아담 레이너라 하오. 나는 평범한 사내라 쓸데없는 서론은 싫으니 바로 말하지. 돈 좀 벌고 싶나? 자네와 나, 둘 중 누구도 혼자서는 못할 작은 장사를 제안하겠소.";
			link.l1 = "헤! 돈 좀 되는 일인가? 흥미롭군. 듣고 있지, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "있잖아, 미안한데 너는 믿음이 안 가. 그래서 거래는 안 하겠어.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "믿을 만하냐고? 하하! 사람은 얼굴만 보고 판단하는 게 아니지. 뭐, 됐다. 너는 쉽게 돈 벌 기회를 방금 놓친 거야. 더 협조적인 놈을 내가 찾아보지...";
			link.l1 = "우리 대화는 끝났소, 나리. 안녕히 가시오!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "카! 이렇게 머리 잘 돌아가는 선장하고 거래하니 참 기분 좋군. 일이 간단해: 근처 항구 중 한 곳에서 곧 출항할 플루트 한 척이 꽤 많은 은을 싣고 있지. 배는 한 척뿐, 호위도 없어. 웃기지 않아? 크-카\n 식은 죽 먹기지. 내가 언제 어디서인지 알려주면, 자네가 먹고 나는 몫만 챙기면 되는 거야.";
			link.l1 = "물론, 지금 당장 현금으로 받고 싶다는 거지?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "내가 한심한 좀도둑처럼 보여, 선장? 천만에. 이번 약탈에 나도 같이 할 거야, 우리 함께 하자고. 싸움이 벌어질 때 창고에 처박혀 있을 생각 없어, 오히려 반대야 – 잠시지만, 네 장교로 승선 돌격조에 넣어 달라고 부탁하는 거야\n내 일은 잘 알고, 칼도 쓸 줄 알고 총도 쏠 줄 알아. 그러니 너처럼 내 목숨도 걸겠지... 크흠... 크하! 우리가 그 플루트를 손에 넣으면 내 몫은 제대로 챙겨줘야 해.";
			link.l1 = "네 몫으로 얼마나 챙길 생각이냐?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "나는 욕심 많은 사람이 아니오, 선장. 내 몫은 내 오래된 노 젓는 배의 창고에 실을 수 있는 만큼뿐이니, 대략 은 200 꾸러미 정도 되겠군. 내 정보에 따르면, 그 플루트에는 최소한 은 2,000 꾸러미가 있을 거라 하니, 나는 10분의 1만 가져가겠소. 그 정도면 공평하지 않소?\n";
			link.l1 = "정보만으로 전리품의 10분의 1을 달라고? 그런 정보는 동네 선술집에서 주정뱅이한테 럼 한 잔 주고도 산다. 아니, 우리는 같은 길을 가는 게 아니야, 친구!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "흠. 나도 동의하지. 제안을 받아들이겠네, Adam. 승선을 환영하네. 이제 자네 정보에 대해 말해보게. 어디서 왔고, 어디로 가는지, 언제인지, 배 이름은 뭔가?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "정말 구두쇠구만, 선장! 그럼 아무것도 못 받아! 잘 있어!";
			link.l1 = "행운을 빌지! 네 수상쩍은 일에 끌어들일 다른 얼간이나 찾아봐!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "플루트의 이름은 "+pchar.questTemp.FalseTrace.ShipName+", 그녀는 카르타헤나를 떠나 항해를 시작한다 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". 하지만 시간은 많지 않아. 길어야 2주, 많아야 3주뿐이야. 3주 안에 그녀를 못 찾으면 끝이야.";
			link.l1 = "그럼 시간 낭비하지 말자! 모험이 우리를 부르고 있어!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "무슨 일 있으십니까, 선장님?";
			link.l1 = "아니야, 신경 쓰지 마.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "저를 찾으셨습니까, 선장님?";
			link.l1 = "이럴 줄 알았지... 은은 어디 있지, 젠장? 어디 있냐고? 너한테 말하는 거야! 플루트 선장이 그 배가 보급선이라고 했어! 너 나한테 거짓말했지!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "진정하세요, 선장님. 제가 모든 걸 설명해 드리겠습니다.";
			link.l1 = "당연히 그럴 거다! 이제 진정했으니 말이지! 네가 지금 돛대에 매달려 있지 않은 유일한 이유는 아직도 네 속셈을 이해할 수 없기 때문이야. 너는 처음부터 은이 없다는 걸 알면서도 나랑 이 플라이트를 쫓았지. 그러니, 네가 왜 그랬는지 설명해 봐.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "그래, 내가 정말 속였지, 선장. 하지만 내가 원하는 걸 하게 만들려면 그 방법밖에 없었어, 이 배를... 크흠 크흠! 이 빌어먹을 플루이트를 잡으려면 말이야\n하지만 내 빚은 꼭 갚겠다고 약속하지. 이제 왜 그랬는지 말해주지. 플루이트에서 여자를 찾았나? 네 배로 데려가는 걸 선원들이 데리고 가는 걸 봤거든...";
			link.l1 = "흠... 그래서 그 여자애가 필요했던 거냐? 그래서 나한테 해전을 벌이게 하고 그렇게 많은 사람을 죽이게 한 거야!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "내 아내야. 카테린 레이너. 석 달 전에 이 한심한 선장이랑 나를 떠나 도망쳤지. 나는 그들을 찾으려고 온갖 노력을 다 했고, 결국 찾아냈어. 둘 다 가려고 했던 곳은\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". 카테린을 데려오고 그 바람둥이 놈을 처리할 더 좋은 방법은 없었지\n사실을 말했다면 너는 그냥 가버렸을 거야. 그래서 은으로 가득 찬 플루트 이야기를 꾸며냈지.";
			link.l1 = "흥... 네 마누라가 널 떠났지? 아주 흥미로운걸!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "이 사람은 내 정식 아내야, 난 그녀만 사랑하고 다른 누구도 그녀와 함께할 권리가 없어! 그 망할 놈이 내가... 자리를 비운 사이에 그녀에게 사랑이니 뭐니 하는 달콤한 거짓말을 늘어놨지. 여자란 걸 몰라? 그 헛소리를 곧이곧대로 믿고, 어리석은 계집애가 그 자식 따라 도망쳤다니까.";
			link.l1 = "좋아, 들어. 네 가족사엔 별로 관심 없어. 그러니까 네 마누라랑 알아서 해결해. 그런데 내 비용을 보상해주겠다고 했지? 내가 잘못 들은 건 아니겠지?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "그래, 제대로 들었어, 선장. 은혜에는 은혜로 갚는 거지. 지금은 돈이 없지만, 카테린과 나를 데려다 준다면\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", 아무런 수고도 없이 금을 챙길 수 있는 곳에 대한 완전히 믿을 만한 정보를 알려주지.";
			link.l1 = "아주 흥미로운데. 그런데 왜 지금 당장 이 완전히 믿을 만한 정보를 말해줄 수 없는 거지?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "왜냐하면, 아직 그 정보를 내가 가지고 있지 않거든. 자세히 설명해 주지. '사팔눈 솔리'라는 운 좋은 신사 한 명이 있는데, 들어본 적 있나? 그자가 블루웰드에서 멀지 않은 금광을 약탈하러 갈 거야\n어떤 사건들 때문에, 그는 모든 금을 숨겨진 장소에 두고 몇 명의 경비병을 남겨서 지키게 할 수밖에 없어. 솔리 본인은 배를 구하러 벨리즈나 블루웰드로 걸어서 갈 거고\n내가 솔리 일당 중에 심어둔 정보원이 있는데, 그가 나를 기다리고 있을 거야 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". 거기 닻을 내리면, 그가 솔리가 보물을 숨긴 곳을 내게 알려줄 거야\n너는 그리로 가서 경비들을 처리하고 금은 전부 네가 가져라. 원래 내가 직접 하려고 했는데, 지금 상황을 생각해서 전부 너한테 맡기지. 대가도 필요 없어.";
			link.l1 = "네 이야기, 전에 은을 가득 실은 플루트 얘기랑 비슷하군. 이미 한 번 속았잖아. 이번에는 거짓말이 아니라는 걸 어떻게 보장할 수 있지?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "내가 맹세하지. 다른 보증은 없어. 하지만 진짜야, 맹세한다 khe... kha... 젠장할 광산들!";
			link.l1 = "좋아. 이제 가라, 네가 한 말을 곰곰이 생각해 보겠다.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "너무 오래 고민하지 마라. 사팔뜨기 솔리가 자기 보물을 찾으러 곧 돌아올 거라는 걸 알아야지. 내 계산으로는, 네가 거기로 갈 수 있는 시간은 딱 이 주일 뿐이야\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "명심하겠소. 이제 선원 숙소로 가서 다른 선원들과 함께 있게. 우리가 도착할 때까지는 아내와 떨어져 있는 게 좋을 것 같소. 이제 가도 된다.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "저를 부르셨습니까, 선장님?";
			link.l1 = "그래. Adam Rayner, 널 체포해서 가두겠다. 네가 날 속였으니, 난 널 격리하고 당국에 넘기는 수밖에 없어.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "정말인가? 그럴 줄 알았소, 선장. 특히 당신이 창고에 와서 남의 아내나 훔치는 더러운 놈과 얘기를 나눈 뒤에는 더더욱 말이오. 결국 그 자 편을 들기로 한 거요, 그렇지 않소, 선장?";
			link.l1 = "네 알 바 아니다. 넌 날 이용했고, 배신했으며, 이제 또다시 황당한 보물 이야기로 날 속이려 드는군! 보선장, 이 자 끌고 나가라!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "크하, 그렇게 서두르지 마, 선장... 너희 보선이랑 선원들은 당분간 여기 못 들어와. 내가 문 잠근 거 눈치 못 챘어? 이제 여기 우리 둘뿐이야, 너랑 나. 그러니 보여줘 봐, 선장, 네가 어떤 사람인지!";
			link.l1 = "정말이냐? 네가 이길 수 있다고 진심으로 믿는 거야?! 곧 후회하게 될 거다, 이 자식아!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "이제 좀 낫군... 무기 내려놔, 이 악당아! 보선! 이 놈을 족쇄 채워서 창고에 쳐넣어라!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "도와주셔서 감사합니다, 선장님, 제 아내를 되찾게 해주셨군요! 아담 레이너가 당신께 큰 신세를 졌소, 절대 잊지 않을 거요, 하하, 맹세코... 크흑! 젠장할 지뢰들! 이제 사팔뜨기 솔리 얘기로 넘어가죠. 내 부하가 이미 모든 정보를 내게 전해줬소. 솔리는 산후안 델 노르테 만의 동굴에 전리품을 전부 숨겨뒀다오. 본인은 지금 블루웰드에 있소\n서둘러야 하오, 내 친구 말로는 오직 닷새밖에 없소. 부하들도 데려가시오, 솔리의 악당들이 만만치 않으니 분명 골치 아플 거요\n이제 작별을 고할 시간이군. 다시 한 번 고맙소, 선장님, 행운을 빌겠소!";
			link.l1 = "행운을 빌어, Adam. 네 아내 기분 상하게 하지 마!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "하! 도대체 왜, 선장님, 우리가 이 만에 상륙한 겁니까? 내 사람이 항구에서 기다리고 있다고 분명히 말씀드렸잖습니까 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! 정글을 걸어서 거기로 갈 생각이야?";
			link.l1 = "틀렸군, 아담. 네 헛소리를 내가 또 믿을 거라 생각했어? 내가 완전 바보인 줄 아나? 이번엔 네 아내와 거래를 했지.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "뭐?! 하! 내 아내랑 무슨 거래를 했다는 거야? 무슨 소리를 하는 거냐, 이 썩은 생선 같은 놈아?!";
			link.l1 = "네 거짓 정보 때문에 나는 텅 빈 플루이트선을 붙잡았고, 그 선장의 목숨을 앗아갔다. 이제 와서 후회해도 이미 늦었지. 네 아내가 그 선원을 사랑하고 있었다고 들었다. 그래서 네 아내가 나에게 너를 죽여달라고 부탁한 거다. 그래서 우리가 지금 이 만에 있는 거지.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "믿을 수가 없어! 카테린... 저런 못된 년 같으니! 뭐, 결국엔 자기 꼴을 당하겠지... 자, 그래서 그년이 어떻게 보상해주겠다고 했냐, 이 멍청아? 걔는 한 푼도 없어, 그 선장이랑 도망치려고 자기 보석까지 다 팔아버렸거든!";
			link.l1 = "그건 네가 알 바 아니야, 이 악당아. 이제 우리 대화는 끝낼 때가 됐지. 네놈은 진작에 갔어야 할 지옥으로 보내주마!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "어디 한번 해보자, 썩은 청어 녀석!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "아! 대체 왜 내 배를 공격한 거냐, 이 쓰레기들아? 도무지 이해가 안 되는군...";
			link.l1 = "양인 척하지 마, 선장. 네가 무슨 화물을 싣고 있는지 난 다 알아. 그게 필요해.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "화물? 하하! 여기서 무슨 화물을 기대했나? 내 창고는 텅 비었어!";
			link.l1 = "뭐라고 했냐, 이놈! 다시 말해 봐!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "다시 말하지만, 내 배에는 화물이 없어. 이 플루트는 식량을 구하러 가는 배야. "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" 군대에 보낼 포탄과 보급품을 실어 나르기 위해.";
			link.l1 = "내 눈을 속이려고 하는군. 네 창고에는 은이 가득할 게 뻔하지. 이 대화가 끝나면 내가 직접 확인해 볼 거야...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "누가 너한테 은 이야기를 했는지 모르겠군. 하지만 그건 완전 헛소리야... 내가 너한테 졌으니 포기하지. 여기 내 검이야. 이제 가서 창고를 확인해 봐. 텅 비었을 거다.";
			link.l1 = "포기한다고? 아니! 난 증인 따위 필요 없어. 칼 들어, 싸워. 아니면 양처럼 배를 갈라버릴 테니까.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "이성적으로 행동해서 다행이군. 네 몸값은 받아낼 수 있을 것 같아... 이봐, 얘들아 - 선장을 감옥에 처넣어라!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "네가 그를 죽였구나, 이 망할 놈! 악당! 불쌍한 "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "이게 뭐야? 어디서 온 거니, 얘야?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "네가 저지른 모든 일로 지옥불에 타게 될 거다. 저주받을 놈!";
			link.l1 = "진정해, 아가씨! 나한테 욕지거리 하면서 운 시험하지 마라 – 아니면 네 선장 따라가게 해 줄 테니!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "너... 너 여자를 상대로 감히 손을 들 생각은 없겠지!";
			link.l1 = "굳이 그럴 필요도 없어. 그냥 너를 쏴버릴 수도 있고, 아니면 바다에 던져버리면 상어들이 알아서 처리해 주겠지... 자, 뭘 망설이냐? 내 배로 가. 겁낼 것 없어 – 조용히만 있으면 아무도 널 해치지 못하게 할 거고, 나도 손대지 않을 테니까...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "뭐... 뭐 할 생각이야, 그에게?";
			link.l1 = "이게 뭐야? 어디서 온 거니, 얘야?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Poor "+pchar.questTemp.FalseTrace.CapName+"! 말해 봐 - 그를 죽일 생각이야? 그러지 마...";
			link.l1 = "이봐, 아가씨 - 내가 그 자를 죽이려고 했다면 진작에 끝냈을 거야. 그는 창고에 가둘 거고, 나중에 풀어주든 몸값을 받든 할 거야... 몸값을 받는 쪽이 더 가능성 크겠지. 자, 이제 착하게 내 배에 올라오라고. 겁낼 것 없어 - 얌전히 있으면 아무도 널 해치지 않을 거고, 나도 손대지 않을 테니까...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "나한테 뭘 바라는 거야? 네가 말한 대로 나를 상어 밥으로 던지려고? 내 인생을 망쳐놓고, 나는...";
				link.l1 = "어서 와, 자기야. 아무도 너를 어디로 던질 생각 없어. 그냥 상황을 분명히 하고 싶을 뿐이야. 내가 이 플루트를 공격한 건 오직 너 때문이지, 다른 이유는 아니거든.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "나한테 뭘 원하는 거야? 어디 있지\n "+pchar.questTemp.FalseTrace.CapName+"몸값? 몸값이 필요한 거야?";
				link.l1 = "좋아, 아가씨, 이제 쓸데없는 질문은 그만하지. 내가 그 일로 널 부른 건 아니야. 한 가지 사실은 밝혀졌고, 그게 네 흥미를 끌 거라 생각해.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "나 때문이라고? 네가 우리 배를 공격해서 내 사랑하는 사람을 죽인 게 내 잘못이라는 거야? 불쌍한 "+pchar.questTemp.FalseTrace.CapName+", 그가 너한테 뭘 했지? 네가 저지른 모든 일에 대해 주님께 답해야 할 거다...";
			link.l1 = "또 그 밥에 그 나물이군! 상어 얘기로 다시 돌아갈까?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "이제 조용하지? 좋아. 내 말 잘 들어! 내가 그 배를 공격한 건, 거기에 꽤 많은 은화가 실려 있다는 정보를 받았기 때문이야. 그리고 그 정보는 아담 레이너한테서 얻은 거다.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "어! 뭐라고?! 아담? 어디 있어? 여기 있는 거야?";
			link.l1 = "이름을 아는군... 카테린. 그리고 보다시피, 나는 이미 너에 대해 다 알고 있지. 아담 레이너가 네 남편 맞지?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "그래. 나는 이 괴물의 아내야. 이 악몽이 드디어 끝난 줄로만 알았는데... 그 자가 너를 시켜서 나를 잡으러 온 거냐?";
			link.l1 = "대체로 그렇게 된 거지. 아담이 나한테 은에 대해 거짓말을 해서 내가 플루이트 '를 잡게 만들었어\n"+pchar.questTemp.FalseTrace.ShipName+"' 분명히, 그는 널 데려오기로 단단히 마음먹었지. 15분 전에 자기 행동을 전부 나한테 설명했어.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "그래서... 그는 뭘 원한대? 너한테 뭐라고 했어?";
			link.l1 = "그자는 자기 정식 아내가 돌아오길 원해. 나를 속인 대가로 사팔뜨기 솔리의 금에 대한 정보를 나한테 주기로 했지. 그리고 나는 너희 둘을 데려가려고 해\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "아니야... (울면서) 그 악당한테 다시 돌아가고 싶지 않아! 그놈한테서 도망치려고 엄청 애썼고 흔적도 감췄는데, 결국 날 찾아냈잖아... 악질 놈! 도둑놈! 피도 눈물도 없는 도둑이야!\n";
			link.l1 = "진정해, 카트린... 말 좀 가려서 해. 어쨌든 그 사람은 네 남편이잖아. 그리고 너를 사랑한다고 했잖아.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(울먹이며) 내 남편이요? 내 남편이 누군지 알아요? 그는 전과자에다 죄수였고, 지금은 가장 잔혹한 도적이야\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! 그 자식은 천박하고 더러운 짐승일 뿐이야, 나를 그냥 다리 사이 구멍으로밖에 안 보는 놈이지!";
			link.l1 = "그와 결혼하기 전에 이미 다 본 거 아니었어?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "처음엔 그 사람이 달라 보였어... 그리고 그의 과거도 내게는 참 낭만적으로 느껴졌지... 하지만 결국 모든 게 변해버렸어. 이제는 그 사람을 보는 것조차 싫고, 같이 사는 건 더더욱 싫어, 그걸 이해 못 하겠어? 정말 싫어! 특히 그가 꾸민 이번 플루이트 공격 이후로는 더더욱!";
			link.l1 = "흠... 그럼, 너를 어떻게 해야 할까, 귀여운 아가씨?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "어떻게 해야 하지? 아니, 나는 알아. 네가 바로 죄악의 도구야, 내 남편 짓거리 덕분에. 넌 죄 없는 사람을 죽였어, 내게 잘해준 유일한 사람이었는데. 죄를 속죄해, 선장. 아담을 죽여. 내 눈앞에서 말이야. 저 쓰레기가 죽는 걸 보고 싶어, 시체에 침을 뱉고 싶을 정도야\n그가 죽으면, 그놈이 보물을 어디 숨겼는지 말해줄게. 그 술주정뱅이 바보가 한 번 자기 은닉처에 대해 떠들었거든, 하하, 자기는 기억도 못 해!";
				link.l1 = "헤! 보아하니 너 참 잔인한 여자구나, Katherine!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... 그 플루트선의 선장 말이야. 당신이 그를 가뒀잖아. 제발 그와 이야기해 줘! 우리 목숨과 자유를 위해 뭔가 제안을 할 거야! 뭔가 방법을 생각해낼 거라고! 나... 나 이제부터는 아담에게 돌아가고 싶지 않아 "+pchar.questTemp.FalseTrace.CapName+" 내 남편이에요! 제발 부탁이에요 – 저를 다시 아담, 그 괴물에게 데려가지 마세요!";
				link.l1 = "흠. 흥미롭군. 내 포로가 나한테 뭘 줄 수 있을까? 당국에 넘기면 몸값을 받을 수 있고, 사팔뜨기 솔리의 금도 내 것이 될 텐데...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "잔인함을 논하는 게 누군지 좀 보라고. 항해해라\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", 아담이 시킨 대로 해, 다만 항구가 아니라 가장 가까운 만에 상륙해. 우리 셋이 거기로 갈 테니 네가 그 자식을 죽이면 돼\n끝나면 은닉처에 대해 말해주지. 맹세컨대 거짓말 아니야. 네가 내 말을 아담보다 더 믿을 거라 생각해—그 자식 한 번 속였잖아? 어때, 선장?";
			link.l1 = "그래... 괜히 부부는 한통속이라는 말이 있는 게 아니지. 너를 보니, 카테린, 정말 아담이랑 딱 어울리는구나... 그 자식이 그렇게 죽었으면 좋겠으면, 술에 취해 자고 있을 때 그냥 네가 찔러버리지 그러냐... 조타수! 이 여자 끌고 나가!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "나를 속이고 자기 이익을 위해 이용하려 드는 놈들은 정말 싫어. 좋아, 캐서린, 네 제안을 받아들이지. 아담은 도무지 믿을 수 없다는 게 분명하니까. 하지만 너도 날 속이면, 맹세코 유럽까지라도 쫓아가서 네 머리에 총알을 박아줄 거다. 이제 꺼져. 보선! 저 여자 끌고 나가!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "너 이 일 후회하게 될 거야... 맹세코, 나는...";
			link.l1 = "보스운! 저 여자를 지키고, 우리가 도착할 때까지 항상 감시해라 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "무슨 사실? 우리한테 뭘 하려고? 왜 우리 배를 붙잡은 거야?";
			link.l1 = "내가 한마디 해도 되겠나, 아니면 내 보선장에게 네 입을 재갈로 막으라고 명령할까?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "솔리의 금이라고? 너 정말 그 악당을 믿는 거야? 또 한 번 속일 거다, 저놈이 원래 그런 놈이거든! 네 포로한테 가서 얘기해 봐!\n"+pchar.questTemp.FalseTrace.CapName+" 진정한 신사라서, 약속을 어기지 않을 것이고 당신에게 거짓말도 하지 않을 거요!";
			link.l1 = "넌 날 설득하지 못했어, 아가씨. 네 선장과는 더 이상 할 말 없어. 난 그를 몸값으로 팔 거고, 아담에게서 솔리의 금도 받아낼 거다. 아담이 또다시 날 속이면, 세상 끝까지라도 찾아내서, 자기 태어난 날을 저주하게 만들 거야... 보선! 이 여자 데리고 가!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "사실을 말하자면, 나는 아담을 믿지 않아... 누가 날 조종하는 건 정말 싫거든. 좋아, 네 선장과 얘기해 보고 무슨 말을 하는지 들어보지. 이제 가도 된다... 보선! 저 여자를 데려가라!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "너는 정말 잔인하고 인정머리 없는 놈이야! 맹세코 나는...";
			link.l1 = "갑판장! 우리가 도착할 때까지 저 여자를 지키고 계속 감시해라 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "이제 끝났어... 불쌍한 "+pchar.questTemp.FalseTrace.CapName+" 복수가 이루어졌으니, 이제야 숨을 쉴 수 있고 스스로를 과부라 부를 수 있겠구나...";
			link.l1 = "내 할 일은 다 했어, Katerine. 이제 네 차례야.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "물론이지요, 선장님. 내 남편—이제는 신께 감사하게도 전남편이 되었지만—은 당신도 알다시피 도적이었어요.\n혹시라도 수색이 들어올까 두려워서 약탈한 전리품을 집에 두지 않았죠.\n비밀 은닉처를 만들었는데, 한 번은 그걸 무심코 흘린 적이 있어요.\n그래도 아주 교묘하게 숨겨놨기에, 그곳은 해안에서 접근할 수 없답니다.";
			link.l1 = "아주 흥미로운데... 그런데 그게 어디 있지?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "이스파니올라 근처의 작은 섬에 있어. 등대 안이야.";
			link.l1 = "포르토프랭스 등대다! 그건 섬에 있어!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "아마 그럴 거야. 거기서 전리품을 찾을 수 있을 거다. 곧 알게 될 거야. 그게 다야. 잘 가, 선장.";
			link.l1 = "잠깐만... 용서해 줘, 카트린, 네가 할 수 있다면. 네 모든 불행의 원흉이 죽었으니 적어도 조금이나마 위안이 되었으면 해. 정말 미안해...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "네 후회 따위 필요 없어, 선장. 내가 시킨 대로 했고, 너도 알고 싶던 건 다 말해줬으니. 이제 가거라, 그리고 내 슬픔과 함께 나를 혼자 두어라...";
			link.l1 = "잘 가, Katherine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "더러운 악당! 그 자가 네 명 모두를 죽였어! 믿을 수가 없군!";
			link.l1 = "이런 전개는 예상 못했지, Katerine? 나는 쉽게 죽지 않아. 너 이중 플레이 꽤 잘하더군!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "내 부하를 죽였군. 네가 계속 숨 쉴 수 있을 거라 생각했나?! 아담이 죽은 걸로 내가 만족할 거라 여겼어? 아니지! 넌 이곳을 절대 떠날 수 없어. 이 섬에서 멀지 않은 곳에 배가 있다. 그 배가 네 낡은 배랑 너까지 같이 수장시켜 줄 거다!\n이제, 네 맘대로 해라.";
			link.l1 = "내가 말했잖아, 자기야, 날 속이면 목이 달아난다고? 교활한 악마 같으니! 죽으면 덜 위험하겠지. 이 예쁜 머리통, 지금 당장 총알 맛을 보게 될 거야...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "안됐다, 카테린. 네 복수심이 결국 아무 소용도 없었구나. 나는 이제 너를 네 운명에 맡기고 이 섬에 두고 가겠다. 곧 이 근처 어부들이 널 발견해서 히스파니올라로 데려가겠지. 그리고 우리의 모든 행위에 대해 주님께서 심판하시길 바라노라...\n";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "기도해야 할 사람은 바로 너다, 괴물아! 살인자! 도와줘! 젠장, 이...";
			link.l1 = "이제 충분히 들었어.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "물에 빠져 죽어라! 네 배가 암초에 부딪혀 산산조각 나길! 네가...";
			link.l1 = "잘 가, Katherine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "아-아, 여기 아담을 죽인 놈이 있군! 캐서린 말이 맞았어, 이 자식이 보물 훔치러 온 거였어!";
			link.l1 = "뭐? 캐서린? 너 누구야?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "우리가 누구냐고? 우리는 아담 레이너의 친구들이다, 네놈이 죽인 그 사람 말이다. 그는 우리 형제단의 우두머리였지. 이제 내가 우두머리다, 내 이름은\n "+GetFullName(npchar)+", 그리고 내 상사를 죽인 것과 그의 아내에게 저지른 폭력에 대해 내가 너를 벌할 것이다.";
			link.l1 = "폭력? 도대체 무슨 소리를 하는 거야?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "너는 아담을 등 뒤에서 찔렀지, 이 더러운 배신자 놈아. 아담이 금을 어디에 숨겼는지 알아내려고 그의 아내를 협박했고, 불쌍한 여자를 외딴 해안에 버려두고 떠났지.\n하지만 그 여자는 살아남았어. 우리에게 도와달라고, 잘못된 일을 바로잡아 달라고 부탁했지. 우리는 며칠 동안 네놈을 기다렸다. 그리고 드디어 나타났군, 이 개자식아!";
			link.l1 = "하하! 확실히 카트린다운 방식이지... 자, 들어봐. 내가 아담을 죽인 건 사실이야. 하지만 그건 그의 아내가 나한테 직접 부탁해서 그랬던 거야. 그녀의 연인이 죽은 것에 대한 복수였지. 그녀가 보답으로 은닉처가 어딘지 알려줬어...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "가엾은 과부를 헐뜯지 마라, 이 쓰레기야! 그럼 그 여자가 왜 우리한테 왔겠어? 네 목숨을 대가로 우리한테 금을 다 가지라고 했지. 그 여자는 돈이 아니라 네 죽음을 원해! 자기 남편의 죽음에 대한 정의로운 죽음이지!\n하지만 맹세컨대, 그 여자가 가난하게 죽지는 않을 거다, 내 이름을 걸고 맹세하지 "+GetFullName(npchar)+", 그리고 이제 네가 죽을 때다, 겁쟁이 놈아!";
			link.l1 = "세상에, 대단한 연설이군. 오, 저기 그녀가 있네, 이 희극을 직접 보려고 안달이 났지... 신사 여러분?\n";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "정말 덜렁이구나, 선장! 은으로 가득 찬 플루이트선을 잃다니... 너를 믿은 내가 실수였지. 잘 가라!";
			link.l1 = "잘 가라, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "경고했잖소, 선장님, 우리에겐 딱 이주밖에 없었다고! 지금쯤이면 사팔뜨기 솔리가 이미 전리품을 다 챙겼을 거요. 당신이 이렇게 허둥대는 건 내 잘못이 아니오. 잘 가시오!";
			link.l1 = "그래, 내 잘못이다. 잘 가라. 다시는 안 만났으면 좋겠어. 너만 보면 재수가 없거든.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "헤! 드디어군! 기다리느라 지쳤다고, 이 빌어먹을 모기들까지... 잠깐... 솔리는 어디 갔지? 이해가 안 되네...";
			link.l1 = "솔리 녀석은 여기 안 와. 내가 대신 온 거야... 그러니 금을 내놓든가, 아니면 죽은 목숨이야.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "아르! 두고 보자! 이리 와라, 녀석들아! 무장해!";
			link.l1 = "이렇게 어이없이 죽다니, 자, 덤벼라 이 죽지 못해 사는 놈들아!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "약속한 대로 해주셨군요, 선장님. 저를 믿어주셔서 감사합니다. 아담은 걱정하지 마십시오, 제가 그를 마땅한 곳에 데려다 주겠습니다. 그는 자기 몫을 받게 될 겁니다.";
			link.l1 = "나는 아담 따위 신경 안 써. 그 배에 관한 네 약속은 어쩔 건데?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "그래, 그래, 알았어. 어디 보자, 오늘부터 세면... 그래... 12일에서 14일 뒤에\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" 금광석을 가득 실은 대형 갤리온이 유럽으로 출항할 거야. 그 배는 프리깃이나 코르벳 한 척이 호위할 거다\n그러니 준비해라. 값진 먹잇감이지만 만만치 않아. 그래도 네가 해낼 거라 확신한다. 내 저항도 꽤 손쉽게 꺾었으니까... 반드시 도착해야 해 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" 2주 안에 매복을 준비해라\n네 목표는 호위선 한 척이 딸린 대형 갤리온이라는 걸 명심해. 그게 다다, 아마. 나머지는 네 손에 달렸지.";
			link.l1 = "그렇군... 음, "+pchar.questTemp.FalseTrace.CapName+", 잘 가시오. 어쩌면 그대에게 행운과 카테린과의 행복한 삶을 빌어야 할지도 모르겠군. 두 분이 무사하길 바라오. 이렇게 슬픈 상황에서 만나게 되어 유감이오.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "감사합니다, 선장님. 이미 말씀드렸듯이, 당신에게는 어떤 고귀함이 있습니다. 정직한 행동이 비열한 짓보다 더 큰 이익을 가져온다는 것을 언젠가 깨닫길 바랍니다. 조국을 위해 헌신한다면, 훌륭한 해군 장교가 될 수 있을 것입니다.";
			link.l1 = "네 말은 생각해 보마. 자, 그럼 이만 가보지!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
