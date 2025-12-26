void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "무슨 일이십니까?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "내 집에 온 걸 환영하네, 신사 여러분. 무엇을 도와드릴까?";
			link.l1 = "르바쇠르가 안부를 전하라고 했소, 나리.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "그런 거였군... 알리시아! 잠깐 나가 있거라. 이 신사분들과 나 사이에 볼일이 있네.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "하지만...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "사랑해, 자기야. 어서 가!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_1");
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "놀라운 일이로다, 주님! 세상 끝에서 인생의 사랑을 찾기 위해 모든 것을 잃을 만한 가치가 있었소! 신사 여러분, 이제 나는 여러분의 것이오. 혹시 우리 거래를 할 수 있을 것 같지는 않소?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "아니, 그리고 자비를 구하려고도 하지 마.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "기사단의 기사라면 자비를 구하는 건 어울리지 않지.";
			link.l1 = "그래도 예전에는 기사였지.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "관료들이 내게서 그 칭호를 빼앗으려 해도, 세상의 모든 잉크가 모자랄 걸.";
			link.l1 = "그렇다면 증명해 봐. 하지만 먼저 내 호기심을 좀 풀어주지. 자네, 왕실에 반역한 자인가? 그렇지 않으면, 왜 르바쇠르가 자네 목숨을 그토록 원했는지 이해가 안 되거든.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "나는 내 맹세에 충실하오, 나리. 그러니 나를 탓하지 마시오. 다만 한마디만 하겠소. 왕관에 반역한 자가 또 다른 반역자를 제거하라고 나를 보냈소. 그리고 나보다 더 유능한 형제가 성공할 때까지 그는 계속 이런 짓을 할 거요. 말은 이쯤 하지. 신사 여러분, 전투로!\n";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_2");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "아아! 오, 고마워요, 선장. 그 녀석 진짜 만만치 않았어. 나 혼자선 절대 못 이겼을 거야.";
			link.l1 = "이 승리가 그다지 기쁘지가 않군. 이제 여기서 끝난 건가?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "아직 아니야, 먼저 2층으로 재빨리 도망친 그 여자애부터 처리하고 정리해야 해.";
			link.l1 = "뭐?! 물러서! 제정신이야, 클로드? 난 도살자가 아니라고!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "아무것도 할 필요 없어, 선장. 게다가 이건 다 선장 잘못이야. 그 여자한테 르바쇠르 얘기를 꺼내지 말았어야지.";
			link.l1 = "그건 말도 안 되는 소리라는 거, 너도 알잖아. 그리고 또 한 번 그렇게 횡설수설하며 나를 나무라면, 이번엔 그냥 넘어가지 않을 거야.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "헤! 내 실수요, 선장. 맞아, 르바쇠르의 명령엔 기사뿐만 아니라 그 일행 전부를 처리하라고 분명히 적혀 있었지. 전부 말이오, 알겠소? 저 인간들은 만만하게 볼 상대가 아니니, 그 요구도 진지하게 받아들여야 해. 내 일 방해하지 마시오, 선장. 마지막 더러운 일 한 번만 더 하면, 그땐 끝까지 당신 곁에 있을 거라 맹세하오!\n";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(신뢰) (명예) 예전에 내가 높이 날 운명이라고 하셨죠, 그리고 그걸 위해 힘을 보탤 수 있어서 기뻤다고 하셨고요.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
			}
			link.l2 = "꺼져라! 네 더러운 일이나 해라. 네 맹세는 받아들이겠다, 하지만 죽을 각오로 지켜라. 서로 이해한 거지?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "이 값으론 안 돼, 클로드. 그 소녀를 죽이게 두지 않을 거야.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "헤! 결국 우린 서로 죽이게 되어 있었던 거지, 그치, 선장?";
			link.l1 = "그런 것 같군. 토르투가에서 멈췄던 데서 다시 시작하지, 어때?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_3");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "알겠소, 선장님!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_4");
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "끝났어, 선장. 그 여자, 나도 놀랐지...";
			link.l1 = "그 얘긴 듣고 싶지 않아. 나는 약속을 지켰어. 이제 네 차례야.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "금도 좋지만, 평범한 용병을 위해 자기 목숨을 거는 건 훨씬 더 값진 일이죠. 끝까지 함께하겠습니다, 선장.";
			link.l1 = "그렇다면, 여기서 끝이군.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "알겠소.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_5");
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "내가 그랬지. 그래서 뭐 어쩌라고, 선장?";
			link.l1 = "그 말이 허튼소리가 아니었다는 걸 증명해 봐. 내 팀에 들어오고 싶어? 앞으로의 전리품을 나누고 싶어? 내 명령을 따라. 그 여자 건드리지 마. 왜냐고? 그렇게 하지 않으면 넌 영원히 도살자일 뿐이고, 난 그런 놈을 둘 자리가 없으니까.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "이게 우리 둘이 두 번째로 목숨을 걸고 싸우는 거군, 선장\n그리고 또다시 네 혓바닥 재주 덕분에 네가 이겼어! 하하! 네 말이 맞아! 뭐, 그 여자애는 집어치우지. 난 결국 짐승이니까. 선원으로 받아줄래?";
			link.l1 = "어서 와, 클로드. 이번엔 진짜로.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "알겠소, 선장님!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_6");
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "무슨 일이 생겼어, 선장.";
			Link.l1 = "짐작컨대, 또 사직하겠다고 협박하면서 임금 인상 요구하려는 거지?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "헤! 이번엔 아니야... 걱정 마시오, 선장님. 돈만 주신다면, 합리적인 선에서야 언제든 당신 편이지. 그게 우리 용병 형제들이 살아남는 유일한 방법이거든. 그리고 우리 중 최고라고 해도 결국 푼돈이나 받지.";
			link.l1 = "그냥 바로 본론으로 들어가면 어때?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "토르투가에서 만난 그 계집 기억나?";
			link.l1 = "마르셀린? 총독 부인 말인가? 그런 여자는 잊을 수 없지.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "나는 우연히 르바쇠르의 집에 온 게 아니야. 그 악당이자 이단자와 거래가 있었지.";
			link.l1 = "권력자들을 그렇게 깎아내리며 말하다니, 클로드, 좀 이상하군.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "어? 허! 르바쇠르는 악마야! 그 자는 자기 밑에서 먹고사는 해적들보다도 훨씬 더 악질이지!";
			link.l1 = "방금 네가 직접 그 자와 거래했다고 했잖아. 그거 좀 위선적인 거 아니냐?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "나는 천사가 아니야, 선장. 나는 시키는 대로 사람을 죽이고 그걸로 먹고살지. 그래서 나를 그렇게 중하게 여기는 거 아니겠어?\n하지만 나 같은 놈도 르바쇠르 소굴에서 토르투가 여자들에게 무슨 짓을 한다는 소문을 들으면 등골이 오싹해진다니까!";
			link.l1 = "소문 따위엔 관심 없어. 이 사람은 귀족이자 국왕의 신하니까, 존경받을 자격이 있지.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "그래서 자네가 이 왕의 하인을 털고, 그의 아내까지 건드렸다고? 허! 마음대로 하시지, 선장. 본론으로 들어가자고. 각하께서 나에게 어떤 자를 찾아 죽이라고 명하셨지. 뭐, 이런 일은 내겐 흔한 일이야. 물론 이렇게 높은 분이 직접 의뢰하는 경우는 드물지만 말이야.";
			link.l1 = "그래서 뭘 원하지? 풀어줘서 네가 약속 지키고 이 사람을 죽이게 하라고?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "이 일, 선장, 당신이 도와줬으면 해. 토르투가에서 내 처지가 나빠졌을 때 당신 밑에 들어오기로 했지만, 이 일 끝내기 전엔 마음이 편치 않아. 레바쇠르가 알게 되면 날 죽일 거야. 게다가, 일을 끝까지 안 하는 건 프로답지 않지.";
			link.l1 = "고객의 아내와 관계를 맺는 게 과연 프로답다고 할 수 있을까? 이런 부탁을 당신 입에서 듣게 되다니 참 이상하군, 특히 우리 대화의 시작을 떠올려 보면 말이야. 그때 당신은 우리 관계의 본질을 아주 정확히 짚었지. 금을 위한 피, 그렇지?\n";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "나를 도와주면 내 칼만 얻는 게 아니야, 내 충성도 함께 얻게 되지. 한눈에 봐도 넌 크게 될 운명이야, 선장. 내가 그 길에 힘을 보태주면 기쁘겠어.";
			link.l1 = "인정하지, 너 같은 실력자가 내 등 뒤를 지켜주는 게 훨씬 낫지. 네가 찾는 그 목표는 어디서 찾을 수 있지?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "지금은 네 검이면 충분해. 나는 암살자가 아니야. 긴장 풀어, 장교!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "알겠소, 선장. 그래도 한번 물어볼 만했지.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_1");
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "헤헤! 그게 문제야, 선장. 내가 아는 건 그자가 몰타 기사단 출신의 전 기사라는 것뿐인데, 지금은 영국 땅 어딘가에서 도망 다니고 있지. 귀족 출신이라서 누추한 오두막 같은 데서 살진 않을 거야.";
			link.l1 = "기사단의 기사인가?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "전직 기사였지. 그래, 그리고 이 일 맡은 걸 천 번은 이미 후회했어. 기사들은 악마처럼 싸우니까, 네 검 실력이 제대로 시험받을 거라고 장담한다.";
			link.l1 = "마음에 들진 않지만, 한번 해보자고. 그러니까: 가난뱅이도 아니고, 귀족인데다가 영국 놈들하고 숨어 있다? 르바쇠르는 왜 저 자를 처리해야 하는지 말하지 않았나?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "당연히 안 하지! 하지만 이건 분명 정치적인 문제야, 아니었으면 병사들을 보냈겠지.";
			link.l1 = "해보겠지만, 장담은 못 하겠어.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "고마워요, 선장님.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_2");
		break;
		
	}
} 
