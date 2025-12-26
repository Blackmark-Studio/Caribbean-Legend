// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "명백한 버그야. 개발자들에게 알려 줘.";
			link.l1 = "그래, 그렇게 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "안녕하십니까, 선장님! 아주 흥미로울 만한 사업 제안을 하나 드리고 싶습니다.";
			link.l1 = "계속하시지, 나리.";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "과달루프에서 스페인 본토까지 수송 일을 위해 당신 배를 빌리고 싶소.";
			link.l1 = "너 거기로 승객으로 가고 싶다는 거야?";
			link.l1.go = "citizen_2";
			link.l2 = "스페인 본토? 난 사양할게. 우리랑 스페인 놈들이랑은 딱히 친구도 아니거든. 다른 호구나 찾아봐.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "말씀대로입니다, 선장님, 하지만 이번 항해는 그리 위험하지 않소. 안녕히 가십시오.";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "원하시는 대로 하겠습니다, 선장님. 안녕히 가십시오!";
			link.l1 = "잘 가라.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "꼭 그렇진 않소, 나리. 승객이란 선장의 뜻에 따라야 하는 사람이오. 나는 자네와 자네 선원들, 그리고 자네 배를 고용하고 싶소. 나와 내 친구 두 명을 파나마까지 데려다주게.";
			link.l1 = "파나마로 간다고? 어떻게? 대륙 전체를 돌아서 항해하겠다는 거야?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "하하하! 좋은 농담이군, 선장. 당연히 아니지. 네가 해야 할 일은 우리를 포르토벨로에서 멀지 않은 모스키토 만까지 데려다 주는 것뿐이야.\n파나마까지는 우리가 알아서 갈 거야. 정글을 통과하는 게 이번이 처음도 아니니까.";
			link.l1 = "보수는 어떻게 되는 거지?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "두 상자의 두블룬이다. 삼백 개지. 배에 오르면 먼저 한 상자를 선불로 주겠다.\n목적지에 도착하면 두 번째 상자도 네 것이 된다.";
			link.l1 = "이렇게 쉬운 일에 후한 보수라니. 무슨 꿍꿍이가 있나, 이봐?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "선장, 시간은 돈이야. 나랑 내 친구들에겐 시간이 없어. 오늘 밤에 여기서 출항해야 하고, 열흘 안에 도착해야 해. 이번이 두 번째 임무야. 자, 할 거야?";
			link.l1 = "거래 성사!";
			link.l1.go = "citizen_6";
			link.l2 = "미안하오, 나리, 하지만 그 제안은 내게 너무 수상하게 들리오. 다른 바보를 찾아보시오.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "훌륭하군. 내 친구들은 지금 정글에 있으니, 우리 합의에 대해 알려주겠네. 오늘 밤 열 시에 캡스터 해변에서 우리를 만나게 될 걸세. 늦지 마시오, 선장!";
			link.l1 = "좋아. 캡스터 해변, 오늘 밤 열 시다.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "잠깐만요, 선장님, 우리 아직 서로 소개도 안 했잖아요. 제 이름은 베르트랑 피네트입니다. 그리고 당신은...";
			link.l1 = ""+GetFullName(pchar)+". 선장 "+GetFullName(pchar)+". 잘 가시오, Pinette 나리.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Captain "+GetFullName(pchar)+", 거기 있었군. 이제 출발해도 되나?";
			link.l1 = "그래. 배에 온 걸 환영한다.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "좋아. 선금으로 두블룬이 가득 든 상자를 받아라.\n그리고 기억해라 - 목적지까지 우리를 데려가는 데 열흘밖에 없다. 하루도 더 넘기지 마라!";
			link.l1 = "조건은 기억하고 있어. 걱정 마, 제때 도착할 거야. 자리들 잡아.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "그래서, 선장님, 약속하신 일을 완전히 끝내셨군요. 이제 제 차례입니다. 이 상자와 저희의 깊은 감사를 받아주십시오.";
			link.l1 = "거래하게 되어 즐거웠소, 나리.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "나도 그렇소. 안녕히 가시오, 선장 "+GetFullName(pchar)+".";
			link.l1 = "잘 가라!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "자, 선장님, 여기까지 왔군요.\n당신은 약속한 일의 절반만 이행했으니, 나도 그만큼만 하겠소.\n선불금은 전액 받았다고 생각하시오.\n불만은 없겠지? 어차피 그쪽 잘못이었으니.";
			link.l1 = "마음에 들진 않지만, 네 말이 맞다는 건 인정하겠다. 이제 각자 길을 가자.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "아무튼, 수고했소, 선장 "+GetFullName(pchar)+". 잘 가라!";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "오! 이런 우연이! "+TimeGreeting()+", "+GetFullName(pchar)+"! 그런데 어떻게?";
			link.l1 = TimeGreeting()+", Pinette 나리. 당신을 찾는 게 쉽지 않았소.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "그 이유가 뭡니까, 선장?";
			link.l1 = "좋은 나리, 이름이 있는 사람이 있소 "+GetFullName(sld)+" 그분이 당신을 몹시 보고 싶어 하십니다. 왜 그런지 알고 있겠지요.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "물론 알고 있지. 하지만 그대도 알아야 하오, 내 역시 나리와 만나고 싶어 하는 건 아니니. "+GetFullName(sld)+" 전혀. 너 그 자의 현상금 사냥꾼이냐? 도무지 이해가 안 돼.";
			link.l1 = "유감이지만, 지금의 나는 그런 사람일 뿐이고, 그게 마음에 들지 않아. 내가 실수했지, 그리고 지금 나리 "+GetFullName(sld)+", 젠장할, 그놈이 나한테 선택지를 줬어. 네가 과달루프에 영광스럽게 돌아가든가, 아니면 내가 돈 카를로스 데 밀리아르를 풀어주려는 네 짓에 공범으로 목이 날아가든가 둘 중 하나지. 그건 정말 나한테 큰 상처가 될 거야, 너도 알잖아.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "아, 저 자식! 이건 정말 악랄한 협박 수법이군!.. 자, 선장, 어떻게 할 거야? 선택할 건가, 아니면 저런 놈한테 협박당할 거야?";
			link.l1 = "그럼 네 생각은 어떠냐? 내 생각엔 네가 나랑 바세테르로 같이 가게 될 것 같은데.";
			link.l1.go = "citizen_19";
			link.l2 = "내가 여기서 선택권이라도 있나?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "아, 실망시키게 되어 유감이오, 선장. 나는 당신의 아름다운 배에 오를 생각이 전혀 없소. 여기서는 힘으로 아무것도 얻을 수 없을 것이오, 이곳은 경비병들이 둘러싸고 있고, 당신이 폭력적인 의도를 보이면 나는 곧바로 도움을 청할 것이오. 물론, 나를 찌르려 할 수도 있겠지만, 우리 좋은 친구는 차가운 시체에게서 동전을 얻을 수 없을 것이오. 그러니 지금 당신이 할 수 있는 가장 현명한 선택은 나를 그냥 두고 떠나는 것이오. 내가 무사히 가도록 허락하겠소.";
			link.l1 = "지금까지 일어난 일 다 보고 내가 그냥 물러날 거라고 진짜 믿는 거냐? 이 난장판에 날 끌어들인 건 너잖아, 이 망할 놈아, 이제 대가를 치를 때다!";
			link.l1.go = "citizen_20";
			link.l2 = "네 말이 맞는 것 같군. 너를 찌르는 상상은 마음에 들지만, 아무 소용도 없지. 이게 끝이라고는 꿈도 꾸지 마라. 난 이제 바로 바스테르로 간다. 거기서 우리 좋은 친구에게 네 소식을 전해줄 거야. 그러면 그가 가면 쓴 놈들을 네 뒤로 보낼 테니.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "아-악! 군인들! 도와줘!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "물론이지. 네 상사에게 가면 쓴 놈들 좀 조심시키라고 전해라 – 요즘 내가 꽤 인기 많거든. 잘 가라, 선장.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "잠깐! 항복이야! 항복한다고!";
			link.l1 = "좋아, 이제 무기 내려놓고 배로 걸어가!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "항상 선택지는 있소, 선장님. 내가 알기로는, 그 은행가의 위협이 없었다면 나를 쫓지 않았을 텐데?";
			link.l1 = "정확히 그렇다.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "좋아. 그럼 네가 저 자식 입을 확실히 막을 방법을 마련해 주지. 네 고용주에게 가져갈 편지를 써 주겠다. 그에게 전해라. 만약 그가 입을 열기 시작하면, 과들루프 총독이 코리지, 즉 대량의 다이아몬드를 운송하던 특사 루거선의 실종을 계획하고 자금을 댄 인물에 대해 알게 될 거라고.";
			link.l1 = "흠. 이제야 이해가 되기 시작하는군, Pinette 나리.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "그렇게 똑똑해서 다행이군, 선장. 드 리옹이 만약 커리지호 실종의 진실을 알게 된다면, 그 교활한 구두쇠의 머리를 직접 도시 성문에 못 박을 거야. 내가 곧 쓸 이 편지에는 협박꾼을 진정시킬 증거가 들어 있을 거다. 펜 좀 꺼내게 잠깐만 기다려.";
			link.l1 = "좋아...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(글을 쓰며) 자, 받아. 이 꾸러미 안에 비슷한 편지가 두 통 들어 있어. 하나는 은행가에게 줘서 실컷 즐기게 해. 나머지 하나는 네가 가지고 잘 숨겨 둬.";
			link.l1 = " 그 정보 믿을 만한가?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "맹세하네, 자네가 날 도와줬으니 이제 내가 자네를 도와주지. 안심하게, 이 유언장을 읽으면 협박꾼도 자네를 더 이상 건드리지 않을 걸세. 아, 맞다... 한 가지 더 있네, 선장. 우리가 평화롭게 해결했으니... 내 비밀 은닉처가 하나 있는데, 앞으로 내 일에 관여하지 않겠다고 약속하면 그 위치를 알려주지. 어차피 그놈들은 나를 과들루프에 다시는 못 들어오게 할 테니까.";
			link.l1 = "편지가 의도한 대로만 된다면, 그건 내가 반드시 약속할 수 있지.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "그럼 그렇게 하지. 과달루페 동굴 안 바위들 사이를 찾아봐. 네 수고에 대한 소박한 보상이라 생각하게. 행운을 빌네, 선장.";
			link.l1 = "당신도 마찬가지요, Pinette 나리.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "안녕하시오, 나리! 당신이 선장이오 "+GetFullName(pchar)+", 맞지?";
			link.l1 = "맞아. 뭘 도와줄까?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", 바스테르 은행장이 가능한 한 빨리 당신을 찾아오라고 했소. 당신이 도착하는 걸 놓치지 않도록 매일 우리 항구 사무실을 확인하라고 내게 명령했소.";
			link.l1 = "흥미로운데, 그가 왜 그렇게 나를 보고 싶어 하는 거지?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" 직접 그 이유를 말해줄 거야. 그의 초대를 거절하지 않길 바란다.";
			link.l1 = "흠... 좋아. 저 은행가들은 힘 있는 놈들이라서 하찮은 놈들한테는 시간 낭비 안 하지. 최대한 빨리 그 사람을 만나러 가볼게.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "감사합니다, 선장님. 안녕히 가십시오!";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "아르! 이 쓸모없는 놈들! 이게 우연한 만남일 리가 없지...";
			link.l1 = "그 말이 맞아, 장... 아, 미안, 후안이라고 해야겠군. 내가 널 찾아냈지. 이제 내 화물칸으로 좀 옮겨주겠나? 기분 좀 풀고 나서 얘기하자고.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "나는 내 몫을 다 했어. 이제 네 차례야. 해, 그리고 거짓말의 대가가 뭔지 명심해.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "버트랑 피네트는 바베이도스의 주요 플랜테이션에 있을 거야, 좀 더 구체적으로 말하면. 그는 거기서 계속 일을 할 계획이었지. 그 플랜테이션의 감독관이 그의 친구야.";
			link.l1 = "무슨 작전 말이야?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "과달루프에서 하던 거랑 똑같지. 반쯤 합법인 무역, 밀수, 노예. 내 생각엔 저 자식 노예랑 설탕 장사를 하려는 것 같아. 아니면 대체 왜 플랜테이션으로 옮겼겠어?";
			link.l1 = "알겠네. 그 자가 영국 당국 중에 후원자가 있나?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "그런 것 같아. 참 별난 녀석이지. 어디서나 친구가 많더라고.";
			link.l1 = "또 뭐 필요한 거라도?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "뭐처럼? 교활하고 영리하지, 항상 뭔가를 알고 있고, 항상 비장의 수를 숨기고 있어. 더 알아볼 시간은 별로 없었어.";
			link.l1 = "알겠다. 좋아, 나는 브리지타운으로 항해해야 해. 이제 가도 된다, 돈 후안. 피네트에게 경고할 생각은 꿈도 꾸지 마라. 거기서 그자를 못 찾으면, 다시 네 목이 위험해질 테니까.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "미안하다, 친구. 개인적인 감정은 없어. 네가 너무 많이 알아버렸지, 그게 문제야.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
