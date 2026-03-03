// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
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
			dialog.text = "명백한 버그다. 개발자들에게 알려라.";
			link.l1 = "그래, 그렇게 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", 선장님. (경례) 제 소개를 하겠습니다 - 중위 "+GetFullName(npchar)+", 세인트 존스에 주둔 중인 앤티과 해병 연대 소속이오. 부탁이 하나 있소.";
			link.l1 = "안녕하십니까, Gretton 중위. 제 이름은 "+GetFullName(pchar)+". 무슨 부탁인데?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "상황을 간단히 설명하겠소. 내 부하 넷과 나는 세인트 존스에서 신트마르턴으로 항해 중이었는데, 폭풍이 우리 배를 덮쳤지. 악천후는 오래가지 않았지만, 그 정도로도 우리 낡은 배에 물이 새기 시작했소. 그래서 진로를 바꿔 이곳에 정박해 수리를 하게 되었지. 하지만 이 일로 시간이 너무 지체되고 있소\n우리는 신트마르턴, 그중에서도 그랑 카스 해변에 서둘러 가야 하오. 도와주시오, 선장. 충분히 보답하겠소. 이틀만 항해해 주면 넉넉한 보수를 드릴 테니!";
			link.l1 = "후하게 보수를 줘야겠지, 중위. 내가 영국 해병들을 네덜란드 섬에 몰래 들여보내길 원한다면 말이야.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", 이건 너랑 상관없는 일이야. 넌 위험하지 않아. 그냥 만에 우리를 내려주면 그걸로 끝이야. 자, 거래하는 거지?";
			link.l1 = "좋아, 나도 끼지. 여기서 그렇게 멀지 않잖아. 그 보수에 대해 들어보자.";
			link.l1.go = "seafox_3";
			link.l2 = "미안하지만, 나는 다른 곳에 급한 일이 있어서 네덜란드인들을 괜히 건드리고 싶지 않네.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "말씀대로 하겠습니다, 선장님. 그럼 계속 찾아보겠습니다. 안녕히 계시고, 신의 가호가 함께하길!";
			link.l1 = "안녕히 가시오, 중위.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "만 피스 오브 에잇 만 개다. 여기 선금이다.";
			link.l1 = "좋아. 네 놈들 배에 태워, 시간 낭비하지 말자.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "순조로운 항해에 감사드립니다, 선장님! 정말 죄송하지만, 지금 당장 당신께 돈을 드릴 수가 없습니다... 이 근처에 우리 루거선 한 척이 있어야 했는데, 보시다시피 없네요. 한 번만 더 도와주셔야겠습니다. 이 만에서 이틀이나 사흘만 기다려 주실 수 있겠습니까? 우리가 주변을 좀 살펴보고 와야 합니다. 돌아오면, 우리를 앤티가로 데려다 주십시오. 폭스 대령께서 넉넉하게 보상해 주실 겁니다.";
			link.l1 = "흠... 이게 우리가 약속한 거랑은 좀 다른데...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "실망하지 마십시오, 선장님. 선장님의 심정은 이해하지만, 유감스럽게도 지금은 돈이 전혀 없습니다. 그러나 두 번의 항해와 이곳에서 우리를 기다려준 것에 대한 보상, 그리고 폭스 대령 본인의 감사까지 반드시 받게 될 것임을 약속드립니다!";
			link.l1 = "너를 완전히 내버려 둘 수는 없지... 좋아, Gretton 중위. 사흘 동안 기다리겠네, 하지만 그 이상은 안 되네.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "감사합니다, "+GetAddress_Form(NPChar)+"! 우리 내륙으로 간다. 맹세컨대 72시간 안에 돌아올 거야, 단 1분도 더 늦지 않겠어.";
			link.l1 = "행운을 빌네, 중위. 잡히지 말게.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "이런 우연이 다 있나! 그랑 카스 해변에서 우리를 기다리고 있을 줄 알았는데, 선장\n "+pchar.lastname+"!";
			link.l1 = "안녕하시오, 중위 나리, 놀란 건 나도 마찬가지요. 그대가 네덜란드 군인처럼 입고 나타날 줄은 몰랐소.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "이건 우리 변장이야... 왜 여기 나와 있는 거야, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "그건 위험한 변장이야, 친구. 첩자들은 재판도 없이 바로 처형당할 수 있지. 그리고 처형 얘기가 나와서 말인데, 네가 네 목숨을 부지하고 싶으면 내 말 잘 듣는 게 좋을 거야.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "전적으로 내 주의를 기울이고 있소.";
			link.l1 = "나는 필립스버그로 항해해서 네가 내린 뒤에 현지인들과 이야기를 나눴어. 네 뒤를 네덜란드 놈들이 쫓고 있어. 그놈들은 네가 붙잡힌 영국 고위 장교들을 구출하러 왔다는 걸 알고 있더라.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "젠장, 망할! 대체 어떻게 이걸 알아낸 거야?";
			link.l1 = "포로로 잡힌 영국 장교 중 한 명이오. 자유를 대가로 구출 작전에 대해 아는 모든 것을 네덜란드인들에게 털어놨지. 필립스버그 전체가 자네와 부하들이 도시로 들어오기를 기다리고 있네.\n설상가상으로, 네덜란드 코르벳 한 척이 신트마르턴 주변 해역을 순찰 중이야. 함정이네, 중위.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"저 비열한 악당 같으니! 내가 그 배신자가 누군지 밝혀내서 의회 앞에 고발하겠소!";
			link.l1 = "그건 나중에 하도록 하지, Gretton 나리. 오늘 밤 Grand Case 해변으로 돌아가서, 그들이 잡기 전에 내 배로 돌아오게.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "그리고 네덜란드 감옥에 영국 신사들을 버리고 오라고? 차라리 죽겠소, 나리. 나는 폭스 대령님을 실망시키지 않을 것이오.";
			link.l1 = "흠, 네가 붙잡히면 네덜란드 놈들이 교수형이랑 총살형 중에서 고르게 해줄 것 같아?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "여기서 그냥 떠나게 놔둘 거라고 생각하지 마시오, de Maure 선장. 우리 둘 다 이 일에 깊이 빠져 있소.";
			link.l1 = "젠장, 네 말이 맞을 거야. 우리가 닻을 올리자마자 저 코르벳이 바로 들이닥칠 테니까...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "네덜란드 놈들이 우리가 온다는 건 알지, 하지만 *어떻게* 오는지는 모를 거야. 변장은 이미 준비해뒀어 – 이 제복 좀 봐. 멋지지 않아? 우리 계획이 배신당하지 않았다면, 그냥 현지 감옥에 가서 기습하고 안에 있는 놈들 전부 죽였을 거야. 하지만 분명 거기서 매복하고 있을 테니, 즉흥적으로 가야지. 선장, 필립스버그 교회로 가서 거기 있는 설교자 필리페 야콥센을 찾아. 그 사람은 아침 여섯 시부터 열 시까지 거기 있을 거야. 필리페는 우리 내부 사람 중 하나야. 그에게 이 암호를 전해: '포로 선원들이 고해한 게 언제였지?'. 그 다음에 상황을 설명하고, 폭스 대령의 이름으로 협력을 요구해. 그리고 그가 뭐라고 하는지 나한테 전해주면 돼. 간단하고, 너한테 위험은 없어.";
			link.l1 = "네덜란드 칼뱅파 교회에서 고해성사에 대해 묻는 건 꽤나 위험한 짓이야, 중위. 목사가 나를 교황주의자라고 목매달려 할걸. 좋아, 그럼 그 제복들에 대해 말해 봐... 이거 네덜란드 순찰대한테서 벗긴 거야?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "예, 나리.";
			link.l1 = "그놈들은 지금 어디에 있지?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "이 동굴에서 멀지 않은 덤불 속에 인질로 잡혀 있다.";
			link.l1 = "알겠다. 이들을 안전하게 지켜. 나는 마을로 들어가겠다. 여기서 기다리면서 몸을 낮춰라 – 네덜란드 놈들도 바다뿐만 아니라 정글까지 샅샅이 뒤지며 너를 찾고 있으니까.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "우린 교회 쥐처럼 조용히 있겠습니다, 선장님. 서둘러 주십시오!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "돌아왔어? 선장, 여기서 뭐 하는 거야? 어서 마을로 가, 우리 은신처가 눈에 띄잖아!";
			link.l1 = "마을에서 돌아왔어. 너희 영국인들은 대체 무슨 장난을 치고 있는 거지?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "뭐라고 했소?";
			link.l1 = "나는 교회에 갔어. 큰 건물에, 멋지고 소박하더라. 딱 그 네덜란드 이콘파괴자들이 좋아할 만한 스타일이지. 있잖아, 중위. 필리페 야콥센이라는 설교자는 없더라고.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "그건 말도 안 돼, 그는 매일 아침 그곳에 들르는데-";
			link.l1 = "닥치고 내 말이나 들어! 네가 말하는 야콥센이라는 놈이 정말 있긴 한 건지도 모르겠지만, 그놈은 교회에 오지도 않아! 아무도 본 적이 없어! 아침에도, 저녁에도! 젠장할! 내가 대체 왜 이런 빌어먹을 일에 동의했지?! 멍청한 창녀 자식에 풋내기, 젖내 나는 중위 따위가 이끄는 꼴이라니-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "나리, 그 모욕에 대한 사과를 요구하오. 여기서 나가면, 관례에 따라 결투를 벌이겠소-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "닥쳐, 다들!!! ... 방금 뭔가 들었어.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "이런, 누가 밖에 있잖아! 이봐! 네가 네덜란드 놈들을 다시 데려왔구나, 이 악당아!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "만나서 반갑소, 나리. 무슨 소식이오?";
			link.l1 = "네 놈 부하를 만났어. 오늘 저녁에 그자가 '맛을 낸' 와인을 감옥 주둔군에게 전달할 거야. 집시한테서 물약을 받았는데, 치명적이진 않지만 마시면 죽은 듯이 잠들 거라고 하더군. 오늘 밤 안에 들어가서 잡혀 있는 신사들을 빼내야 해. 참고로, 그 와인 배달에 내가 25두블룬이나 썼으니 보고서에 꼭 언급해 줘.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "돈 걱정은 하지 마시오. 선장님, 이번 작전에 우리와 함께해 주시고 감옥까지 안내해 주셨으면 하오. 선장님은 필립스버그에 와본 적 있으니 우리보다 도시를 더 잘 알지 않소. 감옥 안까지 들어갈 필요는 없으니, 탈옥은 우리가 알아서 하겠소. 문 앞까지만 데려다 주시오.";
			link.l1 = "제기랄, Gretton 나리, 이 일은 갈수록 더 재밌어지는군. 보수도 그에 맞게 오르고 있겠지?";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "틀림없는 사실입니다, 선장님. 우리를 도와주신 걸 후회하지 않으실 겁니다. 당신 배가 그랑 카스 해변에 있습니까?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "그래.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "아니.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "좋아. 그럼 준비하고 저녁 열한 시까지 마을 입구에서 우리를 만나.";
			link.l1 = "거기서 보자.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "반드시 그녀를 그쪽으로 옮겨라. 우리는 정글을 통해 우리 사람들을 빼내야 하니까. 항구나 심슨 만에서 출항하는 건 요새 때문에 불가능하다. 모든 걸 준비해서 밤 열한 시까지 마을 입구에서 우리를 만나도록 해라.";
			link.l1 = "거기서 보자.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "준비됐소, 선장님?";
			link.l1 = "그래.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "그럼 움직이자.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "쉿... 선장님! 끝났으니, 이제 여기서 얼른 빠져나가요!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "어떻게 해냈는지 모르겠지만, 해냈어! 네 도움이 없었으면 절대 불가능했을 거야, 나리. 이제 비교적 쉬운 일만 남았어 - 살아서, 멀쩡한 몸으로 신트마르턴을 빠져나가야 해. 그랑 카세 해변으로 가자!\n";
			link.l1 = "가자!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Captain "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", 도와주셔서 감사합니다! 제발 부탁이니, 바로 항구를 떠나지 말고 제가 폭스 대령에게 보고할 동안 하루만 더 머물러 주십시오. 내일 그를 찾아가 보세요. 그의 집무실은 총독 관저에 있습니다.";
			link.l1 = "좋소, Gretton 중위. 내 시간을 쓸 만한 가치가 있도록 해 주시오. 자네의 소동 때문에 네덜란드인들 사이에서 내 평판을 회복하려면 오래 걸릴 테니.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "도와주셔서 감사합니다, 선장님! 당신\n "+GetSexPhrase("진정한 영웅처럼 행동했어","아주 용감한 아가씨구나")+", "+GetAddress_Form(NPChar)+"! 그레튼 중위가 살아남지 못했다니 비극이군. 그는 진정한 신사이자 영국의 아들로서 죽었지. 내가 폭스 대령에게 보고하는 동안 하루만 더 머물게 해주었으면 하네. 내일 그를 찾아가 보게. 그의 집무실은 총독 관저에 있네.";
			link.l1 = "좋소. 내 시간을 쓸 만한 보상을 해주시오. 자네 소동 때문에 네덜란드인들 사이에서 내 평판을 회복하는 데 오래 걸릴 거요.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "걱정하지 마, "+GetAddress_Form(NPChar)+". 보고서에 최대한 좋은 평가를 드리겠습니다. (경례) 영광이었습니다, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "흠... 그래, 무슨 일로 왔나?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "항만 사무소에서 당신 배가 최근에 도착했다는 소식을 전해왔소. 필립스버그의 총독 마틴 토마스 나리께서 당신을 뵙고 싶어 하신다네.";
			link.l1 = "무슨 일로? 내가 체포된 건가?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "아니, 아니, "+GetAddress_Form(NPChar)+" 선장님, 체포된 게 아닙니다. 총독께서 새로 도착한 모든 선장들을 궁으로 초대해 커피도 대접하고 인사도 나누라고 명하셨습니다. 저를 따라오십시오!";
			link.l1 = "거절할 수 없는 제안이군. 앞장서.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 네가 그 영국 군인들을 본 곳을 우리에게 보여 줘.";
			link.l1 = "걔네들은 정글에 있는 동굴에 숨어 있어, 그냥 평범한 도적들처럼.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "앞장서라, 우리가 따라갈 테니!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "잠깐만요, 선장님! 저기, 동굴 입구 근처에서 첩자들을 만났다고 하셨죠?";
			link.l1 = "그래. 그들이 나랑 얘기한 뒤에 안으로 들어가는 걸 잠깐 봤어.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "아마 아직도 그 안에 있을 거야. 우리가 한꺼번에 들이닥치면 놈들이 동굴 안으로 도망칠 거고, 거기서 놈들을 끄집어내는 건 악몽이 될 거야... 똑똑하게 가자고. 선장, 자네가 혼자 저기로 가서 놈들 주의를 끌어. 나는 내 부하들과 저 모퉁이의 마른 우물로 이동할게. 그 우물이 동굴 안으로 바로 이어지거든. 놈들은 우리가 뒤에서 오는 걸 전혀 모를 거야\n자네가 안으로 들어가서 첩자들이 아직 있으면, 말도 안 되는 질문을 하면서 놈들을 붙잡아 둬. 놈들 시선을 완전히 끌면, 입에 담을 수 없는 욕을 실컷 해. 자네가 뱃사람이니 그 정도는 쉽겠지. 그게 우리 신호야. 내 부하 두 명이 정문을 지켜서 놈들이 그쪽으로 도망치지 못하게 할 거다. 우리가 놈들을 잡을 거야.";
			link.l1 = "네 계획은 내 건강에 몹시 위험해 보이는데. 내가 보기엔, 쟤네가 제일 먼저 나부터 죽이려고 할 것 같아.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "걱정 마시오, 선장님. 적 습격대가 보이자마자 최대한 크게 소리치기만 하면 되오. 놈들이 공격해 오면 도망치면서 계속 소리치시오. 내 부하들은 잘 훈련되어 있으니 걱정 말고, 당신이 다치기 전에 저 첩자들을 처리할 것이오.";
			link.l1 = "그래야지. 나 들어간다.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "거친 놈들이었지... 잘했어, 선장. 영국 놈들은 끝장났어. 파괴공작원들도 처리됐으니, 사령관이랑 총독이 기뻐할 거야.";
			link.l1 = "참 느긋하게 오셨군, 나리...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "밧줄 탓을 해. 끝에 양동이가 달려 있어서 엄청 시끄러웠거든. 우리는 조심해야 했어.";
			link.l1 = "그래... 밧줄 말이지. 뭐, 됐고. 네가 잃어버린 순찰대 중 한 명이 저기 덤불에 묶여 있어. 아직 살아 있을 거야.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "내가 저들을 처리할게. 너는 마을에 가서 좀 쉬어. 내일 우리 총독을 찾아가 봐. 그때쯤이면 내가 너를 칭찬하는 보고서를 총독께 올려놨을 테니까.";
			link.l1 = "그러지. 행운을 빌겠소, 나리.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "무슨 일로 왔느냐, 아들아?";
			link.l1 = "안녕하세요, 신부님. 그냥 궁금해서 그런데, 포로 선원들이 고해한 지 얼마나 됐습니까?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "어제 저녁이었지, 아들아... (속삭이며) 계획이 배신당한 거, 알고 있겠지?";
			link.l1 = "그렇지 않았다면 내가 여기 이렇게 서 있지 않았겠지. 카스퍼 그라튼 중위와 그의 부하들은 지금 정글에 나가 있어. 전부 네덜란드 병사 복장을 하고 있지만, 감옥 경비병들이 그들을 기다리고 있어서 추가 지원이 필요해.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(크게) 나는 그의 성공회 영혼이 지옥에 떨어지지 않도록 매일 기도했소!\n(속삭이며) 계획이 하나 있소, 하지만 필요한 걸 모두 구하려면 금 더블룬 두 다스가 필요하오.";
			link.l1 = "비싼 계획이군. 돈은 뭐에 쓰는 거야?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "감옥 경비는 정말 지루한 일이야. 사기를 유지하려고 책임 장교가 매일 저녁 식사에 맞춰 와인을 주문하지. 그 와인은 내가 출입할 수 있는 창고에서 가져와. 마을에 내게 신세를 진 집시 여자가 있는데, 그 녀석이 우리를 위해 수면제를 만들어줄 거야. 내가 할 일은 좋은 와인 몇 병을 사서 그 약을 타고, 창고에 있는 병들과 바꿔치기만 하면 돼. 그래서 금화가 필요한 거야.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "도블론은 내가 가지고 있어. 가져가.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "내 배로 돌아가서 너한테 좀 가져올게.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "아, 아들아, 우리가 얘기했던 '기부금' 가져왔느냐?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "그래, 여기.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "곧 손에 넣게 될 거야...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "훌륭하군. 내일 이 시간에 다시 찾아오게 - 결과를 알려주겠네.";
			link.l1 = "좋아...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "안녕하냐, 아들아.";
			link.l1 = "당신도 안녕하시오, 목사님. 소식이라도 있소?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "그래. 끝났어. 포도주에 '맛'을 더해 놨으니 오늘 밤 경비병들은 특별한 대접을 받게 될 거야.\n그들은 밤 아홉 시에 저녁을 먹으니, 자정이면 모두 잠들 거다.\n이번이 일을 할 수 있는 유일한 기회야, 두 번은 없어.\n조심해, 네가 네덜란드인으로 변장했다고 완전히 믿을 순 없으니까.";
			link.l1 = "알겠어. 시간 낭비하지 말자. 잘 있어.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
