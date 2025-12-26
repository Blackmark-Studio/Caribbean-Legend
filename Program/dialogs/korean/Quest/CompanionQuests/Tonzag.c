void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "뭐 원하는 거야?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		case "startoff":
			dialog.text = "드 모르 선장! 토르투가에 온 걸 환영해!";
			link.l1 = "좋은 하루군, 부관. 친구들이랑 바다 경치 즐기고 있나?";
			link.l1.go = "startoff_joke";
			link.l2 = "물러서, 중위.";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "선장님, 당신의 명성은 이미 자자하오. 상부에서 우리 아름다운 토르투가 섬의 경치를 구경시켜 주기로 결정했소. 지금 바로 시작하지, 마을 감옥부터 말이오. 당신의 장교들도 함께 초대되었소.";
			link.l1 = "중위, 나는 해변에서 잡은 더러운 밀수꾼 따위가 아니야. 농담은 집어치워. 제대로 설명해.";
			link.l1.go = "startoff_joke_1";
			link.l2 = "그럼 시간 낭비하지 말자! 앞장서라, 부관!";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "너희 선원들을 상대하려면 다른 방식이 필요하겠군. 병사들, 전투 준비해라! 드 모르 선장, 그리고 당신과 당신의 장교들은 체포된다. 무기를 내려놔라!";
			link.l1 = "총알 한 방 줄 수 있지, 어디 맞고 싶어, 중위? 너희 육지 쥐들한텐 달리 방법이 없어.";
			link.l1.go = "startoff_silence_1";
			link.l2 = "무슨 법으로? 무장한 무리를 피 한 방울 안 흘리고 잡고 싶다면, 중위, 좀 더 노력해야 할 거다.";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "나한테는 너희 전부 다 똑같아... 미안하지만 설명은 없어, 선장. 윗선의 명령이야. 무기를 내놔, 순순히.";
			link.l1 = "지금은 문제 일으키기 싫어... 시키는 대로 해.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "어... 내 말을 제대로 못 알아들은 것 같군. 선장, 너와 네 장교들은 체포됐다! 무기를 내려놓고 우리와 함께 가라!";
			link.l1 = "지금은 문제 일으키고 싶지 않아... 시키는 대로 해.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "한 마디만 더 해 봐, 선장. 여기서 바로 묻어줄 테니까. 무기 내려놔, 당장!";
			link.l1 = "지금은 문제 일으키고 싶지 않아... 시키는 대로 해.";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "나는 피 따위 두렵지 않아, 선장. 네가 기적적으로 살아남는다 해도, 다시는 토르투가 땅을 밟지 못할 거야. 그리고 우리 군 정보부는 네가 이 섬에 드나드는 걸 아주 중요하게 여긴다고 생각하지.";
			link.l1 = "지금은 문제 일으키고 싶지 않아... 시키는 대로 해.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "선장, 상황이 엿같아요! 적이 우리를 꽉 조이고 있어서, 우리가 죽을 때까지 절대 안 놔줄 것 같아요! 우리 사람들이 지금 진짜 위험에 처했고, 대포 사수들 대부분이 쓰러졌어요!";
			link.l1 = "내가 놈들을 도울게. 네가 지휘해서 여기서 나가자!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "예, 나리!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "승리입니다, 선장님! 상륙대는 전멸했고, 적은 후퇴를 선택해 남쪽으로 향했습니다. 배 상태는 양호합니다. 생존 선원:\n " + GetCrewQuantity(pchar) + " 사람들. 보고 완료했다!";
			link.l1 = "고맙다! 모두에게 럼을 돌리고, 항구에 도착할 때까지 경계를 강화해라!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "만세! 알겠어!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "그리고 저기 그 놈이 직접 나타났군! 밖에서 피비린내 나는 학살을 봤냐? 이 모든 게 다 네 짓이야, 배신자 놈! 하지만 다 대가를 치르게 될 거다: 포르토 벨로, 그루오, 그리고 이 광산까지!";
			link.l1 = "잠깐, 그게 무슨 뜻이야...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "악! 이거 영 불길한데...";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "산 산티아고여, 나를 지켜주소서! 악행이로다! 대체 어떤 괴물이 이런 짓을 저지를 수 있단 말인가? 대답해라, 나리!";
			link.l1 = "진정해, 나리! 먼저 네 소개부터 해라! 그래, 여기서 끔찍한 학살이 벌어졌지. 하지만 그 짓을 한 놈들은 이미 다 죽었어. 내가 직접 그놈들 시체로 광산을 '장식'해 놨거든...";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "나는 " + GetFullName(npchar) + ", 왕립 로스 테케스 광산의 수석 기술자다. 나는 몇 달간의 임무를 마치고 막 돌아왔는데... 이게 대체 뭐지! 여기서 벌어진 일은 신과 인간에 대한 범죄다. 그러니 즉시 무기를 내려놓으라고 명령한다. 카라카스 당국이 이 악행을 조사할 것이다!";
			link.l1 = " 나는 따를 수 없어, 나리, 그리고 이 학살과는 정말 아무 상관도 없어! 하지만 계속한다면, 네 시체도 저 더미에 얹히게 될 거다.";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "나는 죽음을 두려워하지 않지만, 언제 물러나야 할지는 항상 안다. 가라. 하지만 기억해라, 여기서 무슨 일이 있었는지 내가 모두 보고할 거다. 한 치의 사실도 빼놓지 않을 테니!";
			link.l1 = "그건 동의 못 하겠군, 나리. 이렇게까지 오게 되어 유감이야. 싸울 준비해!";
			link.l1.go = "mine_head_fight";
			link.l2 = "죽고 싶어서 설치는 거냐, 나리. 하지만 오늘은 아무도 더 죽지 않는다. 우리는 떠난다, 그리고 이 점도 네 보고서에 꼭 적어두길 바란다!";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "그 죄수는 어떻게 할까요, 선장님?";
			link.l1 = "별거 없어, 그냥 그 자식이 죽거나 도망치지 않게만 해.";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "알겠소! 오늘 심문에는 내가 끼지 않아도 되는 거요, 선장?";
			link.l1 = "왜 안 되겠어? 직업을 바꾸기로 했나, 알론소?";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "하하, 아니오, 선장님. 이 일 정말 좋아하지만, 이제 배에 새로운 전문가가 탄 것 같군요!";
			link.l1 = "에르퀼? 그 생각은 어디서 난 거지?";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "그래, 선장. 그 영감이 일부러 공구함을 챙겨와서 제대로 써먹었지. 나는 내 거 꺼낼 필요도 없겠더군. 하!";
			link.l1 = "알겠다... 원래 하던 대로 해!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "아... 샤를 드 모르. 전 연맹 전체를 대표해서 사과를 드리오. 당신을 건드리지 말라는 명령이 우리에게 너무 늦게 도착했소. 우리 조직은 당신에게 아무런 원한도 없소, 선장. 하지만 이 대머리 짐승에 대해서라면... 쳇! 이 자가 당신 밑에 있는 한은 안전하겠지만, 내 조언은 저 놈을 곁에 두지 말고 원래 있던 시궁창에서 썩게 내버려 두라는 것이오!\n";
			link.l1 = "추천은 고맙지만, 네 용병들로부터 누가 나를 지켜주고 있는지 그 이유가 더 궁금하군.";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "알 수 없어, 선장. 아마도 우리 새 후원자한테서 지시가 내려온 거겠지. 들어봤냐, 배신자? 이제 연맹이 다시 우두머리 자리에 올랐거든!";
			link.l1 = "그리고 그는 누구지?";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "알 수 없습니다, 선장님, 그리고 설령 안다 해도 그런 건 밝히지 않습니다.";
			link.l1 = "그렇다면, 다른 얘기를 해 봐. 그러면 네가 원하는 곳으로 가도 돼. 내 말은 지킬 거다.";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "그냥 이렇게 끝내자는 건가? 좋아, 선장. 물어볼 거 있으면 물어봐, 그리고 날 보내줘. 맹세컨대, 설령 돌아갈 수 있다 해도 난 리그로 돌아가지 않겠어.";
			link.l1 = "왜 그렇게 에르퀼에게 집착하는 거지? 탈영병 하나 때문에 너무 호들갑 떠는군.";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "뭐라고 말했지, 이 개새끼야? 모든 게 겉보기와는 달라, 선장! 리그는 끊임없이 움직이고, 암호도 바뀌고, 고용주도 달라진다. 나가고 싶어? 물론이지! 출구는 상급 장교들만 막혀 있고, 이 쓰레기는 한 번도 그런 적이 없어. 그의 아내는, 그래, 하지만 우리는 톤자가 부인을 너무 존중해서 그녀만큼은 예외로 뒀지.";
			link.l1 = "그럼 왜?";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "포르토 벨로에서 일이 하나 있었지... 그건 정말 컸어. 네 친구는 그냥 떠난 것도, 계약만 깬 것도, 일을 끝내러 온 무리를 죽인 것만도 아니었지. 거리에서 진짜 학살을 벌여서 우리와 카스티야 놈들 사이를 아주 복잡하게 만들어 놨어. 그날 착한 가톨릭 놈들이 겪은 만큼의 공포를 뿌린 해적 습격은 드물지. 젠장, 그 짓을 다른 놈이 했으면 나도 감탄했을지 모르겠군.";
			link.l1 = "또 학살이냐? 흥미롭군. 계속해라.";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "그 당시 회사의 부국장이었던 로덴부르크가 개입했지.\n그가 어떻게든 모든 일을 무마하긴 했지만, 스페인 측의 징벌 작전 때문에 우리 최고의 인재들 중 많은 이들을 잃고 말았어.\n시간이 좀 흐른 뒤엔, 다시 그들과 거래를 시작했지...\n하지만 아무것도 잊지 않았고, 기회가 오자마자 복수하려 했어.\n모든 일의 주동자였던 톤자가 반드시 죽어야 했지.";
			link.l1 = "그건 실패했군. 광산은 어떻게 됐지?";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "우린 어쩔 수 없이 그렇게 했어. 그 쓰레기들을 치우는 데 너무 많은 돈이 들었지; 금이 필요했거든. 전부 그 놈 때문이야... 하지만 암살 시도는 실패했고, 나는 정리 좀 하려고 로스 테케스로 돌아왔지... 어떻게 내가 어디에 있는지 알아냈지?\n";
			link.l1 = "상관없다. 네 우두머리를 만나야겠다. 너희 수수께끼 같은 후견인의 보장이 언제든 사라질 수 있으니, 오해는 내가 직접 풀고 싶다.";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "카라카스에서 이미 당신을 기다리고 있을 거라 확신하오, 선장. 보시오, 나는 당신에게 아무것도 숨기지 않소.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "아르노 사령관이 죽었고, 이제 오스틴이 지휘하고 있어.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "네 질문엔 다 대답했어, 선장. 약속 지켜.";
			link.l1 = "내보내주지. 내 배에서 내려. 그리고 카라카스에서 나를 노리는 매복이 없기를 빌어라.";
			link.l1.go = "captive_spare";
			link.l2 = "흥미로운 대화였어. 내가 광산에서 본 걸 생각하면, 학살의 원인을 에르퀼 탓으로 돌리는 건 좀 지나쳤지. 네가 있을 곳, 지옥으로 꺼져라.";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "신사 여러분, 회의에 초대받으셨습니다. 교회에서 기다리고 있으니 안전은 보장됩니다.";
			link.l1 = "빠르군...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "샤를 드 모르. 에르퀼. 넌 여기서 살아나가지 못할 거다.";
			link.l1 = "대화를 시작하기엔 참 좋은 방법이군. 이 모든 게 정말로 필요하냐?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "너랑은, 선장, 일이 그리 간단하지 않아. 있잖아, 우리 새 주인은 널 그냥 내버려 두라고 고집했지... 근데 그딴 부탁은 엿이나 먹으라지! 난 네 부류가 아주 질색이야! 너희들은 하얗고 예쁜 돛 아래 항해하면서 입에 얼음도 안 녹을 것처럼 굴지. 하지만 내 칼날이 네 몸에 박히면, 다들 계집애처럼 비명을 지르더군. 그게 참 재밌다니까, 찰스, 내가 말해주지! 오랜만에 이런 짓을 하네... 그리고 지금 내 눈앞에 네가 있잖아, 잘생긴 놈아.";
			link.l1 = "너 아프구나, 이봐.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "아니, 널 보낼 수는 없다. 하지만 네 친구라면 얘기가 훨씬 간단하지. 내 부하들에겐 그 녀석이 필요 없거든. 다만, 그 녀석의 옛 리그 동료 몇 놈이 내 방식이 효과적인지 아직 확신을 못 하고 있지... 너무 깨끗하게만 일해왔으니까, 깨끗한 두블룬, 깨끗한 회사에서 말이야. 하지만 놈들 생각을 바꿔줄 방법을 나는 잘 알지. 대담한 죄인 한 놈의 머리를 쟁반에 올려주면 되거든, 하하!";
			link.l1 = "그딴 짓 하려고 여기 온 거라면 잘못 찾아왔군, 미친놈아. 진짜로 교회에서 싸움이라도 벌이겠다는 거냐?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "그래, 왜 안 되겠어? 사람들 불쌍하다고? 로스 테케스만큼 돈이 되진 않겠지만, 그래도 재밌게 놀 수 있지. 신의 집 벽을 피로 물들여 보자고, 아하! 선장, 물감은 넉넉히 준비해 주겠지.";
			link.l1 = "알겠다. 우리를 부러워하지, 이 미친 쥐야? 우리의 자유가 부러운 거냐? 여자들이 우리를 보면 기뻐하고, 주머니엔 동전이 짤랑거리니? 네 꼴 좀 봐라. 네 주인놈들이 널 어디서 파냈냐, 돼지야? 누가 널 교회에 들여보냈지?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "땅이나 처먹어라, 이 쥐새끼야!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 
