// Арчибальд Колхаун
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
			dialog.text = "필요한 것이라도 있소?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "하, 드 모르 나리! 포트 로열에 오신 걸 환영하오! 아직도 나를 기억하시오?";
			link.l1 = "흠... 당신이 칼훈 나리로군요? 헨리 칼훈 맞습니까?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "거의 맞았어... 아치볼드 칼훈.";
			link.l1 = "아, 용서하시오, 나리. 맞아요, 기억납니다. 우리는 카포 카토체, 만에서 만났었지요.\n당신과 함께 있던 선장은 윌리엄 패터슨이었고, 그의 함대도 알아보았습니다.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "정말 맞는 말씀이오! 우리 선장을 용서해 주시오. 모르는 사람에게는 항상 무례하게 굴거든. 디에고 데 몬토야의 요새를 번개처럼 쳐부순 솜씨, 정말 훌륭했소. 우리도 그 요새에서 한껏 발톱을 갈았었지...";
			link.l1 = "정의를 위해서라는 점도 덧붙이겠소. 당신네 선장이 미리 준비해 두지 않았다면, 내가 스페인 대포 사격 속에서 상을 차지하러 달려갈 수 있었을지 의문이오. 당신네 지휘관은 자기가 찾던 것을 발견했소?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "그래. 그는 요새 아래에 있는 카스마트 깊숙이 파고들어서 무슨 기록 보관소 같은 걸 찾아냈지. 말로 다 할 수 없을 만큼 만족해하더군. 그런데, 실례가 안 된다면 묻고 싶소, 정글에 있는 그 요새를 공격하게 된 계기가 무엇이오?";
			link.l1 = "생피에르에서 나에게 패한 뒤, 돈 디에고는 음모를 꾸미더니 결국 쿠바를 노골적으로 공격했지. 그러고는 전투를 중단하고 산악 지대로 도망쳐 본토 쪽으로 사라졌어. 그래서 나는 그 겁쟁이 놈을 완전히 없애기로 결심했지. 다시는 프랑스의 명예를 더럽히지 못하게 말이야.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "그래, 샤를 드 모르 선장의 무용담에 대한 전설 같은 이야기들을 꽤 들었지. 이제는 내 두 눈으로 직접 보았군...";
			link.l1 = "그래, 나도 윌리엄 패터슨의 용맹에 대해 몇 가지 들은 적이 있소. 당신은 그 같은 선장을 둬서 운이 좋군.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "운이 좋군, 그건 사실이지. 요즘 그 친구는 아주 대단한 인물이 되어버렸어. 상류층, 연회, 무도회, 퍼레이드, 사적인 파티까지… 우리가 포트 로얄에 도착할 때마다 총독 관저에서 꺼낼 수도 없지. 사실 지금도 거기 있을걸.\n샤를 드 모르 선장, 스코틀랜드 주정뱅이에게 한 번 호의를 베풀어줄 수 있겠나? 내 동료가 되어 함께 이야기 좀 나누자고! 맨날 똑같은 얼굴만 보는 것도 지겹고, 자네는 말동무로 괜찮아 보이네. 내 집에 와서 쉬면서 훌륭한 위스키 한 통 같이 하세. 내가 쏘지!";
			link.l1 = "음... 솔깃하긴 한데, 하지만...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "아이고 그만하시죠, 선장님. 가끔은 선장님도 쉬셔야죠. 그런데 말인데, 내가 현지 상점에서 바로 가져온 훌륭한 에피타이저가 좀 있어요. 상점 바로 위층에 방을 빌렸거든요. 언제든 뭐 좀 먹거나 한잔하고 싶으시면 아래층으로 내려오기만 하면 돼요, 하하! 편리하지 않아요? 자, 갑시다!";
			link.l1 = "나도 모르게 넘어가 버렸군!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "좋아. 따라와!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "여기 얼마나 좋은지 보시죠? 시원하고... 여기 위스키 통도 있소! 자, 선장, 원샷이오!";
			link.l1 = "자, 우리의 우연한 만남과 즐거운 인연을 위해 한잔하자!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "기쁘구려!... 아! 최근에 카리브에 도착하셨지요, 드 모르 나리?";
			link.l1 = "비교적 최근에... 아니면 생각보다 오래전일지도 모르겠군. 어떻게 말해야 할지 잘 모르겠어. 내 인생의 절반을 여기서 산 것 같은 기분이야.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "오, 그 기분 나도 잘 알지... 나도 여기서 오래 있었으니까. 그리고 윌리엄이 날 구해줬던 그 빌어먹을 섬에 상륙했을 때... 오호, 거기서 내 인생 절반은 작별 인사를 한 기분이더라고.";
			link.l1 = "흥미롭군! 어느 섬이었지?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "윌리는 내 오랜 친구야. 내가 아직 스코틀랜드의 맑은 공기를 마시던 시절부터 알던 사이지... 좋은 시절이었지. 내가 어리석게도 저 빌어먹을 교황파 놈들과 심지어 종교재판관하고까지 다투는 바람에, 그놈이 날 죽이려고 사람을 보냈어. 그때 나는 상인이었고, 내 플루트선도 있었지. 에휴, 그 재수 없는 날 스페인 놈들이 해적 복장으로 내 배를 공격했어. 우린 용감하게 싸웠지만, 결국 쥐처럼 몰려버렸지! 그래도 그때도 콜혼 영감은 침착함을 잃지 않고, 물통 하나랑 널빤지 몇 개 들고 바다로 뛰어들었어. 나는 어둠을 틈타 병사들 눈에 띄지 않고 배에서 헤엄쳐 나왔지. 살아남을 확률은 별로 없었지만, 배에 남아 있으면 아예 기회조차 없는 거였으니까. 이틀 뒤, 나는 어느 무인도 해변에 떠밀려 왔어. 그때쯤이면 카리브에서 좀 살고 있었지만, 그 섬은 그때까지 한 번도 들어본 적이 없었지! 작고 완전히 사람이 없는 곳이었어... 그리고 거기서 2년을 보냈지, 영원처럼 느껴졌던 시간이었어. 아직도 어떻게 정신줄을 붙잡고 있었는지 모르겠다.";
			link.l1 = "너는 사람이 없는 섬에서 2년이나 살았다고?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "그럼, 저주받은 곳이지! 다행히도 맑은 물이 있었어. 나는 게, 따개비, 물고기, 새를 먹고 살아남았지. 그래서 그 섬을 게섬이라고 이름 붙였어. 무기도 없어서 야만인처럼 작살, 창, 화살을 익혔지! 오호! 마셔, 마셔, 선장! 나도 한 잔 걸치는 거야, 뭐...";
			link.l1 = "그래... 나는 네가 부럽지 않아.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "자, 바로 그거야! 내가 처음 그 커다란 모래섬 해변에 발을 디뎠을 때 딱 이렇게 말했지: '늙은 아치, 네 처지가 부럽진 않지만, 그렇다고 완전히 절망적인 것도 아니야!' 그리고 선장, 내 목숨을 붙잡아 준 게 뭔지 아시오?\n";
			link.l1 = "섬을 지나가는 배라고?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "아니오! 고된 노동이 나를 살렸소! 노력과 신앙, 그리고 살고자 하는 의지 덕분이었지! 나는 섬 전체, 구석구석을 탐험했고, 그 보상으로 목수 도구와 필기구, 그리고 자잘한 것들이 가득 든 궤짝을 얻었소. 그 순간 내가 스스로에게 뭐라고 했는지 아시오? 더 부어라, 선장, 그냥 더 부어!\n나는 이렇게 말했지. 아치, 마음을 굳건히 하려면 일해야 하고, 신께서 시작할 모든 것을 주셨다! 이제 알겠소? 나는 만 근처에 집을 짓기 시작했는데, 그게 나를 어두운 생각에서 구해주고, 살아갈 이유를 주었소!";
			link.l1 = "당신은 살아 있는 영감이십니다, Calhoun 나리. 그런 상황에서 뭐라도 할 수 있는 사람이 많지 않을 텐데요...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "그래, 늙은 칼하운이 스코틀랜드에서 태어난 데는 다 이유가 있지! 맞아! 우리는 산의 아들들이야 – 강하고, 용감하고, 억세지. 그 늪지대 약골들보다 훨씬 낫지. 더 따라라... 맞다, 내가 무슨 얘길 하고 있었더라? 그래! 나는 열심히 일해서 제법 괜찮은 집도 지었어. 또 내 불운한 일상들을 적으려고 일기장도 쓰기 시작했지. 윌리가 날 구해줬을 때 그 일기장도 챙겼어. 지금은 여기 이 탁자에 두고, 포트 로얄에 머물 때마다 따뜻하고 푹신한 침대에서 다시 읽곤 해. 그 안에 내가 그곳에 가기 전과 후에 일어난 모든 일을 다 적어놨어. 그게 내가 아직 정신을 붙잡고 있는 이유 중 하나지.";
			link.l1 = "그래서 결국 패터슨 나리가 너를 그 섬에서 데려갔단 말이오? 그런데 그가 어떻게 그 섬을 찾았지? 네가 말하길...\n";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "그래, 그래, 그 섬은 어떤 지도에도 표시되어 있지 않아. 하지만 윌리, 그 사람은 늙은 윌리잖아! 뭐든지 할 수 있지! 그가 그 빌어먹을 섬을 찾아냈고, 나를 구해줬어. 그래서 나는 평생 그에게 감사할 거야. 그래...";
			link.l1 = "패터슨 나리 밑에서 일하는 게 즐거우시오? 다시 한번 스스로의 힘으로 떠나보고 싶지 않소?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "이제 독립적인 삶은 질렸어. 윌리는 젊고 성공했지, 그리고 나도 오랜 친구고. 내가 더 뭘 바라겠어? 아니, 난 내 남은 인생을 윌리와 함께할 거야, 아니면 적어도 내가 또 만취해서 쫓겨날 때까지는 말이지, 하하! 술 얘기가 나왔으니, 한 잔 따라 줘!\n";
			link.l1 = "아흑...(술 마시며) 말해보시오, 칼훈 나리. 듣자하니, 자네가 예전에 보물 사냥꾼이었다던데, 사실이오? 아니면 그냥 헛소문이오?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "누가 그걸 말해줬지? 뭐, 이제 숨길 필요도 없군. 나도 한때 그랬어. 하지만 결과는 좋지 않았지. 바로 그 보물 사냥 때문에 저주받은 예수회 놈들과 그 섬에 얽히게 됐거든. 신부 놈들이 내 탓에 한 남자를 고문해서 죽였고, 나 자신도... 아, 과거는 과거로 묻자고.\n나는 내 죗값을 충분히 치렀고, 앞으로는 다시는 그런 일이 없길 바란다네. 아니, 윌리라면 절대 그런 일 못 하게 할 거야, 분명히!";
			link.l1 = "이봐, 아치볼드. 미겔 디초소라는 남자에 대해 들어본 적 있나?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "그 이름은 처음 듣는데. 누구지?";
			link.l1 = "아, 별로 흥미로운 사람은 아니야... 그냥 모험과 보물을 쫓는 걸 즐기는 남자일 뿐이지. 하지만 네가 그 사람을 들어본 적 없다면, 더 이상 얘기하지 않겠다.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "그래, 그러지 말자! 대신 옛 유럽 이야기를 하자고! 이십 년 전 스코틀랜드에서 있었던 일이 생각나는군...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
