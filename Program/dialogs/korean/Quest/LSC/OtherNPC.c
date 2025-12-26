// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐 필요한 거 있어?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "호호, 이것 좀 봐라, 얘들아! 누가 우리를 찾아왔나! 남의 상자를 털러 온 도둑놈이군! 이리 와! 그리고 너, 친구야, 시치미 떼거나 칼 뽑을 생각도 하지 마라 – 이렇게 가까이서 놓칠 리 없으니까... 챈드가 널 보면 아주 좋아하겠지!";
			link.l1 = "하지만 나는... 나는 이제 막 도착했어!";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "네 말이 맞아, 하하! 너 제대로 엉망진창에 빠졌구나, 이 친구야... 그리고 이제 못 빠져나가. 자, 무기 내려놓고 따라와! '타르타로스'에 있는 우리 감옥이 너 같은 도둑을 오래도록 기다렸거든!";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Few hours later...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "여기서 뭐든 훔치려고 하지 마. 내가 지켜보고 있을 테니까.";
			link.l1 = "환영하오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "가서 Chad가 시킨 대로 해. 말 너무 많이 하지 마!";
			link.l1 = "그래, 가는 중이야...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "이봐! 거기서 뭐 하는 거야? 이 자식아! 이제 끝장이야!";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "이봐, 도대체 여기서 뭐 하는 거야, 젠장? 바르비에 어디 있지?";
			link.l1 = "우리 친구 아돌포가... 몸이 좋지 않아. 회의에 올 수 없어서, 자기 선실에 잠시 앉아 있으면서 너를 기다려 달라고 부탁했어.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "이봐, 여기서 대체 뭐 하는 거야, 젠장?";
			link.l1 = "우리 친구 아돌포가... 몸이 안 좋아. 회의에 올 수 없어서, 대신 내가 오라고 부탁했지. 뭐, 그런 셈이야.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "이상하네... 오늘 아침까지만 해도 멀쩡했는데, 지금은 아프다니.";
			link.l1 = "글쎄, 세상일이란 다 그렇지. 갑작스런 열병이 들이닥쳤거든...";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "오, 네 얼굴이 마음에 안 들어. 거짓말하고 있군. 바르비에가 이 만남을 다른 놈한테 맡길 리 없어. 말해, 이 자식아, 넌 누구고 그에게 무슨 짓을 한 거지?";
			link.l1 = "있잖아, 너도 별로 볼품없어. 바르비에가 아프다고 이미 말했잖아. 너 좀 둔한 거야, 아니면 내가 또 말해야 해? 그가 네게 열쇠를 주기로 했고...";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "젠장! 결국 나를 찾아냈군...";
			link.l1 = "그래, 이 쓰레기들아! 그녀한테 손도 못 대게 할 거다! 죽을 준비나 해라!";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "너냐 "+GetFullName(pchar)+"?";
			link.l1 = "그래, 나다. 무슨 일이야?";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "상어가 나를 보냈어. 최대한 빨리 그를 찾아오라고 하더군. 너에게 중요한 일이 있다고 해.";
			link.l1 = "왜 이렇게 급해?.. 알겠어, 바로 '산 아구스틴'으로 갈게.";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "너냐 "+GetFullName(pchar)+"?";
			link.l1 = "그래, 나야. 무슨 일이야?";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "어, 너를 찾느라 지쳤다... 상어랑 레이튼 덱스터가 널 당장 보자고 하더라. 아주 중요한 일이니까 서둘러.";
				link.l1 = "그래? 좋아, 나는 지금 바로 '산 아구스틴'으로 간다.";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "어휴, 너를 찾느라 지쳤다... 레이튼 덱스터 제독께서 즉시 찾아오라고 하신다. 아주 중요한 일이니 서둘러라.";
				link.l1 = "제독?";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "그래. 그는 부선장이었고, 상어가 죽은 뒤 우리 제독이 되었지.";
			link.l1 = "알겠소. 좋아, 바로 '산 아구스틴'으로 가겠소.";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "아, 여기 있었군... 기억나, 네가 치미셋과 마지막으로 얘기한 사람이었지. 그를 죽였나?";
				link.l1 = "헛소리 집어치워! 내가 아니라는 거 뻔히 알잖아. 누가 살인자인지 너도 알고 있을 거라고 본다.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "에이, 하루 종일 여기 있으려니 너무 지루하잖아! 럼주랑 카드라도 가져왔으면, 친구야, 한 판 놀아볼 수 있었을 텐데...";
				link.l1 = "미안하다, 친구야, 지금은 이럴 시간 없어. 나중에 보자.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "짐작은 좀 있지, 그래도 확실한 사실은 없어. 흑인 남자의 죽음을 본 사람은 아무도 없어. 정의의 섬 전체에 우리, 상어 패거리가 범인이라는 소문이 돌고 있고, 어떤 신참이 제독의 명령으로 그랬다는 말도 있어. 알겠지? 그러니까 지금은 리바도스 쪽엔 가지 마. 걔네들 지금 너무 화나 있거든.";
			link.l1 = "좋아. 알겠어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "에이, 하루 종일 여기 있으려니 너무 지루하잖아! 럼주랑 카드라도 가져왔으면, 친구야, 우리 한 판 놀아볼 수 있었을 텐데...";
			link.l1 = "미안하다, 친구야, 지금은 이럴 시간 없어. 나중에 보자.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "뭐 원해, 이봐?";
			link.l1 = "흠. 그런데 여기에 무슨 일로 왔지? 악셀은 어디 있나?";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "악셀은 바빠. 도널드 그린스펜이랑 회의 중이라 오늘 하루 종일 그와 함께 있을 거야. 그러니까 뭔가 사고 싶으면 내일 아침에 와서 얘기해. 그리고 나는 가게를 지키고 있으니까, 훔치려고 하지 마...";
			link.l1 = "알겠소. 그런데 왜 오늘 그 일을 하는 거요? 좋아, 내일 아침에 여기 오겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("나는 이미 다 말했어. 내일 여기로 와.","귀찮게 하지 마, 이봐. 꺼져!","나 화나게 하지 마, 이 자식아!","꺼져!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("좋아.","알겠어, 알겠다고.","닥쳐...","뭐?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "무슨 일이오, 나리?";
			link.l1 = "흠... 죄송합니다, 아씨. 무례하고 버릇없는 행동을 용서해 주십시오. 하지만 묻고 싶은 게 있습니다. 혹시 올레 크리스티안센이라는 남자를 아십니까?";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "방금 한 말을 다시 해 봐... 올레 크리스티안센? 올레?!";
			link.l1 = "그래. 머리카락 색이 특이해서 '백색 소년'이라고도 불려. 그를 아나?";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "내가 그를 아냐고?! 그는 내 아들이고, 벌써 십 년째 행방불명이야! 혹시 그가 어디 있는지 아시오, 나리? 제발 어디 있는지, 무슨 일이 있었는지 말해 주시오!";
			link.l1 = "진정하세요, 부인, 그렇게 걱정하지 마세요. 그는 괜찮아요. 제 배에 있습니다. 그가 해야 할 일은 육지에 올라와 여기로 오는 것뿐이에요.";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "오... 드디어 주님께서 제 기도를 들어주신 것 같군요! 그 아이가 사라졌을 때 제가 얼마나 걱정했는지 상상도 못하실 겁니다! 모두 제 잘못이었어요, 전적으로 제 책임이었죠! 어디서 그 아이를 찾으셨나요? 그 아이는 평범한 아이가 아니에요... 음, 무슨 말씀인지 아시겠지요.";
			link.l1 = "그래, 알아. 맞아, 그 사람은 특별하지. 그리고 전혀 변하지 않았어. 아직도 어린애 같아 보여. 내가 어느 섬에서 그를 발견했지. 우연히 만났어. 그가 나한테 하얀 구슬을 달라고 했지... 젠장!... 진주 말이야.";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "진주라고? 오, 맙소사! 내 아들이 사라진 것도 다 진주 때문이야! 그 빌어먹을 목걸이 때문에 이런 일이 벌어진 거라고!";
			link.l1 = "올레가... 진주 목걸이를 끊어서 집을 떠났다는 게 사실인가요?... 진정하세요, 마님, 울지 마십시오!";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "그래, 사실이야. 올레가 부두에서 내 목걸이를 잡아당겨서 진주가 전부 물에 빠졌지. 내가 그놈을 얼마나 욕했는지 몰라, 그리고 내 고인은... 그를 벌줬어. 올레는 다음 날 사라졌지. 내가 이 일로 나 자신을 얼마나 탓했는지 상상도 못할 거야!";
			link.l1 = "올레는 수년 동안 진주를 모아 왔어. 그는 그걸 하얀 구슬이라고 부르지. 그 모든 걸 너를 위해 모았고, 나에게 너에게 데려다 달라고 부탁했어. 빨간 지붕이 있는 집 말고는 아무 정보도 없었지. 하지만 결국, 너를 찾아냈어.";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "진주를 모으고 있었다고?! 오, 맙소사! 내 불쌍한 아들에게 너무 미안해서 견딜 수가 없어! 내가... 그런데 그 애가 진주를 모으고 있었다니! 오!";
			link.l1 = "아마도 아드님을 불러와야겠군요, 마님. 그 아이가 어찌나 어머님을 보고 싶어 하던지요. 진주를 보여드리면 기뻐하실 거라고 했어요. 하지만 제 생각엔, 진주 때문이 아니라서 기쁘실 것 같네요...";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "마인헤르... 부탁이네. 내 올레를 데려다 주게. 꼭 안아 주고 용서를 구하고 싶네...";
			link.l1 = "물론입니다, 마님. 곧바로 그를 이리로 데려올 것입니다.";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "자, 부인, 여기 당신 아들 올레 크리스티안센이요. 알아보시겠습니까?";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "나리... 미안하오, 성함을 여쭙지 않았소... "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+", 마님. 선장 "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "선장님, 제 아들에게 얼마나 감사한지 상상도 못하실 겁니다! 선장님께서 그를 도와주시고 여기까지 데려와 주셨지요. 선장님 덕분에 제가 다시 살아난 기분입니다! 제 아들을 위해서라면 뭐든 하겠습니다. 그동안 못 줬던 모든 사랑을 다 주겠어요.";
			link.l1 = "기쁘군요, 아씨. 올레도 마찬가지로요. 그는 착한 청년이고, 힘든 상황에서 나를 도와줬어요. 마음씨도 곱고요. 올레가 죽음에서 구해준 사람을 내가 알고 있답니다.";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "나리, 내일이나 시간이 되실 때 꼭 여기로 와 주시길 바랍니다. 내 아들 일로 감사 인사를 드리고 싶습니다. 지금은 조금... 뭐, 아시겠지요.";
			link.l1 = "네, 마님.";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "내일 여기로 다시 오시오. 내 아들과 나를 위해 베푼 모든 선행에 대해 제대로 보답하겠소.";
			link.l1 = "좋아. 꼭 찾아갈게!";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "아, 여기 있었군, 나리 "+GetFullName(pchar)+"! 이리 와서, 앉아...";
			link.l1 = "고마워! 올레는 어때?";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "아, 당신이 무슨 일을 했는지 상상도 못할 거예요! 당신을 보는 순간, 상심한 어미의 마음이 얼마나 위로받았는지... 당신에게 빚을 졌어요. 평생 당신을 위해 기도할게요.";
			link.l1 = "부끄럽게 만드시네요, 마님...";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "나는 언제나 겸손이야말로 귀족을 귀족답게 만드는 덕목이라고 생각했어요... 당신이 해준 일에 대한 선물을 준비해뒀답니다. 그래요, 그래요! 거절할 생각은 꿈도 꾸지 마세요! 자, 받아요... 첫째로, 두블룬이 가득 든 상자가 있어요. 둘째로, 이 마법 부적을 받아요. 스카라브라고 부르죠.\n남편이 가지고 있던 건데, 그 보물이 내 아들을 돌려준 이렇게 고귀한 선장님께 간다니 남편도 기뻐할 거라 확신해요. 남편은 목수였고, 스카라브가 일을 빠르게 해준다고 늘 말하곤 했어요.\n이 반지가 당신에게도 잘 쓰이길 바라요. 당신이라면 충분히 낄 자격이 있어요, 의심할 여지 없이! 마지막으로, 내 재봉 도구도 받아요. 아주 좋은 세트랍니다. 이것만 있으면 좋은 물건을 많이 만들 수 있을 거예요.";
			link.l1 = "오! 이건 어떤 선장에게도 정말 귀중한 선물이군요! 고맙습니다, 아씨.";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received the 'Scarab' amulet");
			Log_Info("You have received a sartorial set");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "그리고 내 집의 문은 언제나 당신에게 열려 있다는 걸 알아줬으면 해. 여기서는 언제든지 음식과 좋은 와인 한 병, 그리고 당신이 원하는 모든 것을 항상 찾을 수 있을 거야.";
			link.l1 = "친절한 말씀 감사합니다, 마님. 이 마을에 다시 올 때 꼭 뵙고 싶습니다.";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "꼭 와야 해!";
			link.l1 = "이제 가봐야겠어. 안녕히 계시고, 행운을 빌어!";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "아, 선장님 "+GetFullName(pchar)+"! 이렇게 다시 만나서 정말 반갑네! 어서 와서 앉아, 내가 술 한잔 따라줄게...";
			link.l1 = "고마워! 그냥 인사하고 어떻게 지내는지 궁금해서 왔어. 너랑 올레 둘 다 잘 지내고 있다니 기쁘네.";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 응? 도둑놈!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에, 네가 내 상자를 뒤지기로 했군!","내 내 상자를 뒤져볼 생각이었어? 그냥 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자들을 뒤져볼 생각이었어? 가만두지 않겠다!";
			link.l1 = "어리석은 계집애!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
