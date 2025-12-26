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
			dialog.text = "뭘 원해?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"이봐, 여기 좀 봐!";
			link.l1 = "조용히 해, "+npchar.name+", 우리만 여기 있는 게 아닐 수도 있어.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"응? 여기까지 날 따라온 거야?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "그리고 내 생각이 맞았던 것 같아, 알지! 여기서 무슨 일이 있었던 거야?";
			link.l1 = "알았더라면, "+npchar.name+", 알았더라면 말이야...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "세상에...";
			link.l1 = "그래, 불쌍한 녀석이 죽기 전에 고생한 것 같아. 아무도 그런 최후를 맞을 자격은 없지...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "저기 있는 사람이 그녀 남편이야? 대체 정글에서 뭐 하고 있었던 거지?! 도망친 노예들 얘기 못 들었나?";
			link.l1 = "이제 그 질문에는 더 이상 대답할 수 없을 거야...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "이 짓을 한 사람이 아직 근처 어딘가에 있다고 생각해?";
			link.l1 = "그럴 수도 있지. 그러니까 조용히 하자 – 우리가 그들을 먼저 발견해야 하니까.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "이미 늦었어, "+pchar.name+". 벌써 들킨 것 같아. 저기 좀 봐.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "자, 자, 얘들아, 이것 좀 봐라. 꼭 연인들의 아지트 같지 않냐, 헤헤. 두 사랑꾼이 막 세상을 뜨자마자 또 다른 커플이 그 자리를 차지하러 나타났네...\n";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "아주 똑똑하네. 그런데 셈도 못 해? 저 불쌍한 사람들과 달리, 우리 여기 혼자가 아니거든.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "음, 우리랑 상대하는 건 좀 더 복잡할 거야, 그건 믿어도 돼...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "네가 저놈들보다 똑똑하다고 말해주고 싶지만… 그건 새빨간 거짓말이야. 네놈들 숫자가 많아도, 저 악당들을 이기진 못했을 거야. 그리고 네 옆에 있는 예쁜 아가씨도 지금 네 발밑에 누워 있는 저 여자처럼 됐겠지...\n";
			link.l1 = "도망친 노예들 말하는 거야? 이 사람도 그 중 하나야? 그러면 너희는 비숍 쪽이구나?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "네, 네 질문 전부 맞아. 이틀 넘게 군인들이랑 섬 전체를 뒤쫓았지. 그러다 그 놈들이 흩어졌어. 일부는 동굴 쪽으로 도망쳤고, 경비병들이 뒤쫓았지. 나머지는 만으로 튀었고. 여기서 서쪽으로 반 마일쯤 되는 곳에서 놈들이 우리를 기습해서 몇 명을 잃었어. 우리가 다시 모이고 상황을 파악하는 사이에, 놈들은... 그 어리석은 여자애를 자기들 멋대로 했지...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "이빨 쑤시는 막대기는 네 주머니에나 넣어 둬, 멋쟁이. 내 신경이나 우리 녀석들 신경 긁지 말라고. 만약 네가 우리가 만에서 쓰러뜨린 그 놈들 열두 명한테 둘러싸였다면 얼마나 잘 버틸 수 있을지 한번 보고 싶군. 그 중 한 놈만 운이 좋았지—하지만 오래 가진 못했어... 그 자식이 주교 손에 넘어가는 순간...\n";
			link.l1 = "그래서 너희가 그 자의 용병들이야?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "글쎄, 분명히 주둔군 병사들은 아니지. 그 게으름뱅이들만 아니었으면, 어제 그 악당들을 잡았을 거고… 그 바보랑 그의 아내도 아직 살아 있었을 텐데...";
			link.l1 = "그래서, 이건 네가 한 짓이 아니구나...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "우릴 뭘로 보는 거야, 응? 그래, 우리 천사는 아니지. 하지만 기분 내키면 창관에 가지, 그치만...\n";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "저 자식 입만 열면 거짓말이야, 완전 더러운 악당이지! 저 놈 말 듣지 마, "+GetAddress_Form(NPChar)+"! 우리 그 불쌍한 사람들한테 손가락 하나도 안 댔어!";
			link.l1 = "오, 정말이야? 그런데 우리가 왜 그 사람 말이 아니라 네 말을 믿어야 하지?";
			link.l1.go = "Naemnik_8";
			link.l2 = "알지? 아니면 결국 거짓말하는 쪽이 너인 거 아냐? 내 눈엔 너, 전혀 성인처럼 안 보여.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "아, 제발 좀 스스로 생각 좀 해봐! 우리가 그 괴물 같은 비숍 놈한테서 도망치느라 이틀이나 정글을 헤매며 흔적을 지웠는데, 그게 다 뭐 때문이었겠어? 이제 와서 불쌍한 여자를 욕보이고, 그 피 빨아먹는 놈들에게 쫓기게 하려고? 내 친구들은 간신히 그 해변까지 기어왔어, \n "+GetAddress_Form(NPChar)+"! 우리는 머스킷을 쏠 힘조차 없었어, 아니었으면 저 악당들이 그런 짓을 하도록 절대 두지 않았을 거야... 전부 그놈들이었어, 우리가 다 봤다니까!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "아, 제발 네가 좀 생각 좀 해봐, 알지? 우리가 그 괴물 같은 비숍 놈한테서 도망치느라 이틀이나 정글에서 흔적을 감추며 지냈잖아 – 그게 다 뭐 때문이었겠어? 이제 와서 불쌍한 숙녀를 욕보이고, 그 피 빨아먹는 놈들한테 따라잡히려고 그런 거야?! 내 친구들은 간신히 그 해변까지 기어 나왔단 말이야, "+GetAddress_Form(NPChar)+"! 우리는 머스킷을 쏠 힘조차 없었어, 그렇지 않았다면 저 악당들이 저런 짓을 하도록 절대 두지 않았을 거야... 전부 그놈들 짓이었어, 우리가 다 봤다고!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "닥쳐, 캐스퍼, 이 더러운 똥개야!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "뭐라고 했어?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "귀 먹었어, 아가씨? 내가 저놈 입 다물라고 했잖아. 우리 제리는 허풍 떠는 데는 선수라서 몇 시간이고 떠들 수 있다니까! 주교님이 저놈 혀를 잘라서 자기 입에 쑤셔 넣으라고 할 뻔했는데, 결국 불쌍해서 봐주셨지. 내 생각엔 그게 오히려 아쉬운 일이야!\n";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "하지만... 너 그 사람을 캐스퍼라고 불렀잖아, 알지...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "이봐, 친구, 네 애인한테 좀 설명해 줘. 사람들은, 이런 꼬마 같은 쓰레기라도, 이름 말고도 성이 있다는 걸. 예쁜 여자들이 멍청하다는 말은 들었지만, 이런 젠장...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "그 말값은 톡톡히 치르게 될 거야, 알지!";
			link.l1 = "메리, 잠깐만! 내가 직접 처리할게. 무기 집어넣어. 지금 당장.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "오, 여기 진짜 신사가 계셨네. 뭐, 당신 예의가 그 찌질이의 비명보다는 훨씬 낫군. 그 녀석은 불쌍한 자기 마누라보다 더 크게 소리질렀다니까 – 저 언덕 뒤에서도 들릴 정도였어. 솔직히, 그 녀석 덕분에 우리도 좀 편했지 – 그 소리 덕에 그 자식들을 찾아냈으니까...\n";
			link.l1 = "여기 카리브에서는 귀족이란 정말 드문 존재야. 자, 모두 숨 좀 돌리자—지금 당장 여기서 죽는 건 전혀 고귀한 일이 아니거든.";
			link.l1.go = "Naemnik_17";
			link.l2 = "여기서 진짜 악당들은 너희들이야. 지금 당장 메리에게 사과해, 그러면 피 보는 일은 없을지도 몰라.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "그 말엔 반박하기 힘들지. 하지만 먼저, 진정 좀 해...";
			link.l1 = "그녀의 이름은 메리 캐스퍼야. 그거면 많은 게 설명되지.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "캐스퍼? 걔가 그의 딸이라도 되는 거야, 하하?";
			link.l1 = "나는 그 말을 정말 믿기 힘들어. 하지만 이제는 네가 이해했으니, 네 말을 거둬들이길 바래.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "돌아왔어? 아니면 뭐야? 나한테 결투라도 신청할 건가? 해봐... 네 소중한 사람을 정글 한가운데 혼자 두는 게 두렵지 않다면 말이지, 헤헤. 우리 녀석들은 그런 상황이라면 아주아주 환영이지.";
			link.l1 = "봐, 네 본색이 드러났네. 가면은 오래가지 못했지.";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "너, 이봐, 참 모순덩어리구나 – 그렇게 평화로우면서도 이렇게 무례하다니. 그리고 대체 왜 내가 이 빨간 머리 미치광이한테 용서를 빌어야 하지?\n";
			link.l1 = "그녀의 이름은 메리 캐스퍼고, 그리고...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "캐스퍼? 이런, 이럴 수가! 제리, 혹시 네 딸이냐, 응? 하하하하! 내 귀를 의심하겠네! 누가 이런 걸 상상이나 했겠어!";
			link.l1 = "웃을 수 있을 때 실컷 웃어봐. 너 같은 놈들, 입만 살고 교양이라곤 없는 놈들은 여자를 함부로 대하고 그걸 놀이쯤으로 생각하지. 헛간에서 태어나 자칼한테 키워졌나 보지? 네 버릇을 보면 딱 그렇군. 뭐, 머릿속에 짚밖에 안 들었으니 예의 따위 들어갈 자리가 없겠지.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "그래, 그래... 참 건방진 꼬마 벌레로군. 말해 봐, 친구야, 네 여자는 해먹에서 좀 괜찮은 편이냐? \n뭐, 나는 좀 의심스럽긴 한데... 직접 확인해 보면 좋겠군.";
			link.l1 = "봐, 결국 본색을 드러내는구나. 가면은 오래가지 못했네.";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "정말 제대로 한 방 먹였네, "+GetAddress_Form(NPChar)+", - 저 악당들. 지옥에서 불타길 바란다! 내가 제때 도와주지 못해 정말 아쉬워. 여기 오는 길에 봤던 머스킷은 너무 멀리 있었어. 우리가 목숨 걸고 도망칠 때 우리 쪽 누군가가 떨어뜨린 것 같아. 나도 그 자식 프리머를 내 손으로 쏴버렸으면 좋았을 텐데.";
			link.l1 = "프라이머가 너를 정말 힘들게 했나 보네, 네가 다시 돌아올 결심을 했으니.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "그건 아주 약하게 말한 거야. 그 놈 때문에 내 등에 흉터가 잔뜩 생겼지. \n제일 끔찍했던 건, 그 자식이 마음만 먹으면 우리한테 물을 안 줄 수 있었다는 거야.";
			link.l1 = "저 놈들 중에 한 놈도 살아남지 못했다니 아쉽군. 곧 올 병사들에게 넘겨줄 수도 있었을 텐데.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "왜 그런지, 음, 잘 모르겠어, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "음, 있잖아... 사령관이 그에게 자백을 강요했을 거야, 그러면 네 이름이랑 죽은 친구들의 이름도 깨끗해졌을 텐데.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "응, 알았어, 하하. 그러고 나면 윌리엄 비숍이 내 가죽까지 벗겨버리겠지. 그거, 플랜테이션에 있던 흑인한테 다 들었어... 비숍은 네가 흑인이든 백인이든 상관 안 해 – 도망자라면 똑같이 빠르게 처리하거든. ";
			link.l1 = "네가 어떻게든 플랜테이션으로 돌아가야 할 것 같아...";
			link.l1.go = "Djerry_5";
			link.l2 = "그래서 너는 플랜테이션으로 돌아가지 않겠다는 거야?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "너 정말 농담 잘하네 – 그런 말 들어본 적 있어, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "농담 아니야, "+npchar.name+". 내가 여기 우연히 오게 된 줄 알아? 네 놈들 무리를 쫓아 정글로 들어갔지. 전부 끌고 농장으로 돌아가서 금화 좀 챙기려고 말이야. 하지만 남은 건 너 하나뿐이야. 혼자선 별 가치도 없으니, 어쩌면 그냥 놔줄지도 모르지. 그런데 말해 봐, 무슨 생각이었지? 넌 혼자야. 나머지는 다 죽었어. 도대체 뭘 바라는 거야, 이 자식아? 계속 언덕이랑 덤불에 숨어 있다가 총알에 맞아 죽든, 열병에 쓰러지든, 재규어한테 잡아먹히든 그럴 셈이냐?\n";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "너 정말 농담 잘하네 – 그런 얘기 들어본 적 있어, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "농담 아니야, "+npchar.name+". 네가 내가 여기 우연히 오게 된 거라고 생각해? 나는 네 무리를 쫓으려고 정글로 들어갔고, 너희 전부를 농장으로 끌고 가서 금화 몇 닢 챙기려고 했지. 하지만 이제 남은 건 너 하나야. 너 혼자서는 별 가치도 없으니, 어쩌면 그냥 놔줄지도 모르지. 그런데 말해 봐, 무슨 생각이었지? 넌 혼자야. 나머지는 다 죽었어. 도대체 뭘 하려고 하는 거냐, 이 자식아? 계속 언덕이랑 덤불에 숨어 있다가 총알에 맞아 죽거나, 열병에 쓰러지거나, 재규어한테 잡아먹힐 때까지 버틸 셈이냐?\n";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "이게 더 나아, 신만이 아시지, "+GetAddress_Form(NPChar)+" - 내 생각엔, 그게 주교가 나한테 준비했던 온갖 고문으로 죽는 것보단 훨씬 나은 운명이야. 근데 솔직히, 그렇게 나쁘진 않아 – 너덜너덜한 곶 근처에 돛단배 한 척 숨겨 놨어.";
			link.l1 = "바베이도스에서 가장 가까운 땅은 원주민이 사는 도미니카와 스페인 사람들이 있는 토바고야. 어느 쪽이 너한테 더 나쁜지조차 모르겠네...\n";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "난 돈놈들이랑 한 번 부딪혀 볼 생각이야 – 밀수꾼이랑 해적들이 토바고에 자주 닻을 내리거든. \n아, 그 못마땅한 표정 보이네, "+GetAddress_Form(NPChar)+". 하지만 나는 내 나라를 충실히 섬겼어. 그런데 나라가 나를 채석장에 내던졌을 때, 내가 뭘 어쩌라는 거였겠어?";
			link.l1 = "난 판단하는 거 아니야, "+npchar.name+". 모두 각자의 길이 있는 법이지. 이제 화약이랑 탄환을 더 챙기고, 가. 군인들이 오기 전에.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "감사해, "+GetAddress_Form(NPChar)+". 그리고 너, 아가씨, 어, 메리. (고개를 숙인다). 물론, 우리는 친척은 아니지만, 이런, 어, 상황에서 같은 성을 가진 사람을 만나다니... 정말 예상치 못한 일이군, 그리고...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "그런 것 같아, 알겠지. 그리고 이제, 잘 가, 제리.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 무슨 일 있어? 네 동명인에게 너무 빨리 작별 인사를 했잖아.";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "나는 그냥 그 남자랑 최대한 빨리 떨어지고 싶었어... 걔 얘기는 허점투성이야, 알지?";
			link.l1 = "무슨 소리야, 자기야?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "주교의 앞잡이한테서 들은 걸 생각하면, 그 불쌍한 영혼들은 분명히 그 자의 손에 죽었을 거라고 의심할 여지가 없어. 하지만 그 전에... 캐스퍼, 네 그 사람이 뭐라고 했는지 듣고 있었어?";
			link.l1 = "뭐가 마음에 안 들었어, 자기야?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "그가 해변에 숨겨진 보트가 있다고 주장해. 하지만 플랜테이션에서 도망친 사람이 스무 명이 넘거든. 그러니까 그 보트 꽤 커야겠지, 맞지? 제리는 해군 탈영병이야, 혼자서 큰 배를 다루는 게 얼마나 힘든지 잘 알거든, 알지...";
			link.l1 = "돛만 올리고 방향만 잡으면 돼 – 나머지는 바람이 알아서 해줄 거야. 물론, 진짜 위험한 도박이긴 하지. 그래도 어쩌면, 바다에서 죽는 게 플랜터의 사형수로 죽는 것보단 나을지도 몰라.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "아마도. 하지만 이제 보니 뭔가 또 맞지 않는 게 있어... 그의 말로는, 그와 친구들이 멀리서 용병들이 그 불쌍한 소녀를 학대하는 걸 지켜봤다고 하거든...\n";
			link.l1 = "죽을 힘을 다해 자기 배로 도망치는 대신에... 그래, 네가 무슨 말 하려는지 알겠어, "+npchar.name+"... 혹시 캐스퍼 씨에게 몇 가지 질문을 더 해봐야 하지 않을까...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " 이봐, "+npchar.name+", 옛 친구! 잠깐만 기다려...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " 젠장!!! 메리, 조심해!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "비열한 악당! 우리가 그 자의 목숨을 구해줬는데, 그 놈은! 그게 무슨 의미야,\n "+pchar.name+"그래서... 그런 거였어...";
			link.l1 = "아아, "+npchar.name+", 여기서 무슨 일이 있었는지 진실을 아는 사람은 이제 아무도 남지 않았어...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "여기서 나가자, "+pchar.name+". 여기서 병사들이 우리를 찾으면, 큰일나.";
			link.l1 = "맞아, 메리. 가자...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "있잖아, "+pchar.name+"이렇게 다 끝나고 나니까, 진짜 한잔 하고 싶네, 알지?";
			link.l1 = "그 말엔 이견 없어, 자기야. 나도 한잔 하고 싶거든. ‘Irish Cuckold’에 들르자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "깨워서 미안해요, 선장님...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "그래도 최소한 노크는 했네, 그거면 됐지. 이제 말해봐—나한테 뭘 원하는 거야?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "노크할 생각을 해서 다행이야, 친구. 그냥 들이닥쳤으면 지금쯤 계단에서 굴러떨어졌을걸.\n뭘 그렇게 빤히 봐? 말해, 왜 여기까지 기어들어온 거야?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "마을 사람 중 한 명이 당신을 만나고 싶어 해 – 루이스 거넌이야. 중요한 이야기가 있다고 하네.";
			link.l1 = "그 이름은 처음 듣는데. 정말 중요한 일이 있어서 나를 이런... 일에서 불러낸 거라면 좋겠네. 들여보내...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "안녕, 나리 "+pchar.lastname+"... 캐스퍼 양.";
			link.l1 = ""+TimeGreeting()+", 이봐 "+npchar.lastname+". 우리 전에 만난 적 없었던 것 같은데. 그런데 어떻게 우리를 아는 거야?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "기억 안 나? 아, 그렇구나... 내 얼굴에 피랑 먼지가 잔뜩 묻어 있었거든, 나도 몇 시간 전에 거울 속 내 모습을 보고 깜짝 놀랐어...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "너... 너 그 남자 맞지, 알지, 우리가 널 찾아냈고...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "그리고 내 수잔. 불쌍한 수지...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "우린 네가 죽은 줄 알았어. 그리고... 그녀가 네 아내였지, 맞지?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "알겠어요, 나리. 그녀는 제 아내였어요. 저는 두려움에 완전히 얼어붙어서... 아무것도 할 수 없었어요. 이런, 이런...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(흑흑) 나를 때리고 억지로 보게 했어...";
			link.l1 = "일어나, "+GetAddress_Form(NPChar)+". 네 잘못이 아니야. 그 많은 악당들을 상대로 혼자 버틸 수 있는 사람은 아무도 없었을 거야.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "너무 많았어, 정말 많았지... 그래도, 나는...";
			link.l1 = "그래도 당신은 살아남았고, 당신 아내를 죽인 자들은 지옥에서 불타고 있잖아. 작은 위안이긴 해도, 그게 어디야, 나리\n "+npchar.lastname+". 그런데, 너한테 물어보고 싶은 게 있었어...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "알겠어, 이봐 "+pchar.lastname+"?";
			link.l1 = "그 자들은 누구였지? 주교의 용병들이었나, 아니면 도망친 노예들이었나?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "제레미 캐스퍼와 다른 도망자들이었어. 브루스 프라이머와 그의 부하들에 대해서는 네가 틀렸어.";
			link.l1 = "주교의 용병들인가?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "그래. 브루스는 확실히 악당이었고 비숍을 위해 더러운 일도 많이 했지만, 강간범은 아니었어.";
			link.l1 = "그 순간 내게는 그렇게 보이지 않았어. 하지만 너랑은 다투지 않을게, "+npchar.name+". 하지만 너는 의식이 있었고 모든 걸 봤으니까, 일어나서...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "용서해 줘, "+GetAddress_Form(NPChar)+". 나를 한심한 겁쟁이라고 불러도 돼 – 하지만 정말 너무 무서워서 몸이 움직이지 않았어. 그 악당들이 수지랑 내 길을 막았을 때, 처음엔 그냥 목이 터져라 비명을 질렀지, 누군가 도와주러 오길 바라면서.";
			link.l1 = "그리고 그놈들이 너를 두들겨 팼지.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "제리가 자기 머스킷 개머리판으로 나를 내리쳤어, 그리고는 수잔 앞에서 나를 산산조각 내버리겠다고 했지. 나... 이런 말 하긴 부끄럽지만, 솔직히 너무 무서워서 잠깐 정신을 잃었던 것 같아. 그리고 그 순간에...";
			link.l1 = "알겠어, 나리 "+npchar.lastname+". 네가 한 행동에는 부끄러울 게 없어. 네가 겪은 걸 모두가 견딜 수 있었던 건 아니니까. 네가 나서지 못한 건 아쉽지만, 이미 지난 일이야. 그래도 네 아내를 죽인 놈들 중 한 명이라도 저세상으로 보낼 수 있어서 다행이야 – 비록 그 자가 우리를 거의 속일 뻔했지만 말이야.";
			link.l1.go = "Lewis_14";
			link.l2 = "그래서 우리가 주교의 용병들과 싸우다 거의 죽을 뻔한 게, 네가 무서워서였다는 거야? 정말 멋진 변명이네,\n "+npchar.name+". 결국엔 우리가 어떻게든 해결해서 다행이야, 좀 늦긴 했지만...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "그래, "+GetAddress_Form(NPChar)+". 그래서 감사 인사를 하러 왔어. 처음엔 그를 믿었다 해도 말이야...";
			link.l1 = "브루스 프라이머가 그 일이 일어나게 하려고 온갖 짓을 다 했지, 젠장할 놈. 입만 좀 조심했더라면...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "그래, "+GetAddress_Form(NPChar)+". 그 일에 대해 감사 인사를 하러 왔어. 처음엔 그를 믿었다고 해도 말이야...";
			link.l1 = "브루스 프라이머가 그 일이 일어나게 하려고 별 짓을 다 했지, 젠장할 놈. 입만 좀 조심했어도...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "아아, 그날 우리 모두 실수를 했지... 수잔과 나는 너덜너덜한 곶에서 산책을 나가선 안 됐고, 브루스는 입을 조심했어야 했어... 그리고 너도 제레미를 믿지 말았어야 했지. 하지만 캐스퍼 아가씨 덕분에 정의가 다시 세워졌어.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "네가 나한테 뭘 물어보고 싶은지 알 것 같아, 나리\n "+sld.lastname+". 하지만 난 그 남자와는 아무 상관 없어.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "알아요, 아가씨. 이 방에 들어서는 순간 바로 깨달았어요. 당신과 그 사람 사이에는 조금도 닮은 점이 없어요. 그런데도, 수잔은... 이 세상에 우연히 일어나는 일은 없다고 확신했죠.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "네 아내 말이 맞았어. 나도 직접 여러 번 봤거든, 알지. 그리고 "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "너무 맞는 말이야. 하지만 지금은 철학적인 얘기할 때가 아니라고 생각해. 그게 너한테 도움이 될 것 같진 않은데, \n "+npchar.name+". 그런 건 시간만이 해결해 줄 수 있어.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "어쩌면 네 말이 맞을지도 몰라, 이봐\n "+pchar.lastname+". 음, 다시 한 번 감사드리며, 안녕히 가십시오. 당신과 캐스퍼 아가씨를 위해 기도하겠습니다.";
			link.l1 = "몸조심해, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "알아, 자기야, 나도 그 자식 그냥 풀어줄 뻔했어...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "제리 캐스퍼라는 사생아.";
			link.l1 = "그래... 잠깐만... 설마, 그 사람이...라고 생각하는 거야?";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "정말 바보 같게 들리는 거 알아...";
			link.l1 = "당연하지! 그리고 네 성이 스미스나 존스였다면 어땠을까? 그런 이름 가진 사람들이 거리에 셀 수 없이 많잖아, 알지? 그중엔 분명히 나쁜 짓을 하는 사람도 있을 거고... 그리고 그 제리, 지옥불에 타버렸으면 좋겠는데, 알지? 걔는 사실 카스퍼조차 아닐지도 몰라...";
			link.l1.go = "Mary_34";
			link.l2 = "맞아, 자기야. 우리가 아는 한, 걔가 제리였다는 보장도 없어. 가짜 이름 썼을 수도 있잖아.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "그래도... 네가 내 말을 이해하지 못한다는 건 알지만, 만약 그 사람이 네 성을 가졌다고 상상해 봐\n "+pchar.lastname+".";
			link.l1 = "그건 같은 게 아니야, 메리. "+pchar.lastname+" – 는 귀족 가문 성이고, 그리고...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "그래도... 네가 내 말을 이해하지 못하는 거 알아. 하지만 상상해 봐, 만약 그 사람이 네 성을 가졌다면 어떻게 생각할지\n "+pchar.lastname+".";
			link.l1 = "그건 같은 게 아니야, 메리. "+pchar.lastname+" - 고귀한 가문 이름, 그리고...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "그리고 캐스퍼들은, 음, 우리는 이름도 없고, 가족도 없는 그냥 그런 사람들이잖아, 맞지? 네가 나 같은 사람을 알아봐 준 것만으로도 매일 주님께 감사해야 하는 거 아닐까 싶어, 괜히 잘난 척하는 그런 사람들 말고...";
			link.l1 = ""+npchar.name+", 그건 전혀 내가 말하려던 게 아니야 – 너도 그건 알잖아. 귀족 가문 사람들은 피로 이어져 있어 – 단순히 성만 공유하는 거랑은 완전히 다르지. 내가 말했듯이, 성은 그냥 아무나 가져다 쓸 수도 있는 거니까...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "그것 때문만은 아니야, "+pchar.name+"...";
			link.l1 = "자기야, 오늘 하루 정말 길고 힘들었잖아. 우리가 정글을 몇 마일이나 헤매고, 죽을 뻔도 했고... 그러고 나서 잠도 거의 못 잤지. 머릿속에 이상한 생각이 드는 것도 당연해. 우리 둘 다 푹 쉬는 밤이 필요해.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "난 전혀 이상하다고 생각 안 해, 알겠지... 내일 얘기하자.";
			link.l1 = "머리가 맑아야 모든 걸 훨씬 빨리 정리할 수 있어. 누워, 자기야, 오늘은 잊고 넘어가자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "괜찮아, "+GetAddress_Form(NPChar)+"응? 너 얼굴이 이상해, 마치 유령이라도 본 것 같아. 럼 한잔 할래? 아니면 와인? 여기 좋은 술 많으니까, 좀 쉬는 것도 나쁘지 않지.";
			link.l1 = "술 따위는 집어치워. 난 여자를 찾고 있어...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "그럼 잘못 찾아오셨네요, 선장님. 여긴 선술집이지, 사창가가 아니에요. 밖으로 나가시면, 길 건너편에 바로 보일 거예요...";
			link.l1 = "듣지, 지금 농담할 기분 아니야. 나는 빨간 더블릿을 입고 무장한 빨간 머리 소녀를 찾고 있어. 이름은 메리 캐스퍼야.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "음, 농담 아니면 내가 할 말은 없어. 내 근무는 한 시간 전에 시작했는데, 여기서 빨간 코트 입은 빨간 머리는 못 봤어.";
			link.l1 = "그래서 그녀는 밤에 떠난 거야... 하지만 어디로 갔을까?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "좋은 아침이야, 자기야! 꽤 오래 잤네...";
			link.l2 = "정말 나 걱정하게 만들었잖아, "+npchar.name+"...다시는 그렇게 예고도 없이 사라지지 마...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "깨우고 싶지 않았어. 그리고 말이야, 너도 가끔 아무 말 없이 그냥 사라지잖아...";
			link.l1 = "그래서 나한테 똑같이 갚아주기로 한 거야?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "솔직히, 그냥 내 생각을 정리할 시간이 좀 필요했어, 알지. 너 걱정시키고 싶지 않았어.";
			link.l1 = "뭐가 신경 쓰여?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "어제 우리 대화 말이야. 성씨나 혈연에 대해서...";
			link.l1 = "그래서, 결국 나한테 정말 화난 거구나...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "전혀 아니야, 자기야, 그런 뜻이 아니었어. 그냥 갑자기 내 가족에 대해 아무것도 모른다는 걸 깨달았을 뿐이야. 예를 들어 너는 귀족 집안의 아들이잖아. 배에 있는 녀석들도 가끔씩 자기 가족 이야기를 한두 개씩 풀어놓곤 해. 그런데 나는... 들려줄 이야기가 하나도 없어. 부모님도 전혀 몰랐고, 심지어 내가 어디서 태어났는지도 모르겠어...";
			link.l1 = "정의의 섬에서였던 거 아니었어?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "에릭, 나를 키워준 그 남자도 항상 그렇게 말했어. 그런데 그게 사실이라면, 왜 정의의 섬에서 내 부모님에 대해 말한 사람이 아무도 없는 거지? 한마디도, 스쳐 지나가는 언급조차 없었어. 예전에 도널드 그린스펜에게 물어본 적도 있는데, 똑바로 대답해주지 못했지.";
			link.l1 = "아니면 원하지 않았을 수도 있지.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "맞아! 나도 똑같이 생각했어, 알지? 나 예전엔 그냥 아무 생각 없이 살았거든. \n그런데 어제 그 망할 제리랑 마주쳤을 때 말이야... 나 자신에게 물었어—내 아버지는 누구였지? 어머니는? 왜 아무도 내 부모에 대해 말해주지 않았을까, 마치 그분들이 존재하지도 않았던 것처럼? 만약 내 아버지도 그 제리만큼이나 악당이었다면 어쩌지?";
			link.l1 = "전혀 상관없어, "+npchar.name+". 다른 사람들이 널 키웠지 – 그리고 정말 잘해줬어.";
			link.l1.go = "Mary_50";
			link.l1 = "그럴 것 같진 않은데. 그리고 네가 전에는 신경도 안 쓴 거 같은데, 지금 와서 그게 왜 중요한지 모르겠어.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "하지만 나한텐 중요한걸, "+pchar.name+", 알지. 나도 알고 싶어, 내 부모님이 누구였는지 알 권리가 있으니까. 너도 그렇게 생각하지 않아?";
			link.l1 = "당연히 동의하지, 의심의 여지가 없어. 그런데 네 아버지랑 어머니에 대해 뭔가 알아내려면 정의의 섬에서 해야 할 거야. 어차피 너, 부모님 이름조차 모르잖아, 맞지?\n";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "하지만 나한텐 중요한걸, "+pchar.name+"그래, 알겠지. 나도 알고 싶어, 내 부모님이 누구였는지 알 권리가 있다고 생각해. 너도 그렇게 생각하지?";
			link.l1 = "물론이지, 나도 동의해, 의심할 여지 없어. 하지만 네 아버지랑 어머니에 대해 뭔가 알아내려면 정의의 섬에서 해야 할 거야. 결국, 너 그분들 이름조차 모르잖아, 그치?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "아니, 자기야. 그 사람들 이름은 들어본 적도 없는 것 같아, 알지?";
			link.l1 = "그럼 아직 식민지 기록 보관소에 갈 때가 아니야. 먼저, 그 배들의 무덤으로 다시 돌아가서 네 조상에 대한 흔적을 거기서 찾아봐야 해.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "네가 나를 이해해 줘서 기뻐,  "+pchar.name+". 고마워.";
			link.l1 = ""+npchar.name+", 너 정말 나를 놀라게 해, 알지. 이게 내가 너에게 해줄 수 있는 최소한이야, 내 사랑.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "어쩌다 보니 나는 그들에 대해 아무것도 모른 채 거의 이십 년을 살아왔네...";
			// dialog.text = "어차피, 그게 스무 해가 넘도록 나를 괴롭히진 않았으니까...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "그러니까, 나는 좀 더 기다릴 수 있어.";
			link.l1 = "이게 너한테 중요한 일인 것 같네, "+npchar.name+". 그러니까, 너무 오래 기다리게 하지 않을게, 자기야. 이제 가자, 배로 돌아가야 해. 적어도 네가 거기 있다는 걸 알면 마음이 좀 놓일 거야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "고향 해안... 있잖아, "+pchar.name+", 있잖아, 우리가 열 년 뒤에 여기 다시 와도 지금이랑 똑같을 것 같아, 알지?";
			link.l1 = "아마도, "+npchar.name+", 아마도. 안쪽 고리의 배들은 계속 떠 있겠지만, 여기 사는 사람들은 달라질 거야.";
			link.l1.go = "Mary_62";
			link.l2 = "그럴 리 없다고 생각해. 여긴 이미 모든 게 간신히 버티고 있거든. 한 기술자의 천재성 덕분에 말이야.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "그리고 십 년, 십오 년 전에 이 난파선들에서 살던 사람들은 이제 거의 기억도 안 나. 내 곁에 가장 가까웠던 사람들만 기억나지—앨런, 에릭...";
			link.l1 = "그게 그냥 세상 이치인 것 같아. 모든 것, 모든 사람을 다 기억할 순 없는 거지. 나도 이름이랑 얼굴이 점점 기억에서 사라져가, 파리에서 지내던 시절 사람들도 그렇고, 가스코뉴는 말할 것도 없고. 나이 든 사람들만 그런 줄 알았는데, 나도 그러네.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "그리고 십 년, 십오 년 전에 이 난파선들에서 살던 사람들은 이제 거의 기억도 안 나. 내게 정말 소중했던 사람들만 기억나지 – 앨런, 에릭...";
			link.l1 = "그런 게 인생인 것 같아. 모든 것과 모든 사람을 다 기억할 순 없지. 나도 파리에서 지내던 시절의 이름이나 얼굴을 잊어버릴 때가 있어—가스코뉴는 말할 것도 없고. 나이든 사람들만 그런 줄 알았는데, 나도 그렇네.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = ""하지만 이곳은... 완전히 다른 세계 같지 않아? 상상이나 돼? 얼마 전에 여기 도착한 사람들 중 몇몇은 여기서 시간이 본토보다 거의 세 배나 더 빨리 흐른다고 주장한다니까..."\n";
			link.l1 = "하하, 그럼 너 몇 살이 되는 거야?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "나 진지했어, "+pchar.name+", 알겠지!";
			link.l1 = "음, 진지하게 말하자면 이제 본격적으로 일에 들어가야지. \n나왈스 중에 그린스펜보다 나이 많은 사람이 있어?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "음, 아니, 그런 것 같지 않아. 하지만 내가 그 일에 대해 물어봤을 때 그는 아무 말도 안 했다고 이미 말했잖아.";
			link.l1 = "그렇지만, 이십 년 전에 무슨 일이 있었는지 이해하는 데 우리를 도와줄 수 있는 사람이 또 누가 있을지 나는 다른 생각이 없어. 적어도 지금은 말이야. \n그러니까, 우리는 '에스메랄다'로 향할 거야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "아, "+pchar.name+" 그리고 메리, 이게 웬일이야! 둘 다... 살아 있고 멀쩡해서 정말 반갑다, 헤헤. 지난달에만 바깥 고리에 두세 척이 좌초됐어—요즘 바다가 아주 뒤숭숭하거든. 그리고 말인데, 잠긴 문에 막 들이닥치지 마—자물쇠가 박살나면 결국 내가 고쳐야 하잖아. 도널드 만나러 온 거지?\n";
			link.l1 = "좋은 하루 보내, 친구. 우리는 직접 그를 만나러 왔어. 그런데 문이 잠겨 있는 걸 보니, 다른 배로 옮겼거나 옛 친구들을 만나고 싶지 않은 모양이네.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "둘 다 아니야, 하하. 그린스펜은 지금 바깥쪽 고리에서 훈련 중이야.";
			link.l1 = "훈련이라고? 진짜야? 그 사람이 리바도스랑 또 전쟁이라도 하려고 준비하는 거야?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "전쟁은 사실 끝난 적이 없어, "+pchar.name+". 요즘은 예전만큼 싸움이 자주 일어나진 않아. 그래도 산초네 선술집에선 가끔 누군가 얼굴에 주먹을 맞기도 하고... 가끔은 칼이 뽑히기도 하지.";
			link.l1 = "흠, 예전에는 일족 사람들이 선술집에 잘 안 나타났던 것 같은데.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "음, 네가 정의의 섬을 떠난 이후로 몇 가지 변화가 있었어. 도널드랑 에디가 사람들을 그럭저럭 통제하고 있지. 지금은 말이야. 하지만 내일은 어떻게 될지 아무도 모르지 않아? 그래서 옛날 도니가 이 모든 걸 시작한 거야...\n";
			link.l1 = "내가 정의의 섬에서 학살을 막으려고 그렇게 애썼는데, 너 여기서 또 군인 놀이하려고 그랬던 거야? 그리고 걔는 바깥쪽 구역에서 얼마나 오래 어슬렁거리고 있었는데?";
			link.l1.go = "Schmidt_5";
			link.l2 = "훈련이야 좋지, 하지만 이미 위태로운 휴전을 더 위험하게 만드는 거 아니야? 그리고 그린스펜은 도대체 애들을 얼마나 오래 훈련시킨 거야?\n";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "3일이나 지났어. 그는 내일 정오까지 돌아오기로 했지. 저기서 머스킷을 그렇게 닦아대니, 아침이 되면 쏠 것도 남아 있지 않겠는걸! 하하!\n";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "3일이나 지났어. 내일 정오쯤이면 그가 돌아올 거야. 저기서 머스킷을 저렇게 빡빡 닦아대니, 내일이면 쏠 총도 남아나지 않겠는걸! 하하!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "내 선실 아직 'Ceres Smithy'에 비어 있어? 아니면 벌써 누가 들어갔어?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "마지막으로 네가 거기 있었을 때랑 전혀 달라진 게 없어. 문도 아직 열지 않았고. 솔직히 말해서, 그동안 자물쇠 청소나 기름칠도 안 했거든. 그러니까, 부숴야겠다 싶으면 말만 해.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "물론이지. 고마워, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "정말로, 모든 게 예전 그대로야. 내 물건들도 전부 내가 두었던 자리에 그대로 있고... 마치 내가 한 번도 떠난 적 없는 것처럼 말이야... 여기가 바로 너랑 내가 처음 만난 곳이잖아, \n "+pchar.name+". 기억나지?";
			link.l1 = "당연하지! 너 그 둘 정말 잘 처리했잖아, 너 그 둘 정말 잘 처리했어, 나도 잘못하면 토막 날까 봐 걱정했거든.";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "전혀 그런 게 아니었어, 알지! 너 진짜로 나를 죽음의 문턱에서 끌어냈잖아!";
			link.l1 = "운명에 이끌려 여기, 너에게 온 것 같은 기분이야.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "정말 그렇게 생각해, 자기야?";
			link.l1 = "물론이지, 내 사랑. 그리고 그때부터 매일 그 일에 감사하고 있어, 나를 곧장 'Ceres 대장간'으로 데려다줬으니까.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... 처음 나를 봤을 때, 무슨 생각이 들었는지 말해 줄래?";
			link.l1 = "음... 그때 일어났을 때, 내 심장이 가슴에서 튀어나올 것 같은 기분이었던 것만 기억나. 너는 정말...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "뭐?";
			link.l1 = "내가 지금까지 알았던 누구와도 달라. 너의 우아함, 너의 목소리... 그리고 그 빨간 더블릿. 난 처음부터 너한테 당해낼 수가 없었어. 있잖아, 나 예전부터 궁금했어. 왜 드레스나 코르셋이 아니라 빨간 더블릿을 입는 거야?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "나는 아홉 살 때, 바깥 고리에서 그걸 발견했어. 그땐 거기 돌아다니는 걸 정말 좋아했거든—새로운 걸 다 탐험하고, 정의의 섬에선 구할 수 없는 것들, 특히 책을 찾는 게 재미있었지. 그걸 입어보고 싶어서 죽을 지경이었는데, 그땐 너무 커서 나를 통째로 삼켜버릴 것 같았어. 그래서 내가 다른 보물들을 숨겨두던 곳, 물 위로 튀어나온 까마귀 둥지 중 하나에 몰래 감춰뒀지.";
			link.l1 = "그리고 네가 그걸 감당할 만큼 성장하자, 가서 되찾았다는 거야?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "몇 해 전에, 나는 빨간 코트를 입은 대담한 바다 선장에 관한 책을 발견했어. 그는 아무것도 두려워하지 않았지 – 사랑하는 사람을 위해 수백 명의 적과 맞섰거든. 그때 처음으로 더블릿을 입어봤어. 그걸 입으면 용기가 생기는 것 같아.";
			link.l1 = "그리고 그 저항할 수 없는 매력, 자기야! 그런데 있잖아, 지금 내가 원하는 건 딱 하나뿐이야... 네 걸 벗기고 싶어...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "그래서 뭘 기다리고 있는 거야, 내 용감한 선장님?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "좋은 아침이야, 자기야. 나왈들이 방금 '에스메랄다'랑 '산 가브리엘'로 돌아왔고, 도널드도 같이 있어. 내가 보트 중 하나에서 그를 봤거든, 알지?";
			link.l1 = "좋은 아침, 좋은 아침... 솔직히, 그런 밤을 보낸 후엔 정오까지 자고 싶었는데, 너는 벌써 일어나서 여기저기 날아다니고 있네, 알지?";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "어제는 더블릿이랑 돛대 꼭대기, 내가 그걸 숨기곤 했던 곳에 대해 얘기했지... 그런데 갑자기 그 시절이 너무 그리워졌어. 모두에게서 도망쳐서, 저 위에서 조용히 넓은 세상에 대한 책을 읽던 그때 말이야... 참지 못하고 결국 그곳으로 배를 몰았어. 예전엔 거기서 몇 시간이고 보내곤 했는데, 오늘은... 그냥 해 뜨는 걸 바라봤어. 그리고 깨달았지. 세상 그 무엇보다도, 나는 네 곁에 있고 싶다는 걸.";
			link.l1 = "나도 네 곁에 있을게, "+npchar.name+". 자, 도널드한테 갈까? 할 얘기가 아주 많을 거야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", 메리, 반갑구나! 네가 어제 다녀갔다는 얘기는 이미 들었다네. 나도 '케레스 대장간'에 들러볼까 했는데, 이 늙은이보다 먼저 가버렸구나. 아, 내가 네 나이였더라면...";
			link.l1 = "음, 너도 에너지가 넘치잖아, 우리가 이미 봤지? 훈련은 어떻게 됐어?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "생각보다 더 잘 됐어. 적선에 올라타는 연습도 하고, 선실을 습격하는 것도 해봤지... 뭐, 전반적으로 잘 해낸 거야. 물론 내가 녀석들을 좀 빡세게 굴리긴 했지만, 그 애들한테도 좋은 경험이었어. 다리 좀 펴본 게 얼마만인지, 아, 진짜 오랜만이었거든, 하하.";
			link.l1 = "무슨 계기로 그런 대단한 일을 하게 된 거지? 정의의 섬이 너무 조용해서 심심했어?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "흠, 네 목소리에서 못마땅해하는 기색이 느껴지네, "+pchar.name+"... 너도 그럴 만한 자격이 있다고 생각해...";
			link.l1 = "정말로, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "우리가 서로 목을 베지 않으려고 이 썩은 난파선들 사이를 꽤나 뛰어다녀야 했지 – 그건 아직도 잊지 않았어. 아무도 잊지 않았지.";
			link.l1 = "이렇게 내 노력을 보답하는 거야? 역시 사람들이 하는 말이 맞네, 진정한 전사는 평화에 짓눌린다지.";
			link.l1.go = "Grinspy_5";
			link.l2 = "그리고 솔직히 말해서, 나는 해적들이나 리바도스 녀석들보다 네 분별력에 훨씬 더 기대하고 있었어, 알지?";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "내 말 끝까지 들어. 알겠지? 우리가 평화를 지키는 데는 성공했지만, 우리 사이의 차이는 전혀 사라지지 않았어. 적어도 그 검은 피부 이교도들과는 말이야. 바로 지난주에도, 나왈 한 명이 선술집 싸움에서 죽었거든. 하지만 우리도 가만있지 않고 똑같이 되갚아줬지...\n";
			link.l1 = "그래, 그래 - 항상 그렇게 시작하지.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = " 내 말 끝까지 들어. 알겠지? 우리가 평화를 지키긴 했지만, 우리 사이의 차이는 여전해. 적어도 흑인 이교도들과는 말이야. 바로 지난주에도 나왈 한 명이 선술집 싸움에서 죽었어. 하지만 우리도 가만있지 않고 복수했지...\n";
			link.l1 = "알겠지, 항상 그렇게 시작하는 거야.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "네가 두 가지를 잘못 알고 있어, "+pchar.name+". 우선, 이건 시작이 아니라 계속되는 거야. 네가 순진하게 끝낼 수 있다고 생각했다면, 그건 착각이었지. 그리고 두 번째로, 나는 뺨을 또 내밀 만큼 성인군자가 아니야. 흑인들이 또 도를 넘었고, 난 그게 마음에 안 들어. 덱스터도 마찬가지야, 참고로. 하지만 자기가 대단한 정치인이라도 되는 양, 싸움에 휘말리지 않으려고 하더라고. 그래서 곰곰이 생각해 본 끝에, 가장... 고통 없는 방법으로 이 위태로운 평화를 유지하기로 했어.";
			link.l1 = " 네가 리바도스 놈들을 네 작은 훈련으로 겁주기로 한 거야?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "몇 주 전에, 군수품을 실은 영국 갤리온이 바깥쪽 고리에 떠밀려 왔어 – 네가 믿지 못할 물건들이 실려 있었지... 하지만 제일 중요한 건 완전히 새 머스킷총 쉰 자루랑 좋은 화약이었어. 그리고 보트들도 있었지... 페인트가 아직 마르지도 않았더라고! 예전 것들은 다 썩어가고 있었고, 폭풍이 지나간 뒤엔 멀쩡한 보트가 몇 척 남지도 않았거든, 알겠지...";
			link.l1 = "그 모든 게 결국 나왈족의 소유가 된 거야?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "아마 내가 그걸 제독한테도 말했을 거야, 하지만 자기가 제일 똑똑하다고 생각하니까 나도 바보처럼 보이긴 싫거든. 그리고 뭐, 내 계획은 성공했잖아.";
			link.l1 = "블랙 에디가 네 부하들을 더 이상 죽이지 않겠다고 약속하는 편지를 보냈어?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "블랙 에디가 자기 흑인 부하들에게 조용히 있으라고 명령했어. 내가 없는 동안 더 대담해질까 봐 걱정했는데, 오히려 완전히 반대였지. 리바도스 녀석들은 조용히 움츠리고 내 선원들이나 예전엔 종종 괴롭히던 마을 사람들 모두에게서 거리를 두고 있어. 흑인들은 흑인일 뿐이야—힘만 알아듣지. 그게 앨런이 늘 하던 말이었어. 만약 그 말이 틀렸다면 이 배가 지금 당장 바다 밑으로 가라앉아도 좋아!";
			link.l1 = "그리고 얼마 지나지 않아 또 말썽을 피우면, 새 머스킷으로 퓨리호랑 프로텍터호에 납탄을 쏟아부어서 겁을 주려는 거야, 알지?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "생각은 대담하고 무모하지만, 그렇게까지는 안 갈 거라고 봐. 그냥 우리가 그들의 배를 습격할 계획인 척만 할지도 몰라 – 그러면 레이튼이 드디어 용기를 내서 나설 거야. 그 녀석 요즘 좀 우쭐대긴 하지만, 눈치 없는 사람은 아니지. 우리 일족이나 흑인들을 박살내는 건 그한테도 이득이 아니야 – 세 개의 비슷한 세력이 있어야 그나마 균형이 맞거든. 하나가 무너지면 모든 게 바로 엉망이 돼. 그건 분명히 알 텐데 – 그런데 왜인지 내가 그 사람 일을 대신해야 하는 거지.";
			link.l1 = "여기 있는 동안 그를 잠깐 보러 갈 수도 있겠지—물론, 그가 또 훈련을 시작하겠다고 하면 얘기가 다르지만, 하하.";
			link.l1.go = "Grinspy_12";
			link.l2 = "기회가 되면 들러서 그 얘기를 그에게 해볼게. 누가 알아, 어쩌면 들어줄지도 모르지.";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "그를 설득해서 흑인들을 통제하게 만들 수 있는 사람이 있다면, 그건 바로 너야,\n "+pchar.name+". 그런데 너희 얼굴을 보니, 정치 얘기하러 온 건 아닌 것 같은데? 그러니까, 말해 봐, 뭐 원하는 거야?";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "우리 부모님이야, 도널드.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "나는 네가 나에게서 뭘 원하는지 잘 모르겠어, 메리.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "그 사람들에 대해 말해 줘, 제발. 당신은 그들을 알고 있었잖아! 전에 한 번 물어봤는데, 대답 안 해줬잖아...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "그래서 네가 찰스를 여기까지 끌고 온 거구나, 하하하! 너 정말 대단하다, 소녀야, 내가 거짓말하면 벼락 맞아도 좋아! 내가 네 아버지랑 어머니에 대해 한 번도 말하지 않은 건, 그냥 내가 그분들을 전혀 몰랐기 때문이야, 그게 다야!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "하지만 당신이 우리 집안에서 제일 연장자잖아, 알지! 내가 기억하는 한, 당신은 여기 쭉 있었어...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "나는 이 섬에 도착한 게 거의 이십 년 전이야, 네가 태어난 후였지. 그때 넌 아직 아주 작아서, 테이블 밑이나 의자 밑을 뛰어다니고 기어 다니면서 불쌍한 에릭 우데트를 전혀 쉬지 못하게 했지... 물론, 나는 그에게 이렇게 활발한 녀석이 어디서 왔냐고 물어봤어 – 그랬더니 그는 네가 몇 년 전에 이 섬에서 태어났다고만 하더군. 네 아버지나 어머니에 대해서는 한마디도 하지 않았어. 혹시 했다 해도 – 내가 그냥 신경을 안 썼거나, 아예 잊어버렸겠지...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = " 정말 많은 세월이 흘렀네... 알겠어, 도널드, 나도 알아.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = " 에릭이 더 이상 우리와 함께하지 못한다니 아쉽네 - 그는 나보다 훨씬 전에 이곳에 왔었지. \n참, 네가 최근에 벌인 모험들에 대해 얘기할 때마다 오렐리 베르틴 이야기를 자주 했었어. 그 할머니가 널 정말 좋아했거든, 그건 분명히 기억나. \n가만 생각해보면, 네가 태어났을 때 이미 그분은 정의의 섬에 살고 있었던 것 같아. 어쩌면 그분이 널 도와줄 수도 있지 않을까?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = " 아마도. 그녀를 찾아갈 이유가 되겠네. 오랫동안 못 봤거든. 내가 너무 무심했지, 알지!";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "그녀가 너한테 화난 것 같진 않아. 하지만 너무 몰아붙이지 마 – 몸이 안 좋다고 들었거든. 더 안 좋은 일이 생기면 안 되잖아...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "쉿, 도널드, 괜히 우리까지 곤란하게 만들 거야! 오렐리, 우리 모두보다 오래 살 거라니까, 알지?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "가자, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "잘 있어, "+npchar.name+". 곧 보자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "자비로우신 주님, 심장이 가슴에서 튀어나올 뻔했잖아. 그렇게 사람을 놀래키고 다니면 안 되지.";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "질리안! 여기서 널 볼 줄은 몰랐네, 알지? 여기서 뭐 하고 있어? 그리고 오렐리는 어디 있어?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "그래, 너도 안녕, 메리. 그리고 너에게도, "+pchar.name+". 오렐리가 아픈 거 몰랐어? 줄리안 형제 부탁으로 내가 돌보고 있어. 그분이 약을 보내주면 내가 오렐리한테 먹이는데... 별로 효과가 없는 것 같아. 지금은 선미 쪽 선실에서 자고 있어. 내가 여기 정리하려고 거기로 데려다 놨어.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "오늘에서야 알게 됐어, 알지. 도널드가 말해줬거든. 그녀는 어때?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "좋지 않아. 그녀는 몸이 약하다고 불평하고, 침대에서 거의 일어나지도 못해. 가끔은 알아들을 수 없는 말을 중얼거리기도 하고, 무슨 말도 안 되는 소리도 해... 옛날 이야기를 너무 많이 들어서 이제는 셀 수도 없을 지경이야.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "흠, 바로 우리가 들으러 온 그런 이야기군. 그녀가 우리와 이야기하기를 거부하지 않았으면 좋겠는데...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "이게 정말 꼭 필요한 거야, 메리? 그녀가 이런 상태일 때 괜히 귀찮게 하면 안 될 것 같은데.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "이건 내 부모님에 관한 일이야. 오렐리가 그분들을 알았을지도 몰라. 나한텐 정말 중요한 일이야, 질리언, 알지?";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "섬에는 그녀가 나아질 수 있도록 도와줄 약이 없는 거야?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "줄리안 형제가 그녀의 약초액을 만들어. 그런데 그건 잠깐밖에 효과가 없어. 그리고 그마저도 그녀는 마시려고 하지 않아서, 내가 거의 억지로 입에 쏟아붓는 수준이야. 가끔은 그녀가 그걸로 질식할까 봐 무서울 정도야 – 내가 다 삼키게 만들어야 하거든...\n";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "불쌍한 오렐리! 정의의 섬에는 정말 그녀를 도와줄 사람이 아무도 없는 거야?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = " 너도 알다시피 여기엔 제대로 된 의사가 없어. 그리고 어차피 뭘 할 수 있겠어? 노환은 누구도 피해가지 않으니까...\n ";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", 우리 배에서 누군가 데려올 수도 있지 않을까?";
			link.l1 = "무서워,  "+npchar.name+", 여기서 우리에게 필요한 건 배의 외과의가 아니라, 숙련된 의사야.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "지금은 마법이라도 믿을 준비가 됐어, 알지.";
			link.l1 = "흠... 마법이라고? 나, 정의의 섬에서 그런 거 본 적 없는데... 어쩌면 치미셋한테 한번 물어봐야 할까...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "치미셋? 그 흑마법사? "+pchar.name+", 진심이야?";
			link.l1 = "지금은 그 어느 때보다 더 그래. 그 사람이 흑인이든 백인이든 지금 내게는 전혀 중요하지 않아. 오렐리를 도와줄 수 있는 다른 사람이 누가 있을지 나도 모르겠고, 너도 모를 거야. 그러니 비켜, 그리고 내 길을 막을 생각은 꿈도 꾸지 마.";
			link.l1.go = "Jillian_16";
			link.l2 = "그래, 맞아. 약도 소용없었어. 줄리안 형제의 기도도 마찬가지였고. 치미셋만이 우리의 마지막 희망이야.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "내 귀를 의심하게 되는군! 하지만 그는... 신도 없는 자잖아!";
			link.l1 = "그리고 그녀는 이제 곧 자신의 이름조차 잊어버릴 위태로운 여인이야. 알겠지, 그는 마법사지만, 내가 듣기로 그들은 정말 많은 걸 할 수 있대. 믿기 힘든 일들도 말이야. 만약 그가 그녀의 정신을 되돌릴 수 있다면, 그가 어떤 신을 섬기든 그게 정말 중요하겠어?\n";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "내 귀를 의심하겠네! 하지만 그는... 신도 없는 자잖아!";
			link.l1 = " 그리고 그녀는 이제 죽어가는 여자야 – 자기 이름조차 잊기 직전이지. 응, 그는 마법사지만, 내가 듣기로 그들은 별의별 걸 다 할 수 있대. 믿기 힘든 일들도 말이야. 만약 그가 그녀의 정신을 되돌릴 수 있다면, 그가 어떤 신을 섬기든 그게 정말 중요해?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", 들어봐, 나도 오렐리를 신경 쓰고 있어... 신께 맹세하는데, 그녀의 고통을 덜어주려고 내가 할 수 있는 건 다 하고 있어! 하지만 정말로 그 흑인 이단자가 이 선실에서 의식을 치르게 둘 거야? 만약 그가 배에 불을 지르거나, 의식 중에 누군가를 제물로 삼기로 마음먹으면 어쩔 건데?";
			link.l1 = "우리가 그렇게 두지 않을 거야, "+npchar.name+", 내가 장담해.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "그리고 분명히 말해두겠는데, 이 일에 대해 누군가 알게 되면... 여기서 무슨 일이 벌어질지 알아? 다른 마을 사람들은 물론이고, 특히 나왈스 녀석들이 가만있지 않을 거야!";
			link.l1 = "그 말이 맞아. 치미세트를 여기로 데려오면 안 되고, 오렐리를 그에게 데려가야 해.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "너 그녀 못 봤지 – 그 노파는 간신히 서 있을 정도야. 바다에 안 떨어지면 그게 기적일걸!";
			link.l1 = "음, 가끔은 기적을 바라는 수밖에 없지. 그리고, 질리언...\n";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "또 뭐?";
			link.l1 = "이건 비밀로 해줬으면 해. 너 똑똑한 여자잖아, 모든 걸 제대로 판단했어... 정의의 섬에서 일어난 소동이 쉽게 유혈 사태로 번질 수도 있어, 우리 아무도 그런 건 원하지 않지, 그치?\n";
			link.l1.go = "Jillian_22";
			link.l2 = "아무한테도 한 마디도 하지 마. 알겠지? 우리는 너를 믿고 맡긴 거야 - 우리를 후회하게 만들지 마라. 너도 나만큼 잘 알잖아, 이 일이 새어나가면 정의의 섬에서 전에 없던 대학살이 벌어질 거라는 걸.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "알겠어. 그런데 아무도 네가 그녀를 '프로텍터'호로 끌고 가는 걸 못 보게 해야 해... 안 그러면 내가 곤란한 질문에 답해야 할지도 몰라.";
			link.l1 = "어색한 대답할 필요 없게 해줄게. 오늘 밤에 우리가 할 거야.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "알겠어. 하지만 아무도 네가 그녀를 '프로텍터'호로 끌고 가는 걸 못 보게 해. \n 안 그러면 내가 곤란한 질문에 답해야 하잖아.";
			link.l1 = "그렇게 두지 않을 거야. 밤에 하자.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "자정 지나서 오세요. 그녀가 여기 있을 거예요. 그리고 제발, 조심하세요.";
			link.l1 = "걱정할 필요 없어, "+npchar.name+", 약속할게, 우리가 꼭 그렇게 할 거야.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "자정 지나서 와. 그녀가 여기 있을 거야...";
				link.l1 = "알지.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "오렐리가 준비됐어. 데려가도 돼.";
				link.l1 = "알겠어. 그럼 가자.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "젊은이들아, 어디... 어디로 가는 거야?! 여긴 리바도스의 배잖아! 에릭은 어디 있지?!\n";
			link.l1 = "에릭이 에디 블랙이랑 친구가 됐어, 몰랐지?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "무슨 소리야, 이 녀석! 에릭은 흑인들을 아주 싫어해!";
			link.l1 = "이런, 이거 참! 알겠어, 그럼 가서 저 자식이 여기서 뭘 하고 있는지 물어보자!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "어머, 누가 우리를 보러 왔네! "+GetFullName(pchar)+" 실제로 만났네! 내 하얀 형제를 보게 되어 반가워, 하하! 그런데, 무슨 일로 여기 온 거야?";
			link.l1 = "그리고 너에게도 안녕, "+npchar.name+" . 그냥 럼주 한 잔 마시러 들를 수 있으면 좋겠는데, 미안하지만 급한 일이 있어서 왔어, 너랑... 아니, 정확히는 치미셋하고 말이야.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "우린 너에게 평생 빚을 졌어, 친구야. 우리가 할 수 있는 건 뭐든 다 도울게.";
			link.l1 = "그거 듣고 안심이야. 이제는 내가 의지할 사람이 아무도 없거든.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "이 여성들 중 누구를 도와줘야 하는 거야, "+pchar.name+"?";
			link.l1 = "너 진지한 건지 그냥 장난치는 건지 모르겠어, "+npchar.name+", 하지만 지금은 농담할 기분 아니야. 도움이 필요한 건 당연히 오렐리야.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "에릭! 에릭! 어디 숨었어, 이 게으름뱅이! 이게 다 뭐야?! 그 빼빼 마른 엉덩이 당장 이리로 굴러와!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "그럼 정말이네... 내 동네 사람들이 이 난파선이 좀 맛이 갔다고 했거든. 이제 보니 거짓말은 아니었네. 그래도 아직 네가 리바도스한테서 뭘 원하는지는 잘 모르겠어...";
			link.l1 = "치미셋하고 얘기하게 해 줘, 그러면 다 알게 될 거야...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "말해 봐, 내 소중한 친구. 네 얘기를 잘 들어줄 준비가 되어 있어.";
			link.l1 = "간단히 말할게, 치미셋. 오렐리에게는 메리와 내가 필요한 정보가 있어. 하지만 그녀의 상태 때문에, 내가 제대로 이해한 게 맞다면 단순히 나이 때문인 것 같은데, 우리는... 그 지식을 그녀에게서 얻을 수 없고, 설령 얻는다 해도 정확하다고 확신할 수 없어. 인디언과 아프리카 주술사들이 해낼 수 있는 기적들에 대해 들은 적이 있어 – 그래서 네 도움을 청하러 온 거야, 치미셋.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "알겠어, 친구. 샤먼들은 신비롭고 불가사의한 힘을 가지고 있지, 그들 자신의 혈육은 물론이고 외부인들은 더더욱 이해하기 힘들 정도로 말이야. 어떤 사람들은 그걸 마법이라고 하고, 또 어떤 이들은 기적이라고 하지. 우리는 정말 많은 걸 할 수 있어 – 하지만 아무도 강물을 거꾸로 흐르게 만들 수는 없어... 그리고 그 누구도 강의 흐름을 멈출 수도 없지.";
			link.l1 = "무슨 말이야, 치미셋?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "나는 시간의 강에 대해 말하는 거야, 친구. 아니면 인생의 강이라고 해도 좋아—네가 편한 대로 불러. 있잖아, 네 말이 완전히 맞아—이 불쌍한 영혼의 병의 근원은 오직 그녀가 살아온 세월에 있을 뿐, 다른 이유는 없어.";
			link.l1 = "그 얘기 조금 들었어. 내가 아는 건, 그게 그렇게 드문 문제는 아니라는 거야.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "맞아. 그 나이 또래 사람들은 종종 꿈의 계곡, 때로는 악몽의 계곡으로 휩쓸려 가곤 해. 돌아오기도 하지만, 다시 떠나게 되지—자기 의지라기보다는 뭔가 알 수 없는 힘이 끌어당기니까. 시간이 지날수록 그 병은 점점 더 심해져—결국엔 자신이나 친구들조차 기억하지 못하게 돼.";
			link.l1 = "그래서, 너도 어쩔 수 없는 거야?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "병을 몰아내는 건... 아니야. 그건 내 능력을 넘어선 일이야. 하지만 내가 할 수 있는 다른 일이 있어...";
			link.l1 = "정확히 뭐?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "이 여자가 정신을 차리는 순간, 내가 미리 준비해둔 간단한 의식을 치를 거야.";
			link.l1 = "완전히 막지는 못하더라도, 적어도 병의 진행을 늦출 수는 있을까?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "정확히는 아니야. 그녀가 가능한 한 오랫동안 제정신을 유지하려면 가진 힘을 모두 쥐어짜야 할 거야.";
			link.l1 = "‘가능한 한 오래’가, 정확히 얼마나 오래라는 거야?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "그건 의식에 달린 게 아니라, 사람에 달린 거야. 어떤 사람은 일주일을 버티고, 어떤 사람은 한 달을 버티지... 거의 1년, 어쩌면 그보다 더 오래 정신과 기억을 지킨 남자 이야기도 들었어... 모두가 그가 완전히 나았다고 생각했을 때, 병이 다시 찾아왔고—그날 밤 바로 그를 데려갔지.";
			link.l1 = "우리가 필요한 걸 알아내는 데 한 시간이면 충분해. 의식을 언제 치를 수 있어, 치미셋?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "지금 당장 그 여자를 데려가서, 창고로 내려보내. 거기엔 이런 일에 쓰는 은신처가 마련되어 있거든... 그 다음은, 그녀가 언제 제정신을 차리느냐에 달렸지... 하지만 내 생각엔 아침이면 끝날 거야.";
			link.l1 = "그럼 난 방해하지 않을게. 그리고 네... 신이신 치미셋이 너를 도와주시길.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "지코모! 저 백인 여자를 창고로 데려가는 것 좀 도와줘.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "잘 됐어, 하얀 형제. 우리가 해냈지...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "오, "+GetFullName(pchar)+"! 너랑 메리가 다시 정의의 섬에 돌아온 줄은 전혀 몰랐어! 정말 멋진 놀라움이네!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, 고마워! 어떻게 고마움을 전해야 할지 모르겠어...";
			link.l1.go = "Chimset_14";
			link.l2 = "와, 이것 좀 봐, 치미셋이 해냈네! 난 단 한 순간도 너를 의심한 적 없었어...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "리바도스 모두가 영원히 당신에게 빚을 졌어, 친구! '프로텍터'의 문은 언제나 당신에게 열려 있어.";
			link.l1 = "더 이상 폐를 끼치지 않길 바라요... 메리, 오렐리, 우리 '플루토'로 돌아가야 해.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "리바도스 모두가 영원히 너에게 빚졌어, 친구! '프로텍터'의 문은 언제나 네게 열려 있어.";
			link.l1 = "더 이상 폐를 끼치지 않길 바라... 메리, 오렐리, 우리 '플루토'로 돌아가야 해.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "내가 어떻게 내 선실을 나왔는지도 기억이 안 나... 에휴, 이 늙은이라서 그런가 봐 – 기억력이 완전히 엉망이야. ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "그래, 그래, 아가씨, 무슨 일로 내 선실에 온 거지?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "오렐리, 나...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "오렐리, 네가 없는 동안 여기를 좀 정리해 달라고 그녀에게 부탁했어. 무릎도 안 좋은데 굳이 허리까지 무리할 필요 없잖아...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "청소하라고?! 너...";
			link.l1 = "질리안, 수고했어. (속삭이며) 우리가 해냈어. 치미셋이 결국 해냈지.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "그럴 리가...";
			link.l1 = "보시다시피. 이제, 우리 얘기 좀 하자.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "그래, 젊은이들아, 늙은이를 바래다줘서 고맙구나. 곧 밖에 전혀 나가지도 못하게 될 것 같아. 이 가엾은 다리들, 내 다리들아...\n";
			link.l1 = "괜찮다면, "+npchar.name+", 우리 잠깐만 같이 있을게. 메리랑 나는 너랑 아주 중요한 일이 있거든.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "다시는 다른 배에 억지로 올라타지만 않는다면, 내가 할 수 있는 건 뭐든 도울게. 듣고 있어.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "오렐리, 내 부모님에 대해 말해 줬으면 해. 그리고 내가 태어난 날에 대해서도. 그게 여기, 이 섬에서 일어난 거 맞지? 도널드는 맞다고 하는데, 그때 도널드는 여기 있지도 않았으니까 확실히 알 수는 없잖아. 하지만 오렐리는 도널드보다 훨씬 더 오래 여기서 살았잖아, 알지! 스무 해도 넘게, 그렇지?\n";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "진정해, 진정해, 아가씨, 너무 빨리 말하지 마, 제발! 내가 따라갈 수가 없잖아...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "알겠어, 응. 좋아, 한 번만 더 정리해 보자...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "걱정 마, 메리. 나 아직 그렇게 늙진 않았어, 하하... 네가 한 말 들었어. 그래도 내가 정말 누구보다 정의의 섬에서 오래 살았으니, 내 나이에 조금은 존중과 이해를 보여줬으면 해...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "당연하지, 오렐리! 어떻게 그런 생각을 할 수 있겠어?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "아, 그냥 요즘 젊은이들을 보면 말이야... 아니, 아니, 우리는 어른들한테 그렇게 안 했지. 물론 너도 그런 건 아니고. 그냥 한꺼번에 묻지 말고 질문을 하나씩 대답하는 게 우리 둘 다 더 편할 거란 얘기였어...\n";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "알겠어, 오렐리. 네가 편한 대로 해, 알지? 그러니까, 내가 태어났을 때 너는 정의의 섬에 있었던 거야? 그러니까, 내가 정말 여기서 태어났다면 말이지...\n";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "나는 1633년에 정의의 섬에 왔어, 그리고 가끔 그날이 아직도 악몽처럼 날 따라다녀. 그 폭풍, 우리 '리프리절'—남편이랑 내가 플로리다로 가려고 타고 있던 플루트선—파도에 휘둘리면서 언제라도 뒤집힐 것 같았지. 우리가 아는 모든 기도를 외우고, 새로운 기도까지 만들어내고 있었어... 그리고, 쾅 하는 소리와 함께...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "그러니까 내가 태어나기도 다섯 해 전에 여기 오게 된 거네, 그치.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "대충 그렇지. 그땐 지금이랑 달랐어. 산 헤로니모도 아직 떠 있었고, 바깥쪽 배 고리는 지금의 절반, 아니 그보다도 더 작았지... 그리고 오래 못 버틴 배들은 빼고 말이야! 이건 꼭 말해주고 싶다, 젊은이들아 - 맑은 날 물 아래를 내려다보면, 그 밑에 난파선이 얼마나 많은지 보고 깜짝 놀랄 거야...\n";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "우리 부모님이 여기 도착할 때 타고 온 배에 관심이 있어. 나랑 같이... 아니면 나 없이?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "너랑 함께야, 아가씨, 너랑 함께지.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "그럼, 결국 나는 본토에서 태어난 거야?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "아니, 내가 말한 '너와 함께'는 조금 다른 의미였어. 네가 네 어머니 뱃속에 있었고, 일주일 뒤에 태어났지.";
			link.l1 = "이게 웃기니, 오렐리?";
			link.l1.go = "Oreli_32";
			link.l2 = "세월이 흘러도 유머 감각은 여전하네, 오렐리.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "글쎄, 나는 남들보다 나 자신을 훨씬 더 자주 비웃어. 미안해, 메리, 네 기분 상하게 하려던 건 아니었어.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "글쎄, 나는 남들보다 나 자신을 훨씬 더 자주 비웃어. 미안해, 메리. 네 기분 상하게 하려던 건 아니었어.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "괜찮아, 오렐리. 제발, 계속 말해 줘. 내가 태어난 후에 내 부모님께 무슨 일이 있었던 거야?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "그 다음엔? 아, 내 사랑, 두 사람 모두 그때까지 살아남았다는 사실 자체가 기적이나 다름없지! 그 해 6월 밤에 얼마나 끔찍한 폭풍이 몰아쳤는지 몰라! 아침이 되어 네 어머니를 태운 배가 안쪽 고리로 들어왔을 때, 처음엔 거의 아무도 자기 눈을 믿지 못했어—곧 아이를 낳을 여인이 그런 무시무시한 난파에서 살아남았다는 게 말이야. 불쌍한 테레사, 어제 일처럼 기억나는구나...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "테레사? 그게 그녀 이름이었어?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "그래, 그렇게 자기소개를 했지 – 그리고 그게 그녀가 한 말의 거의 전부였어. 그날이 끝날 무렵, 그녀는 열에 시달리기 시작했고 출산 때까지 계속 그랬어. 아무도 그녀가 살아남을 거라고 확신하지 못했고, 더군다나 아이가 무사히 태어날 거라고는 아무도 믿지 않았지 – 그녀가 겪은 모든 일을 생각하면 말이야. 하지만 테레사는 해냈어. 그녀는 해냈고… 그리고 세상을 떠났지. 신께서 그녀의 영혼을 편히 쉬게 하시길…";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "어머니가 돌아가시고, 나는 아버지와 남겨졌던 거야? 그런데 왜 모두가 내가 에릭 우데트에게서 자랐다고 말한 거지? 그리고...\n";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "메리, 자기야, 내가 부탁했잖아... 그렇게 질문을 많이 해서 나를 압도하지는 말아줘...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "미안, 오렐리, 내가 좀 흥분했네, 알지? 우리 아버지도, 그분도 난파선에서 살아남으셨잖아, 맞지?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "네 아버지 말인데... 알지, 네 아버지에 대해 내가 할 말은 별로 없어—그런 아버지는 누구에게도 있으면 안 된다고 생각해. 네가 태어난 지 며칠 안 돼서 그는 사라졌고, 널 혼자 남겨뒀지. 에릭이 정말 친절하고 다정한 마음씨를 가진 사람이어서 다행이었어—럼주에 적신 비스킷처럼 말랑말랑한 심장이었거든...\n";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "적어도 그의 이름은 말해 줘!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "아... 제프리였던가, 존이었던가, 기억만 할 수 있다면 좋을 텐데...";
			link.l1 = "그러니까, 너 정말 기억 안 나는 거지, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "내 말을 의심하는 거야, 젊은이?!";
			link.l1 = "조용히 해, "+npchar.name+", 진정해. 너를 기분 상하게 하려던 건 아니야. 그냥 네가 그 시절을 꽤 잘 기억하는 것 같아서, 그뿐이야.";
			link.l1.go = "Oreli_45";
			link.l2 = "의심은 없어, "+npchar.name+". 그냥 모든 세부사항을 제대로 기억하려고 하는 것뿐이야 - 그게 다야. \n하지만 이런 혼란 때문에 일이 좀 더 복잡해지긴 하네.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "기억이란 변덕스러운 아가씨야, "+pchar.name+", 꽤 까다롭지. 특히 이렇게 오랜 세월이 지난 뒤엔 더 그렇지. 테레사는 잊기 힘들어 – 일주일 내내 그녀가 고통받는 걸 지켜봤거든! 아, 정말 안쓰러웠어!";
			link.l1 = "그리고 그녀의 남편, 같이 있지 않았어?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "기억이란 변덕스러운 여인이지, "+pchar.name+", 꽤 까다롭지. 특히 이렇게 오랜 세월이 지난 뒤에는 더 그래. 테레사를 잊기 힘들어 – 내가 그 애가 일주일 내내 고통받는 걸 지켜봤거든! 아, 정말 안쓰러웠지!";
			link.l1 = "그리고 그녀의 남편, 같이 있지 않았어?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "아주 드물었어. 그는 주로 일주일 내내 집에 없었지 – 그때 정의의 섬에는 약과 묘약이 부족해서, 그것들을 찾아다녔거든...\n";
			link.l1 = "그러니까, 아내를 도우려고 했다면 좋은 남편이었겠네.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "그 사람, 좋은 남편이었을 수도 있지. 내가 아니라고 한 적은 없어, 알겠어? 나 헷갈리게 하지 마, 이 젊은이!";
			link.l1 = "나 그런 건 한 번도 생각해본 적 없어, 진짜야, "+npchar.name+". 네가 그를 별로 대단하게 여기지 않는 건 뻔히 보여. 그리고 그의 이름조차 기억하지 못한다는 사실도...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "나는 그 남자를 잠깐 봤어, 거의 그림자처럼, '케레스 대장간' 선실의 어둠 속에서—지금은 위르겐 씨가 사는 곳이지. 그는 밤에만 왔고, 나는 그의 얼굴도 거의 기억이 안 나. 이름 말인데—아무도 그의 이름을 이름으로 부르지 않았어, 항상 성으로만 불렀지. 카스퍼가 어쨌네, 카스퍼가 저쨌네...\n";
			link.l1 = "알겠어, "+npchar.name+". 그래서 메리가 태어났고, 며칠 뒤 그는 흔적도 없이 사라졌지. 죽임을 당한 걸까?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "그거 참 곤란한 질문이네, 젊은이. 여기서는 뭔가를 비밀로 하기가 꽤 어렵거든—다들 항상 지켜보고 있으니까. 또 싸움이 벌어지기만 하면, 그게 배 안에서 일어난 일이든 뭐든, 다음 날이면 정의의 섬 전체가 다 알게 돼.";
			link.l1 = "당연하지.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "죽은 자들의 시신이 항상 발견되는 건 아니야\n노련한 악당들은 손발을 체인샷으로 묶거나, 대포알이나 돌 같은 무거운 걸 달아서 시체를 가라앉히거든\n그리고 바닥에 사는 게들이 마무리를 하지\n하지만 죽은 자들의 소지품은 결국 다시 떠오르게 마련이야";
			link.l1 = "바닥부터라고?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "당연히 아니야! 내 말은 그냥 눈에 띄는 것들 있잖아—반지라든가, 각인된 권총, 의식용 검 같은 거... 그런 건 사람들이 거의 묻지도 않아. 사람을 되돌릴 수 있는 것도 아니고, 이미 겪은 일보다 더 큰 문제를 원하는 사람도 없으니까.";
			link.l1 = "제프리나 존 캐스퍼가 특별히 눈에 띄는 소지품이라도 있었어?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+" 네 영혼에 축복을, 이름조차 기억이 안 나는데 그런 걸 묻다니! 무슨 일이 있었다 해도, 그 물건이 정의의 섬에서 다른 사람 손에 들어갔다는 얘기는 한 번도 못 들었어. 그때 나는 선술집 시녀로 일하고 있었거든, 웬만한 소문은 다 내 귀에 들어왔지. 그렇다고 내가 모든 걸 다 알았던 건 아니야.";
			link.l1 = "사람들이 누군가 흔적도 없이 사라졌다고 말할 때는, 보통 죽임을 당했다는 뜻이야. \n하지만 캐스퍼 씨의 경우에는, 네가 그걸 확신하지 못하는 것 같네...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "나는 그냥, '사라졌다'고 해서 꼭 '죽었다'는 뜻은 아니라고 말하는 거야. 특히 그 시절에는 밀수꾼이랑 장물아비들로 가득 찬 타르탄선들이 정의의 섬이랑 쿠바 사이를 정기적으로 오갔으니까... 알지, 나는 그의 얼굴은 기억이 안 나는데, 눈만은... 어디서도 절대 길을 잃지 않을 사람의 눈빛이었어. 아니, 적어도 본인은 그렇게 굳게 믿고 있었지.";
			link.l1 = "타르탄선, 타르탄선... 그건 불가능한 일도 아니지. 이름만 알면 그 시절 식민지 기록을 확인할 수 있을 거야. 하지만 그가 탔던 배의 종류와 이름만 알면 훨씬 더 쉬울 텐데.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "왜 나를 그렇게 쳐다보는 거야, 젊은이? 내가 그걸 기억할 거라고 생각해?";
			link.l1 = "그러길 바라. "+npchar.name+" - 네가 이미 우리에게 얼마나 많은 걸 말했는지 생각하면 말이야.";
			link.l1.go = "Oreli_56";
			link.l2 = "흠... 그건 정말 의심스러운데.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "혹시 그녀가 대포를 몇 문이나 가지고 있었는지, 구경이 얼마였는지 묻고 싶은 거야? 내 사랑, 여기서 수년에 걸쳐 얼마나 많은 배들이 침몰했는지 알고나 있어? 그런데 내가 그걸 다 기억한다고 생각해? 게다가 그 배에서 살아남은 사람은 손에 꼽을 정도였어 – 그 배는 수면 위에 하루도 채 버티지 못했거든, 알지...";
			link.l1 = "알겠어... 뭐, 그럴 만하지, 벌써 이십 년이 지났으니까. 그래도 우리가 들었던 걸 기억해줘서 고마워.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "혹시 그녀가 대포를 몇 문이나 달았고, 구경이 얼마였는지 묻고 싶은 거야? 내 사랑, 여기서 수년에 걸쳐 얼마나 많은 배들이 침몰했는지 알기나 해? 그런데 내가 그걸 다 기억할 거라 생각해? 게다가 그 배에서 살아남은 사람은 손에 꼽을 정도였어 – 하루도 제대로 못 떠 있었거든, 알지?\n";
			link.l1 = "알겠어... 뭐, 그럴 만하지, 벌써 이십 년이 지났으니까. 그래도 우리가 들었던 걸 기억해줘서 고마워.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "네가 농담하는 거나, 기억이 구멍투성이인 늙은 여자를 놀리려는 게 아니길 바랄게.";
			link.l1 = "전혀 아니야, "+npchar.name+". 정말 많은 도움을 줬어. 얼른 나아. 음, 그럼 우리는 이만 갈게.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "그래서, 테레사... 그게 어머니 이름이었어. 불쌍한 우리 엄마, 알지...";
			link.l1 = "음, 적어도 이제 네가 그 힘과 고집을 어디서 물려받았는지 알겠네. 가라앉는 배 위의 임산부라니... 생각만 해도 소름이 돋아.";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "근데 대체 그녀가 왜 그런 상태로 이 배에 있었던 거야, "+pchar.name+"?! 그런 짓을 하려고 생각하다니, 미친 거 아니야?!";
			link.l1 = "그 질문에는 네 아버지만이 대답할 수 있어 – 존, 잭, 제이콥, 재스퍼, 조던...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "‘J’로 시작하는 영어 이름을 전부 기억하려고 하는 거야? 오렐리도 제프리랑 존만 말했잖아, 알지.";
			link.l1 = "혹시 나처럼 그녀도 나머지는 기억 못하는 걸까? 알잖아, 나이 먹으면 다 그렇지...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", 너는 그렇게 생각하는구나...";
			link.l1 = "지금은 그녀의 기억을 완전히 믿을 수는 없을 거야. 그래도, 우리는 식민지 기록뿐만 아니라 1638년 해군 기록도 뒤져야 해. 그건 훨씬 더 어렵지. 특히 장교 관련 기록은 기밀로 분류되어 있으니까. 그리고 평범한 선원이 자기 아내를 몰래 배에 태우는 걸 허락받았을 거라고는 전혀 생각하지 않아.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "반면에, 평범한 선원에 비해 장교에 대한 정보를 찾는 게 훨씬 쉬워.";
			link.l1 = "배 이름을 알고 있다면 말이지. 아니면 전체 이름이라도. 그냥 '제프리나 존, 아니면 최악의 경우 잭...' 같은 게 아니라 말이야...\n우리가 운이 좋아서 그 배가 해군 소속이었다면 말이지. 상인들은 선원 명부를 훨씬 더 엉망으로 관리하거든.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "그럼 우리는 어떻게 해야 하지, "+pchar.name+"? 오렐리한테 또 말 걸라고? 우리 이미 얻을 수 있는 건 다 얻었잖아, 그렇지 않아?";
			link.l1 = "오렐리랑이 아니야. 도널드랑이야.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "그런데 그 사람이 우리한테 어떻게 도움이 된다는 거야? 자기가 1638년에는 정의의 섬 근처에도 없었다고 했잖아, 알지.";
			link.l1 = "하지만 여기에도 다른 나르왈들이 있었지, 그렇지?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "네가 무슨 말을 하려는 건지 잘 모르겠어.";
			link.l1 = "알겠지, 자기야, 알겠지. 우리가 잡아당길 실이 하나 더 남았어. 가자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "오, 또 왔네! 그래서, 수색은 어떻게 되고 있어?";
			link.l1 = "안녕, "+npchar.name+". 상황이 더 나아질 수도 있겠지. 지금 우리는 마치 신비와 수수께끼로 가득한 동굴을 헤매는 것 같아. 그래도 출구가 가까이에 있다고 느껴.";
			link.l1.go = "Grinspy_32";
			link.l2 = "그리고 너에게도 안녕, "+npchar.name+"처음에 내가 상상했던 것보다 훨씬 나아. 상황이... 생각만큼 절망적이진 않네.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "그 말 들으니 기쁘네. 정말이야. 그런데 또 나한테 뭔가 필요한 거지, 둘 다? 뭘 알아냈어?";
			link.l1 = "메리는 여기, 정의의 섬에서 1638년 6월에 태어났어. 그녀의 어머니 테레사는 출산 직후에 세상을 떠났지. 아버지는 카스퍼라는 이름의 남자인데, 메리가 태어난 지 며칠 만에 흔적도 없이 사라졌어. 우리가 그에 대해 아는 건 이름이 'J'로 시작한다는 것뿐이야. 어떤 사람들은 그가 이 근처 얕은 바다에서 게밥이 되지 않고, 밀수꾼들의 타르탄을 타고 섬을 떠났다고도 해...\n";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "그 말 들으니 기쁘네. 진심이야. 근데 또 너희 둘 다 내게 뭔가 필요한 거지, 알지? 그래서, 뭘 알아냈어?";
			link.l1 = "메리는 여기, 정의의 섬에서 1638년 6월에 태어났어. 그녀의 어머니 테레사는 출산 직후에 세상을 떠났지. 아버지는 카스퍼라는 이름의 남자인데, 메리가 태어난 지 며칠 만에 흔적도 없이 사라졌어. 우리는 그에 대해 아는 게 거의 없어. 이름이 'J'로 시작한다는 것만 알지. 어떤 사람들은 그가 이 근처 얕은 바다에서 게밥이 된 게 아니라, 밀수꾼들의 타르탄을 타고 섬을 떠났다고도 해...\n";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "그리고 딸을 두고 떠났다고? 그거 참 이상한 짓이네.";
			link.l1 = "그래, 맞아. 하지만 이걸 설명할 수 있는 사람은 바로 이 J씨뿐이야.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "그리고 그 사람이 아직 살아 있다고 생각하는 거야? 그래서 그를 찾고 있는 거지?";
			link.l1 = "그것 때문만은 아니야. 우리는 그 사람이 누구였는지, 어떻게 살았는지 알고 싶어. 그건 메리에게 정말 중요한 일이거든.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "흠, 알겠어. 그리고 내가 정말로 너한테 도움이 될 수 없어서 미안해...";
			link.l1 = "사실, 할 수 있어. 말해 봐, 일각고래단이 정의의 섬에서 잃어버린 배들에 대한 기록 같은 거, 남겨두고 있지?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "무슨 뜻인지 잘 모르겠어, "+pchar.name+".";
			link.l1 = "그린스펜, 그린스펜... 내가 있어서 네가 아직 그 자리에 앉아 있는 거라는 거 잊지 마. 그러니까 부탁인데, 내 인내심 시험하지 마.";
			link.l1.go = "Grinspy_38";
			link.l2 = "분명히 이해하겠지, 도널드. 그리고 우리 우정을 생각해서라도, 질문을 피하려고는 하지 않을 거야.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "흠...";
			link.l1 = "배들이 가끔 바깥쪽 고리에 떠밀려 오지. 어떤 건 바로 가라앉고, 어떤 건 한동안 떠 있어—그럼 사람들이 와서 귀한 건 다 뒤지고 챙겨 가지. 리바도스에 대해서는 잘 모르겠지만, 나왈들이 배에서 찾은 자질구레한 것까지 전부 서로 싸우진 않을 거야—대부분은 아마 다 같이 모아 놓고, 전리품을 전부 집계한 다음에야 나눠 갖는 걸 거야.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "흠...";
			link.l1 = "가끔씩 배들이 바깥 고리에 떠밀려 오지. 어떤 건 바로 가라앉고, 어떤 건 한동안 떠 있기도 해—그럼 사람들이 와서 뒤지고, 값나가는 건 전부 털어가. 리바도스에 대해서는 잘 모르겠지만, 나왈들이 배에서 찾은 잡동사니 하나하나 가지고 싸우지는 않을 거야—대부분은 다 같이 모아두고, 나중에 전부 목록을 만든 다음에야 전리품을 나누겠지.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "너 바보 아니잖아, +pchar.name+. 여기 있는 많은 사람들과는 다르게 말이야. 응, 대충 그런 식으로 돌아가. 솔직히 나는 그 서류 작업이 지겨워, 하지만 알란 밀로우 때부터, 그리고 그 전에 나르왈 클랜을 이끌던 이들 때부터 쭉 그래왔어. 우리는 그런 기록을 남겨. 그리고 그뿐만 아니라, 리바도스나 해적들이 먼저 도착한 배들도 다 적어두지. 물론 그런 경우엔, 누가 타고 있었는지, 뭘 실었는지는 알 수 없어...\n";
			link.l1 = "메리의 부모님이 난파 후에 세레스 대장간으로 옮겨졌다는 사실로 보아, 그들의 배를 발견한 건 바로 나왈스였던 거야. \n즉, 그 기록이 어딘가에 남아 있어야 한다는 뜻이지.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "그럴지도 몰라. 확실히 말할 수는 없어. 그리고 앞으로도 못할 거야.";
			link.l1 = "이제는 네가 무슨 말을 하는지 모르겠어, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "난파선 기록 말이야. 도드슨이 떠난 뒤 레이튼 덱스터가 제독이 되면서 그 문서들을 우리에게서 가져갔지.";
			link.l1 = "그냥 그렇게 가져갔다고? 너는 아무 말도 안 했어?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "음, 일단 첫째로, 그는 꽤 예의 바르더라고. 둘째, 곧 돌려주겠다고 약속했지. 그리고 셋째... 내가 그 서류 따위에 왜 신경 써야 하지?";
			link.l1 = "완전히 쓸모없는 기록은 아니잖아, 알지?";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "내가 말했잖아, 이건 그냥 전통일 뿐이야. 주로 우리 일족이 난파선 전리품 때문에 서로 목을 물어뜯지 않게 하려고 하는 거지. 배가 떠밀려 오면, 우리가 챙길 수 있는 건 다 벗겨내고, 목록을 만들고, 일부는 나눠 갖고, 나머지는 우리 창고에 숨겨둬 – 그게 전부야. 서랍을 왜 쓸데없이 복잡하게 해? 이제 거기 좀 더 공간이 생겼으니까 – 그 점은 제독한테 고맙다고 해야겠네, 알지?\n";
			link.l1 = "알겠어, 이해했어. 그럼 'San Augustin'으로 항로를 잡을게. 그래도 다시 너를 보러 들를 수도 있어, 알지?\n "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "아, "+pchar.name+"들어와, 들어와. 무슨 일로 온 거야, 친구? 아니면 그냥 인사하러 들른 거야?";
            link.l1 = "이번엔 일 때문이야. \n뭐, 사실은 개인적인 일이기도 해.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "그리고 네가 이렇게 흥분한 걸 보니, 분명 너한테 중요한 일이겠네.";
            link.l1 = "정말이야? 내 생각엔 그냥 피곤한 거 같은데. 지난 며칠 동안 네 영역을 꽤 많이 돌아다녀야 했거든. 관절이 슬슬 아프다고 투덜거리기 시작했어—그리고 난, 이런 건 너 같은 늙은이들만 겪는 줄 알았던 내가 바보였지.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "그냥 좀 숨이 찼을 뿐이야, 알지? 난 하루 종일 의자에만 앉아 있진 않아. 너랑은 다르게 말이야 – 네 다리는 완전히 포기한 것처럼 보이는데, 하하하!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "그리고 내가 왜 이 의자에 붙어 있는지 한 번이라도 생각해 본 적 있어, 알지? \n여기 정의의 섬에 있는 모든 보물을 다 쏟아부어도 건강은 살 수 없다는 걸 깨달으면, 세상이 완전히 달라 보이거든.";
            link.l1 = "재밌네 – 바로 그 얘기하려고 내가 여기 온 거거든.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "그리고 내가 왜 이 의자에 붙어 있는지 한 번이라도 궁금해 본 적 있어, 알지? \n건강은 돈으로 살 수 없다는 걸 깨달으면, 이 정의의 섬의 모든 보물을 다 준대도 말이야, 세상이 완전히 달라 보이거든.";
            link.l1 = "재밌네, 바로 그 얘기하러 내가 여기 온 거거든.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "내 건강에 대해서?";
            link.l1 = "아니, 정의의 섬의 보물에 대해서야. 좀 더 정확히 말하자면, 그들의 목록에 대해서지. 그리고 아주 정확히 말하자면, 그 목록이 적힌 장부에 대해서야.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "어... 좀 더 쉽게 말해줄래, "+pchar.name+"?";
            link.l1 = "얼마 전만 해도 너는 정의의 섬에 좌초된 배들의 기록을 나왈에서 가져갔잖아...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "그래서, 그 멍청이 그린스펜이 진짜로 너를 그놈들 뒤쫓게 보냈다고? 간도 크네.";
            link.l1 = "전혀 아니야, "+npchar.name+", 도널드는 이 일과 아무 상관 없어. 내가 이 문제로 도널드에게 갔더니, 너한테 가보라고 하더라고. 그런데 네 반응이, 솔직히 좀 웃겼어. 왜 너한테 그 나르왈 기록이 필요했는지 말해줄래?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "왜 안 되겠어? 알겠지만, 나는 배 자체에는 전혀 관심 없어. 그리고 선창에 쑤셔 넣은 귀중품들? 그것도 마찬가지야. 여기 있는 사람들만 욕심부리지 않으면 모두에게 충분하지. 적어도, 내 생각은 그래. 내가 진짜로 신경 쓰는 건 무기야: 머스킷, 세이버... 대포까지도. 알지, 그 똑똑한 놈들은 가끔 그런 것도 건져내더라. 멍청한 검둥이 놈들은 절대 못하지, 하지만 나왈들은...";
            link.l1 = "그래서 그린스펜 사람들이 새로운 분쟁에 얼마나 준비가 되어 있는지 직접 확인해 보기로 한 거야?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "그리고 나랑 내 녀석들이 두 눈 부릅뜨고 지켜보고 있다고 전해 줘. \n 꽤나 노골적인 신호긴 한데, 도널드가 그 훈련으로 벌인 작은 쇼를 생각하면, 내가 그의 돈을 노린다고 착각해도 전혀 이상하지 않지.";
            link.l1 = "그래, 네가 바랐던 대로 일이 잘 풀리고 있는 건 아닌 것 같네. \n그리고 리바도스는 어때? 블랙 에디가 또 문제를 일으키고 있지 않아?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "리바도스, 에디... 저 더러운 흑인 놈들 – 샤크가 저놈들을 그렇게 증오한 것도 당연하지.";
            link.l1 = "그래서 그 녀석이 정말 문제를 일으키고 있구나.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "그게 바로 문제야, 알지, 내가 거짓말하면 천벌을 받겠어! 그 검은 놈들이 조용해졌어, 자기들 배에 틀어박혔다고...";
            link.l1 = "그래서 도대체 뭐가 그렇게 신경 쓰이는 거야, 응? "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "이걸 너한테 어떻게 설명해야 할지, "+pchar.name+"... 있잖아, 이건 마치 드넓은 바다의 바람 같아. 때로는 부드럽고, 때로는 거세고, 또 때로는 진짜 폭풍이 되기도 하지. 그래도 어쨌든 바람은 배를 앞으로 나아가게 하고, 훌륭한 선장은 그 바람을 잘 다루는 법을 알지.";
            link.l1 = "사나운 폭풍보다는 언제나 부드러운 산들바람이 더 나은 법이지.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "알지. 하지만 가끔은 바람이 전혀 없는 때도 있어. 완전한 정적이지 – 그럴 땐 어느 선장도 어쩔 도리가 없어. 그냥 함교에 앉아서 바다만 바라보며, 도대체 다음엔 무슨 일이 벌어질지 궁금해하지. 에디랑 그 친구 치미셋도 마찬가지야 – 뭔가 꾸미고 있는 게 뼛속까지 느껴지거든, 그리고 그게 좋은 일일 리 없지, 천둥에 맹세코!";
            link.l1 = "어쩌면 네가 그냥 엉덩이 떼고 에드워드랑 직접 마주 앉아서 얘기 좀 해야 하지 않을까? 아니면, 차라리 셋이 다 같이 모이고, 도널드까지 데려와서 솔직하게 대화해 봐. 정의의 섬을 또다시 피바다로 만드는 것보단 그게 훨씬 낫지. 하지만, 알았어... 내가 여기 온 이유로 다시 돌아가자.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "너 혹시 일각고래 보물에 관심 있는 거지, 맞지? 거기서 뭘 찾으려고 하는 거야?";
            link.l1 = "여기서 잃어버린 배들의 목록에 관심이 있어. 특히 1638년도의 기록 말이야. 사실은, 우리는 메리의 부모님에 대한 정보를 찾으려고 해. 그녀의 어머니에 대해서는 어느 정도 파악이 됐지만, 아버지에 대해서는 그렇지 않아. 그에 대한 정보는 아주 모호해—이름조차 모르고, 우리가 가진 유일한 단서는 1638년 6월에 바깥 고리에서 난파된 배의 이름뿐이야...\n";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "귀족이군. 나도 한때 내 아버지가 누구인지로 괴로워했던 적이 있어. 하지만 미안, 내가 도와줄 수는 없어.";
            link.l1 = "그건 왜인데, 물어봐도 괜찮겠어?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "너한텐 비밀 없어, "+npchar.name+". 나 때문이 아니라, 도널드 때문이야. 걔는 1651년부터 시작하는 서류만 넘겨줬어. 내가 더 오래된 기록, 적어도 지난 10년치라도 있냐고 물어봤는데, 그게 앨런 밀로우한테서 물려받은 전부라고 하더라. 그렇게 말했어.";
            link.l1 = "그가 거짓말할 이유는 없었다고 생각해.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "나도 그래, 친구. 그는 아무런 질문도 없이 나한테 새 기록을 건네줬거든. 사실, 오히려 그 잡동사니를 치우게 돼서 좀 기뻐 보이기까지 했어... 누가 알겠어, 밀로우가 그냥 수십 년 된 서류들을 정리해버린 걸지도... 태워버렸거나, 아니면...\n";
            link.l1 = "아니, 그럴 리 없어.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "아니, 그럴 리 없어. Alan은 절대 그런 짓 안 해.";
            link.l1 = "왜 그렇게 확신하는 거야, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "나는 그 사람이 이런 서류 작업보다는 칼이나 손도끼를 더 좋아하는 줄 알았어. 글이나 읽을 줄 안다는 것도 놀라운데.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "그 사람은 정의의 섬에 관한 모든 기록을 아주 소중히 다뤘어. 그 기록들이 섬의 이야기 일부라고 생각했거든. 그리고 역사— 이곳만의 역사가 아니라— 그게 바로 앨런의 진짜 열정이었지, 알지? 손에 넣을 수 있는 모든 역사 문서랑 책을 다 파고들었어... 가끔은 그가 전사보다는 학자가 훨씬 더 잘 어울릴 거란 생각이 들었지— 한 번은 그 얘기를 직접 하기도 했어.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "그는 정의의 섬에 관한 모든 기록을 아주 소중하게 다뤘어. 그 기록들이 섬의 역사 일부라고 생각했거든. 그리고 역사란—이곳만의 역사가 아니라—알런의 진짜 열정이었지, 알지? 그가 손에 넣을 수 있는 모든 역사 문서와 책을 파고들었어... 가끔은 내가 생각했지, 얘가 싸움꾼보단 학자가 훨씬 더 잘 어울릴 것 같다고—한 번은 그한테 직접 그렇게 말한 적도 있었어.";
            link.l1 = "어쩌면 그는 정말로 검과 권총 대신 안경이랑 종이, 깃펜을 선택했어야 했을지도 몰라, 알지? 그랬다면 아직도 이 썩은 배 갑판을 서성이고 있었을지도 모르지. 그런데 밀로가 그렇게 기록 보관을 좋아했다면, 그 기록들은 다 어디에 둔 걸까? 실수로 한 장에 잉크를 쏟을 수도 있었겠지만, 그런 게 수십, 아니 수백 장은 있었잖아, 맞지?\n";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "나는 그가 자기 목숨보다도 그 서류들을 더 소중히 지켰다는 것만 알아.\n아마 누가 훔쳐갔거나, 아니면 그가 직접 누군가에게 줬을 수도 있지...";
            link.l1 = "도둑맞았다고? 누가 예전에 선수에서 용골까지 완전히 박살난 배들에 대한 정보를 필요로 하겠어? 그냥 넘겨줬다는 게 훨씬 그럴듯하지, 근데 누구에게, 그리고 무슨 이유로?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "다른 역사 덕후한테나 주겠지, 하하하! 나도 찰스 말에 동의해. 그 오래된 낙서들을 누가 또 원하겠어, 알지?";
            link.l1 = "누군가는 그게 필요했겠지. 나도 좀 생각해봐야겠어. 알겠지,\n "+npchar.name+", 더 이상 붙잡지 않을게. 또 만나자.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", 다시 만나서 반갑네. 메리는 잘 지내고 있나?";
			link.l1 = "우리도 너를 만나서 반가워,  "+npchar.name+". 하지만 우리 일이 어떻게 될지는 네게 달려 있어.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "대화를 시작하는 방식이 흥미롭네, 인정할 수밖에. 그리고 너희 얼굴 표정으로 보아 조금 불안해지는걸.";
			link.l1 = "놀랄 필요 없어, "+npchar.name+", 네 잘못 아니야. 그냥 이 삐걱거리는 난파선들 위를 쉬지도 않고 뛰어다녔더니 좀 숨이 찬 것뿐이야. 그리고 오늘은 공기도 무겁지, 그렇지 않아?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "우리가 너를 찾으려고 정의의 섬을 이리저리 뛰어다녔어, 그러니까 좀 도와줘. 휴, 이 더위 정말 장난 아니네...\n";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "에헴, 그래, 지금은 산들바람이라도 불어주면 정말 좋겠네. 하지만 너를 지치게 한 게 날씨만은 아닌 것 같은데. 그래서, 내가 뭘 도와줄까?";
			link.l1 = "있잖아, 메리랑 나는 20년 전에 무슨 일이 있었는지 밝히기 위해 조사를 시작했어.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "음, 알겠어, 지금은 산들바람이라도 불어주면 정말 좋겠네. 근데, 너를 지치게 한 게 날씨 때문만은 아닌 것 같은데? 그래서, 내가 뭘 도와주면 될까?";
			link.l1 = "있잖아, 메리랑 나는 20년 전에 무슨 일이 있었는지 밝히기 위해 조사를 시작했어.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "흥미롭게 들리네. 그래서, 그게 정확히 뭐에 관한 거야?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "내 부모님 말이야, Antonio. Charles랑 나는 그분들이 누구였는지 알아보려고 하고 있어. 그리고 그분들에게 무슨 일이 있었는지도 말이야. 어머니는 내가 태어날 때 돌아가셨다는 건 이미 알아냈어. 하지만 아버지에 관한 일은 그렇게 간단하지 않아...\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "몇 년도에 태어났더라, 다시 한 번 말해 줘...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "1638년 6월에.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "그때 나는 겨우 열두 살이었어, 메리. 그 시절은 사실 잘 기억나지 않아. 물론 지금도 가끔씩 기억이 스치긴 하지만, 솔직히 말해서 전부 이어 맞추기는 좀 힘들어. 미안하지만, 내가 너를 도울 수 있을 것 같지 않아...";
			link.l1 = "그런 것까지는 필요 없어요, 안토니오. 하지만 메리가 태어난 날에 대해 기억나는 게 있다면 정말 고마울 거예요.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "그럼 내가 어떻게 도와줄까, "+pchar.name+"?";
			link.l1 = "너 역사에 관심 있다고 했잖아. 세계사뿐만 아니라, 특히 정의의 섬의 역사에도 말이야.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "맞아. 내가 찾을 수 있는 책은 전부 읽었고, 손에 넣을 수 있는 모든 필사본도 공부했어...";
			link.l1 = "우리가 말하는 건 그 필사본들이야. 그리고 너 말고도, 정의의 섬에서 너만큼 역사에 열정적인 사람은 딱 한 명 더 있었지...\n";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "앨런 밀로. 알지, 우리 그 얘기 예전에 했었지, 그가 리바도스를 쓸어버릴 계획 세우느라 바쁘기 전이었어. 나중엔 해적들도 포함됐고. 그 사람 진짜 똑똑했어, 대단한 재주도 있었고.";
			link.l1 = "의심할 여지가 없어 – 그 녀석은 보통 애가 아니었지. 뭔가 우리에게 도움이 될 만한 걸 가지고 있었어. 그리고 그건 정의의 섬에선 너희 둘 말고는 아무 쓸모도 없어. 섬 근처에서 난파된 배들의 항해 일지, 거기서 건진 화물과 귀중품에 대한 기록, 어쩌면 승객들의 이름까지도 있을 거야...\n";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "맞아.";
			link.l1 = "그래서, 그놈들을 봤어?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "나는 그걸 직접 봤을 뿐만 아니라, 거기에 담긴 정보도 내 노트에 옮겨 적었어. 우리가 대화하던 중에 그가 우연히 이런 일지들이 있다는 걸 언급했고, 내가 공부해보고 싶다고 해서 그걸 빌려달라고 했지 – 나는 정의의 섬 연대기 같은 걸 만들어보려고 하거든. 그 기록들은 내게 큰 도움이 됐어.\n앨런은 내가 이곳의 역사를 쓰겠다는 내 생각에 무척 신나했지. 물론, 그가 모든 기록을 다 준 건 아니고, 1650년대 기록은 자기 혼자 간직했지만, 그때는 나머지만으로도 충분했어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = " 그 기록들... 1638년도 포함되어 있지, 맞지? 제발, 그렇다고 해 줘!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "나는 그런 항해일지를 한 무더기나 가지고 있어 – 1620년까지 거슬러 올라가는 것들이지. 알란 말로는 그때부터 이런 기록을 남기기 시작했다더라고. 그리고, 맞아, 1638년도 있어, 메리.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "우리에게 그것들을 좀 보여줄래?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "선택권이 없는 것 같네, 하하하! 잠깐만. 다 여기 있어, 이 찬장 맨 아래 서랍에.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = " 편하게들 앉아서, 마음껏 조사해 보세요...";
			link.l1 = "바로 그거 할 거야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "여기, "+pchar.name+", 봐! 조슈아랑 테레사 캐스퍼야! 믿기지 않아 – 우리가 해냈어, 진짜 해냈다니까, 알지! 그리고 배 이름은 '랭글러'야! 이제 아버지에 대해 모든 걸 알아낼 수 있어 – 어떤 사람이었는지, 어떻게 여기까지 오게 됐는지...";
			link.l1 = "무서워, "+npchar.name+", 너무 서두르는 거야... 생각만큼 간단하지 않을 수도 있어. 국왕 폐하의 배... 왕립 해군 기록 보관소에서 정보를 얻으려면 누가 도와줄 수 있을지 생각해봐야 해...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "생각하자! 생각하면 답이 나올 거야,\n "+pchar.name+"! 제일 힘든 건 이미 지나갔어, 알지!";
			link.l1 = "아마 영 나리랑 프리딕 나리에게도 이야기해 보는 게 좋을지도 몰라, 알지?\n하지만 정의의 섬에 그런 이름을 가진 사람은 없었던 것 같은데.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "여기 없으니까, "+pchar.name+". 그 둘은 카스퍼 가족과 함께 구조된 바로 다음 날 밤에 죽었어.";
			link.l1 = "이상하네. 임신한 여자는 일주일이나 더 살았는데, 왕립 해군 소속 선원 두 명은 갑자기 죽었어...\n";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = " 내 기억이 맞다면, 애초에 그리 좋지 않았지. 이제야 생각나네,\n "+pchar.name+" – 나는 세레스 대장간 근처에 있었어, 그들이 배에 실려 왔을 때... 알지, 나는 오렐리 베르틴과 함께 에스메랄다에 있었던 것 같아. 그리고 검은 이방인들의 주술사, 치미세트도 무슨 이유인지 가게에 왔었지. 처음엔 그 두 선원이 이미 죽은 줄 알았는데, 하루가 지나서야 숨을 거두더라고...\n";
			link.l1 = "뭐, 어쩔 수 없지. 그래도 우리 이미 꽤 많은 걸 알게 됐잖아. 도와줘서 고마워, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = " 고마워할 필요 없어, "+pchar.name+". 이 모든 건 앨런 덕분이야\n— 그 기병대 녀석들 중에 저 기록의 진짜 가치를 알아본 자는 거의 없었거든. 하지만 이런 문서들 덕분에 역사가 되살아나는 거지!";
			link.l1 = "언젠가 메리랑 내가 네 연대기를 읽게 되길 바라, 친구야. 여기 네 일지야—잃어버리지 마. 자, 이제 우리 갈 시간이야. 언젠가 다시 만나자, 내 친구.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "여기 없으니까, "+pchar.name+". 그 둘은 카스퍼 가족과 함께 구조된 바로 다음 날 밤에 죽었어.";
			link.l1 = "이상하네. 임신한 여자는 또 한 주를 버텼는데, 왕립 해군 소속 선원 두 명은 갑자기 죽었어...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "다시 만나서 반가워, 친구야. 무슨 일로 여기 온 거야?";
			link.l1 = " 부탁이 있어, +npchar.name+... 아니, 사실은 질문이야.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "질문해. 아니면 부탁을 해도 돼. 내가 도울 수 있는 건 뭐든 다 해줄게.";
			link.l1 = "알겠어. 정의의 섬에서 얼마나 오래 살았어?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "수십 년, 수십 년이지, 친구. 나는 어릴 때 여기 오게 됐어. 하지만 이미 눈치는 빨랐지 – 노예선에 타고 있었거든. 내 이야기는 여기서 네가 들은 많은 이야기들과 크게 다르지 않아. 돌풍, 난파... 내가 갇혀 있던 영국 갤리온은 바깥 고리까지도 가지 못하고, 파도에 밀려 암초에 부딪혀 두 동강이 나버렸지.";
			link.l1 = "어떻게 살아남았어? 암초는 바깥 고리에서 꽤 멀리 있는데, 이런 폭풍우 속의 파도를 뚫고 여기까지 오는 건, 솔직히 말해서, 결코 쉬운 일이 아니거든...\n";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "그날 밤에는 신들이 내 편이었어. 나는 족쇄를 풀고 탈출하는 데 성공했고, 배였던 것의 조각을 붙잡았지. 내 곁에는 부족원 아사나가 있었어 – 우리 둘이서 파도와 맞서 싸우다가 지쳐서 결국 기절했지.";
			link.l1 = "배 중 한 척에 떠밀려 온 거야?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "그래, 우리는 선창에 있는 구멍 속으로 기어들어갔어... 거기서 또 정신을 잃었지, 너무 힘이 없었거든. 아사나가 비명을 지르기 시작할 때 정신이 들었어 – 그도 우리랑 같이 떠밀려온 배에 올라탄 거대한 게에게 산 채로 찢기고 있었지. 그리고 나는 그냥 멍하니 서서 지켜봤어, 내가 다음 차례라는 걸 알면서도 – 두려움과 무력감에 얼어붙어서, 한 치도 움직일 수가 없었어.";
			link.l1 = "네 친구를 도울 수도 있었잖아. 하지만 그랬다면 지금 이렇게 얘기하고 있진 않겠지, 맞지? 그래서 어떻게 도망친 거야?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "네부터 시작하지 않은 게 다행이야, "+npchar.name+". 그래서 어떻게 도망쳤어 – 다시 물에 뛰어들어서 헤엄쳐 나간 거야?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "아사나의 비명은 최근 허리케인 이후 배의 창고를 뒤지러 나온 몇몇 리바도스들에게 들렸어. 그들은 괴물을 포위해서 죽였지. 아사나를 위해 아무도 해줄 수 있는 게 없었지만, 나는 훨씬 운이 좋았어. 그렇게 해서 내가 여기 오게 된 거야. \n하지만 이제 네 차례야, 친구. 왜 이 모든 걸 알고 싶었던 거지?";
			link.l1 = "사실, "+npchar.name+", 어떻게 여기 오게 됐는지 묻고 싶었던 게 아니라, 언제 그런 일이 있었는지 물으려고 했어.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "아사나의 비명은 최근 허리케인 이후 선적 사냥을 나갔던 여러 리바도스들에게 들렸어. 그들이 짐승을 포위해서 죽였지. 아사나에게는 더 이상 해줄 수 있는 게 없었지만, 나는 훨씬 운이 좋았어. 그렇게 해서 내가 여기까지 오게 된 거야. 이제는 네 차례야, 친구 – 왜 이 모든 걸 알고 싶었던 거지?";
			link.l1 = "사실, "+npchar.name+", 나는 네가 어떻게 여기 오게 됐는지가 아니라, 언제 그런 일이 있었는지 묻고 싶었어.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "음, 너희 달력으로는 1623년 늦여름이었어 – 그 이상은 더 정확하게 말할 수 없어...";
			link.l1 = "그럴 필요 없어. 그러니까, 1638년이면 너는 이미 정의의 섬에 15년이나 있었던 거네.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "그래 보이네, 친구.";
			link.l1 = "그해 6월, 허리케인이 국왕 찰스 1세 폐하의 함대 소속 브리그선 '랭글러'호를 바깥 고리로 몰아넣었어.\n선원 중 살아남은 건 단 네 명뿐이었지 — 그중에는 메리의 부모인 조슈아와 테레사 캐스퍼도 있었어.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "알지, 그건 기억나. 친구야. 희미하게, 안개 속을 보는 것처럼, 그래도 기억은 나...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "정말 기억해? 그럼 말해 봐!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "많이 말할 수는 없어. 네 명이었지: 장교 한 명, 그의 아내, 그리고 선원 두 명. 그 여자는 임신 중이었고, 구조한 사람들은 그녀가 아침까지 못 버틸 거라 생각했어. 하지만 그녀는 암사자처럼 강했지. 반면 두 선원은 하루도 못 되어 세상을 떠났어... 내가 그들을 봤거든. 약해 보였지만, 그래도 아직 생명이 남아 있었어...\n";
			link.l1 = "그 사람들이 죽임을 당했다는 거야?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "그렇다면, 그 일에 대한 목격자도 없었고, 시신에도 상처 하나 없었다는 거잖아, 친구...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "장교라고 했지, 그치... 내 아버지가 정말 장교였어?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "그 사람은 장교 제복을 입고 있었어 – 내가 그의 모습을 떠올리려고 할 때 아마 그것만이 유일하게 기억나는 거야.";
			link.l1 = "그가 장교였다면, 다른 옷을 입었을 리가 없어 – 그의 옷장이 그렇게 다양했을 것 같지도 않고... 혹시 다른 특징이라도 기억나? "+npchar.name+"? 특별한 특징이라도 있나... 있잖아, 얼굴에 흉터가 있다든지, 아니면 다른 상처 같은 거...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "나는 별로 기억이 안 나, 친구. 그의 얼굴은 거의 내 기억에서 사라졌어 – 벌써 이십 년이나 지났으니까... 하지만 그의 시선만큼은 너무나도 또렷이 기억나. 나는 그 남자와 딱 한 번 이야기했지만, 그의 회색 눈빛 – 메리와 똑같았지 – 절대 잊을 수 없어. 그 눈에는 절망이 있었고, 궁지에 몰린 영양 같은 두려움이 있었어. 그리고 동시에, 사자에 어울릴 만한 분노와 결의도 있었지...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "너 그 사람이랑 얘기했지, 알지? 무슨 얘기였어?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "네가 태어나기 몇 시간 전에 일어난 일이야. 그가 여기, '프로텍터'에 와서 나를 만나게 해 달라고 요구했지. 리바도스의 우두머리 모게디는 그의 대담함에 깜짝 놀랐지만... 난 갑자기 그 남자에게 흥미가 생겼어. 그가 내 앞에 섰을 때, 무릎을 꿇고 자기 아내를 구해 달라고 애원했지... 누군가, 그들이 여기 머무는 짧은 시간 동안, 그에게 나에 대해 알려준 거야. 난 동의했어, 모게디가 반대했음에도 불구하고...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = " 그럼 내가 너한테 목숨을 빚진 거네?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "거짓말해 봤자 소용없어 – 우리는 네 어머니에게 겨우 도착했지만, 이미 너무 늦었어. 나르왈 선원들이 나를 ‘세레스 스미시’에 태우지 않으려 했거든. 네 아버지가... 그들을 설득하긴 했지만, 나는 불쌍한 테레사를 그녀가 마지막 숨을 내쉴 때에야 볼 수 있었어. 그녀는 너를 낳았고, 내가 좀 더 일찍 도착했다면 어쩌면 그녀를 구할 수 있었을지도 몰라, 하지만...\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "어머니가 돌아가셨어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "이런. 그녀는 너를 바라보며 마지막 숨을 내쉬었어. 하지만 그 전에, 마치 남은 힘을 짜내듯이 루퍼트라는 사람을 불렀지. 그녀는 그의 이름을 온 힘을 다해 외쳤어, 마치 도움을 청하듯이 말이야 – 그리고는 죽었어.";
			link.l1 = "루퍼트? 조슈아가 아니라?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "내가 이 얘기를 들려주면서, 친구야, 마치 그 순간을 다시 겪는 기분이었어. 그건 절대 잊지 못해 – 그녀의 마지막 비명도, 고통에 일그러진 얼굴도. 그리고 그래, 그녀가 마지막으로 남긴 말은 '루퍼트'였어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "우리 어머니, 예뻤어? 치미세트, 어떻게 생기셨는지 말해줄 수 있어?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = " 그럴 필요 없어, 메리. 그냥 거울을 봐봐—네가 어머니를 빼닮았잖아. 그 날카로운 눈빛만 네 아버지에게서 물려받았을 뿐이지.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "그 사람은 어땠냐고, 무슨 일이 있었던 거야? 내가 태어난 지 며칠 안 돼서 흔적도 없이 사라졌다는 것까진 알아냈어, 알지! 하지만 죽은 건 아니지, 그렇지?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "테레사가 죽어간다는 말을 듣자마자, 조슈아는 완전히 분노에 휩싸였어\n맹세컨대, 사바나의 사자들도 네 아버지가 그 날카로운 분노로 나를 플루트에 태우지 않으려던 그 나르왈들을 쫓아갔을 때만큼 사납게 먹잇감을 덮치진 않았을 거야...\n그를 제지하려면 남자 여섯 명이 달라붙어야 했지 – 그것도 그가 전사 둘을 갑옷째로 물에 내던진 뒤였어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "그래서 그 사람한테 뭘 했는데 - 말해 봐, 얼른!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "그를 '타르타로스'의 감방 중 하나에 가뒀어. 아무도 감히 그를 심판하려 들지 않았지—먼저 소문이 잠잠해지길 바랐거든... 거의 모두가 그를 안쓰럽게 여겼지만, 그런 남자와 함께 살고 싶어하는 사람은 드물었어. 며칠 뒤 조슈아는 사라졌고—비슷한 시기에 몇몇 밀수꾼 배들이 정의의 섬을 떠났지. 아무도 그 배들에서 그를 본 사람은 없었고, 그게 그의 죽음에 대한 소문이 시작된 계기였어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "그럼 그 사람이 살아 있다고 믿는 거야, 알지?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "내가 할 말은 다른 사람들도 분명히 너한테 할 거야 – 아무도 그의 시신을 찾지 못했어. 어쩌면 그는 정말로 어느 배 밑바닥에 숨어 있었을 수도 있고, 아니면 그 감방에서 목이 그어져 게밥이 됐을지도 모르지...\n";
			link.l1 = "그가 사라진 시점이 그 상인들이 출항한 때와 겹친다는 사실은 첫 번째 가능성에 더 무게를 두게 해. 그런 우연은 없으니까. 그리고 혹시 누군가에게 자기 계획을 흘린 건 아닐까? 만약 도망쳤다면, 정말 도망친 거지. 갓 태어난 딸을 여기 두고 말이야. 그 나름대로는 이해가 돼. 아기라면 허술한 배로 쿠바까지 가는 여정에서 살아남지 못했을 테니까... 하지만 분명히 딸을 데리러 다시 올 생각이었을 거야.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "나도 모르겠어, 친구. 그 시절에 조슈아 캐스퍼가 누구와 말을 나눴다면, 그건 감옥을 지키던 간수들뿐이었을 거야 – 하지만 그 자들은 모두 오래전에 이 죄 많은 세상을 떠났지. 아, 그리고 맞아, 언젠가 도밍고 신부가 그를 찾아온 적이 있어 – 줄리안 형제가 오기 전엔 백인들을 위한 신부였거든...\n";
			link.l1 = "고백이라도 하려고 했던 걸까? 도망치다가 죽을까 봐 겁났던 거겠지.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "내가 모르는 건 밝힐 수 없어, 친구야. 그리고 도밍고도 아무 말 안 해줄 거야 – 그 사람, 한 십오 년 전에 죽었거든, 알지. 누가 머리를 쳤는지, 아니면 그냥 술 퍼마시다 죽었는지... 술을 엄청 좋아했거든...";
			link.l1 = "하지만 어쩌면 도밍고가 일기를 썼을 수도 있고... 아니면 그 조슈아와의 대화에 대해 형제인 훌리안에게 말했을 수도 있지 않을까?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "그와 얘기해야 해, "+pchar.name+", 알겠지. 그리고 빨리 끝낼수록 좋아. 이 일 처리하기 전엔 배로 돌아가는 건 생각도 하기 싫어.";
			link.l1 = "남은 게 있다면 말이지. 줄리안도 모를 수도 있지만, 우리가 끝까지 밝혀낼 거야. 고마워, 치미셋.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "나는 언제나 네 곁에 있어, 친구야. 하지만 너희 둘에게 조언 하나 해줄게.";
			link.l1 = " 그게 뭐야?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "사냥 나갈 때는 덤불 속으로 너무 깊이 들어가지 마. 길을 영영 못 찾을 수도 있으니까.";
			link.l1 = "그걸 기억하겠다, 주술사. 이제… 작별이다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "하나님의 집 그늘 아래 온 것을 환영한다, 내 아이들아. 고해하러 왔느냐, 아니면 그저 기도하고 싶으냐?";
			link.l1 = "안녕하세요, 줄리안 형제님. 우리의 죄를 일일이 나열하려면 시간이 너무 오래 걸릴 것 같네요, 아쉽게도 지금은 그럴 여유가 없어요. 하지만 안심하세요, 우리는 좋은 가톨릭 신자로서 항구마다 꼭 교회에 갑니다.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "안녕하세요, 줄리안 형제님. 독실한 가톨릭 신자로서 우리는 하루를 주님께 기도하며 시작하고, 똑같이 기도로 마무리합니다.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = " 결혼도 안 하고 한 지붕 아래 함께 사는 선량한 가톨릭 신자들이라니... 그건 신성모독에 가까운 일이야, 아들아. 그리고 그건, 다시 말하지만, 대죄라는 걸 명심해라!";
			link.l1 = "그리고 성경에 사랑이 모든 죄를 덮는다고 하지 않나요?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = " 결혼도 안 하고 한 지붕 아래 함께 사는 선량한 가톨릭 신자들... 이건 신성모독에 가까운 일이야, 아들아. 그리고 그건, 다시 한 번 말하지만, 대죄란다!";
			link.l1 = "그리고 성경에도 사랑이 모든 죄를 덮는다고 하지 않나?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "사랑이란 그분의 계명을 따라 사는 거야 – 내가 다시 상기시켜야 하니, 아들아?";
			link.l1 = "다음에 하지. 우리는 다른 일로 온 거야.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "길 잃은 영혼들이 정의의 길로 돌아오는 데에는 결코 너무 늦은 때란 없지... 하지만 나는 너희 말을 듣고 있다, 내 아이들아.";
			link.l1 = "우리가 정말로 길을 좀 잃었어요, 줄리안 형제님. 과거라는 덤불 속에서 헤맸죠. 그리고 우리가 다시 빛으로 나아갈 수 있도록 형제님이 도와주시길 바라고 있어요.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "아주 재치 있구나, 아들아. 사람이 빛으로 이끄는 것이 아니라 주님께서 이끄신다는 것을 기억해야 한다. 그리고 그분을 따를 때, 그분의 길은 신비롭다는 것도 잊지 말거라.";
			link.l1 = "간단히 말할게, 줄리안 형제. 우리는 메리의 부모님에 대해 알 수 있는 모든 것을 알아내려고 하고 있어. 그녀의 어머니 테레사에 관해서는 대충 상황이 명확해—남편과 함께 정의의 섬에 도착했고, 일주일 뒤 출산 중에 세상을 떠났지. 하지만 그녀의 아버지는... 메리가 태어난 지 며칠 후에 사라졌어, '타르타로스'에서 도망쳤지. 소문에 따르면, 여기서 마지막으로 그와 대화한 사람은 도밍고 신부—네 선임이었대.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "그렇다면 너희는 이미 십오 년도 더 늦었구나, 내 아이들아.";
			link.l1 = "그래, 우리도 신부님이 꽤 오래 전에 돌아가셨다는 건 알고 있어. 그리고 그때는 줄리안 형제, 너는 아직 정의의 섬에 제대로 된 직책으로 올 만큼 나이가 안 됐었지, 맞지?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "그이가 죽고 몇 년 뒤에 결국 여기 오게 되었지. 이 배에서 모든 걸 정리하려면 정말 많은 노력이 필요했지만, 신의 도움으로 해냈어, 아들아.";
			link.l1 = "여기서 일들을 정리하는 동안, 혹시 도밍고 신부님의 기록을 본 적 있어?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "무엇을 구체적으로 말하는 거니, 아들아?";
			link.l1 = "우리는 일기나 어떤 종류의 항해일지를 찾고 있어... 기적을 바라는 건 무리겠지만, 신부님이 그 대화 내용을 메모 중 하나에 적어두었을 수도 있지. 우리는 메리의 아버지가 밀수업자들의 배 중 하나를 타고 정의의 섬을 떠났다고 믿어—아마 신부님에게 어디로 가는지, 언제 딸을 데리러 돌아올 건지 슬쩍 귀띔했을지도 몰라?\n";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "나는 일기 같은 건 한 번도 찾지 못했어, 그건 확실해. 하지만 온갖 기록들은 있었지... 교회 일에 관해서라면, 그는 꽤 꼼꼼했거든— 모든 주님의 종이 그런 꼼꼼함을 가진 건 아니야. 하지만 그의 서류에는 건조한 숫자랑 이름뿐이었어— 그 이상은 없었지.";
			link.l1 = "우리가 알아낸 바로는, 조슈아 캐스퍼—그게 그의 이름이었어—그의 아내가 죽은 뒤 분노에 휩싸여, 리바도스 마법사 치미세타가 메리의 어머니를 만나지 못하게 막은 나왈 일족 두 명을 죽였다고 해...\n";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "그들은 진정한 교회의 자식들처럼 행동했어! 이 악마의 하인을 위해 종교재판소의 지하 감옥이 기다리고 있지!";
			link.l1 = "신이시여, 그분이 자신의 이름으로 얼마나 많은 사람들이 고문당했는지 알게 된다면 경악하실 거야, 알지? 캐스퍼는 좀 더 운이 좋았지 – 그냥 '타르타로스'에 있는 감방에 던져졌을 뿐이야. 하지만 그는 결국 재판까지 가지도 못했어.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "그래, 그래, 틀림없어. 캐스퍼는 '타르타로스'의 감방 중 하나에 던져졌지만, 판결이 내려진 건 아니었어\n아내를 잃은 남편의 행동을 모두가 비난한 건 아니었으니까.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "그 다음엔 어떻게 됐어 – 그 이단자가 도망쳤어?";
			link.l1 = "일주일도 채 지나지 않아 조슈아가 사라졌어. 그리고 그 전날 밤, 도밍고 신부가 그를 찾아왔지. 그래서 문제는—왜일까? 카스퍼가 분명히 개신교도였다는 걸 생각하면, 가톨릭 신부에게 고해성사를 했을 리는 없잖아—그렇지 않아?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "그 다음엔 어떻게 됐어 – 그 이단자가 도망쳤어?";
			link.l1 = "일주일도 안 되어 조슈아가 사라졌어. 그리고 그 전날 밤, 도밍고 신부가 그를 만나러 왔지. 그래서 문제는 이거야 – 왜일까? 카스퍼가 분명히 개신교도였다는 점을 생각하면, 가톨릭 신부에게 고해성사를 했을 리는 없어 – 너는 어떻게 생각해?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "진정한 신앙으로 돌아서기에 늦은 때란 없지, 아들아. 하지만 네 말도 일리가 있다. 그가 고해성사를 필요로 하지 않았다면, 아마도 신부님과 그의 아내 장례 미사에 대해 이야기했을 수도 있겠지—물론 그녀가 가톨릭 신자였다면 말이다. 아니면 그의 딸의 세례, 혹은 더 정확히 말하면 세례 거부에 관한 이야기였을 수도 있겠구나. 개신교도들은 유아 세례를 하지 않으니, 세례는 스스로 의식적으로 결정해야 한다고 믿으니까.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "하지만 나는 세례를 받았어, 줄리안 형제. 에릭 우데트가 그 얘기를 해줬거든.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "그건 내 추측일 뿐이야, 내 아이야. 진실은 나도 알지 못한다네. 주님께서는 우리에게 진정으로 중요하고 꼭 필요한 것만을 보게 하시지.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "그게 바로 내 얘기야, 알지. 혹시 도밍고 신부님의 기록에서 아직 네가 못 본 게 남아 있을지도 몰라, 줄리안 형제? 어차피 넌 그냥 대충 넘겨봤잖아, 그렇지?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "나는 거기에 갈 일이 없었단다, 내 아이야. 네가 이 일을 오래도록, 그리고 정성을 다해 해왔다는 게 보이는구나 – 주님께서 너를 이 가시밭길로 인도하고 계시지. 네가 찾고 있는 것을 결국 찾게 된다면, 그것은 주님의 뜻이니, 내가 그 길을 막을 수는 없단다. 네가 태어난 해의 도밍고 기록을 줄 수 있겠구나; 어쩌면 그 안에서 도움이 될 만한 것을 찾을 수 있을지도 몰라.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "그렇게 해주신다면 정말 관대하신 겁니다, 줄리안 형제님. 1638년의 기록은 아직 가지고 계신가요?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "흠, 흠... (먼지를 털며) 이게 바로 그거네. 1638년 주후의 장부야.";
			link.l1 = "제가 하겠습니다, 줄리안 형제님...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "봐, "+pchar.name+": 8월 3일. 그날이 파비안이랑 내가 세례받은 날이야. 나는 6월 22일에 태어났어. 하지만 아버지에 대해서는 한마디도 없어, 알지.";
			link.l1 = "줄리안 형제가 말한 그대로야 – 숫자랑 이름뿐이네. 재미있는 건 도밍고 신부가 자기 임무에 너무 열성적이어서, 심지어 프로테스탄트들에게도 임종 성사를 집전했다는 거야\n에쿠스, 영, 프리딕스가 가톨릭 신자였을 것 같진 않은데.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "그들이 천국의 문턱에서 진정한 신앙으로 돌아섰을 수도 있지, 아들아.";
			link.l1 = "물론이지, 줄리안 형제—그 사람들이 뭘 하겠어? 특히 소렌이랑 로하스처럼 죽었다면 말이야—아마 그게 바로 치미셋의 길을 막았던 그 나왈들이겠지.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "파드레 도밍고가 중간 이름을 전부 다 써줬으면 더 좋았을 텐데, 알지. \n우리 엄마 이름이랑 내 이름 뒤에 붙은 ‘V.’랑 ‘J.’가 도대체 뭘 의미하는 거야?";
			link.l1 = "그리고 이 파비안이라는 사람은 누구야, 너랑 같은 날 세례받은 그 사람?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "세실 할라르의 아들이지. 아, 지금 막 생각났어! 그분이 날 키워줬거든, 딱히 다정하진 않았지만. 아마 내가 살아남고 파비앙은 그러지 못해서 그랬던 것 같아. 파비앙은 태어난 지 몇 달 만에 죽었거든, 알지.";
			link.l1 = "이 작은 책에서 쓸모 있는 건 거의 못 배웠으니, 그녀와 얘기해보는 게 어때—물론, 네 생일이랑 세례 날짜를 중요한 정보로 친다면 말이지.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "오렐리보다 그렇게 많이 어리지도 않아, "+pchar.name+". 우리가 할 수 있는 건 적어도 그녀가 정신을 차렸기를 바라는 것뿐이야. 그런데 너는 그녀에게 뭘 물어볼 생각이야?";
			link.l1 = "음, 그녀가 네 유모였으니, 도밍고 신부가 조슈아와 나눈 이야기에서 뭔가 들은 게 있을 수도 있지. 그가 그녀 말고 누구에게 얘기했겠어? 어쩌면 오렐리나 에릭도 알았을지 몰라. 하지만 첫 번째한테서 뽑아낼 건 다 뽑아냈고, 두 번째는 이제 아무에게도 말할 수 없을 거야.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "이 훌륭한 여인은 이 하나님의 집에 헌신하는 신자요. 미사를 한 번도 빠진 적이 없고 고해성사도 정기적으로 드리오. 진심으로 너희에게 도움이 될 수 있을 거라 믿는다, 내 아이들아.";
			link.l1 = "감사합니다, 신부님. 안녕히 계십시오.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" 그리고 메리 캐스퍼라니. 정말 반가운 놀라움이네!";
			link.l1 = "마찬가지야, "+npchar.name+". 사실, 우리가 너를 만나러 왔어. 너랑 얘기하고 싶은 게 있거든.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "오, 정말이야? 음, 내 관심은 전부 네게 있어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "이건 내 부모님에 관한 일이야, 세실. 우리 엄마에 대해서는 이미 알아낼 수 있는 건 다 알아냈지... 내가 태어나자마자 돌아가셨어. 하지만 우리 아빠는... 며칠 뒤에 흔적도 없이 사라지셨어. 우린 그분이 죽지 않았다고 생각하는 편이야, 알지.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = " 정말이지, 그 같은 남자를 저세상으로 보내려면 꽤나 큰 노력이 필요했겠지...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "그 사람 봤어?! 말도 해봤어?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "내 딸, 그가 맨손으로 나왈 두 놈을 쓰러뜨리는 걸 봤어, 거의...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "소레노와 로하스?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "그때는 손이 너무 바빠서 그 악당들 이름을 기억할 틈도 없었지 – 그래서 지금은 전혀 기억이 안 나.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "알겠어, 상관없어. 계속해, 세실.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "그리고 뭘 더 이어가겠어? 그 자가 둘을 바다에 던져버렸고, 그들은 돌처럼 가라앉았지. 그리고 나서 그 자를 묶어서 '타르타로스'로 끌고 갔어. 잘한 거야 – 그 살인자가 또 누구를 물에 빠뜨릴지 누가 알겠어...";
			link.l1 = "칼잡이라니? 좀 심한 거 아니에요, 할라드 부인? 지금 여기선, 막 아내를 잃은 한 남자, 한 장교에 대해 이야기하고 있잖아요...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "그 사람을 그리 높이 평가하지 않는 것 같네 – 모든 장교가 그런 식으로 이야기되는 건 아니거든.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "장교라, 그래, 그래. 그의 제복이 꽤 인상적이었지, 아직도 또렷이 기억나. 거의 새것이나 다름없었어. 하지만 나는 살아오면서 장교들을 많이 봤거든, 젊은이. 그리고 그들 모두가 저... 신사보다 훨씬 더 점잖게 행동했지.";
			link.l1 = "그 사람이 또 뭐 했어? 그 둘을 죽인 것 말고?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "장교라, 그래, 그래. 그 양반 제복이 정말 인상적이었지, 아직도 또렷이 기억나. 거의 새 옷이나 다름없었어, 재단사 손에서 막 나온 것처럼 말이야. 하지만 난 살면서 장교란 장교는 다 봤거든, 젊은이. 그리고 그들 모두 이... 신사보다 훨씬 더 점잖게 행동했지.";
			link.l1 = "그 사람이 또 뭐 했어? 그 둘을 죽인 것 말고?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "그는 자기 감방에서 신부를 만나게 해 달라고 요구했어 – 데 라 크루스 신부를...";
			link.l1 = "오, 이것 좀 봐! 바로 그 얘기를 하려고 했던 거야. 그 대화의 자세한 내용, 알고 있어?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "물론이지, 젊은이! 그 개자식 같은 프로테스탄트가 신부님께 자기 딸을 세례 주지 말라고 요구했어—딸의 어머니가 아일랜드 사람, 그러니까 가톨릭 신자인데도 말이야.";
			link.l1 = "영국 여자가 개신교도에 대해 그렇게 말하는 건 거의 처음 들어보는 것 같군... 에헴, 방해해서 미안하오, 부인. "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "나도 예전엔 신교도였어, 숨길 필요 없지. 하지만 줄리안 형제가 나를 올바른 길로 이끌어줬어.";
			link.l1 = "그렇군... 정말로 주님께 헌신한 종이시네요. 하지만 본론에서 벗어났군요. 그러니까, 캐스퍼는 자기 딸이 개신교 신앙으로 자라길 원했던 거죠.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "그게 바로 그가 우리 데 라 크루스 신부님께 한 말이야. 그리고 그가 그 아이 이름을 줄리아로 지으라고도 명령했지...";
			link.l1 = "그래서 'J.'가 그런 뜻이었구나. 메리 줄리아 캐스퍼... 그런데 왜 다들 그녀를 메리라고 불렀던 거지?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "그건 그녀의 어머니가 원했던 일이기 때문이야, 그래서 그렇지. 아이가 뱃속에서 꺼내졌을 때, 그녀는 이름을 속삭였어 – 메리라고. 내가 그 자리에 있던 건 아니지만, 오렐리 베르틴이 출산 현장에 있었지. 원한다면 그녀에게 물어봐도 돼...";
			link.l1 = "그래서 결국 어머니 뜻을 따른 거구나, 알지?\n";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = " 죽은 듯이 사라져버린 그 한심한 아버지가 있는데, 달리 될 수가 있겠어?";
			link.l1 = "글쎄... 데 라 크루스 신부의 재능을 생각하면, 그 아버지가 타르타로스에 남아 있었더라도 그의 의견이 중요했을 것 같진 않아. 도밍고가 너한테 말 안 했지—그는 카스퍼가 도망치고, 어쩌면 그 여자애를 데리러 돌아올 계획이 있다는 걸 몰랐던 거야?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "어쩌면 네 말이 맞을지도 몰라. 하지만 도밍고 신부님이 카스퍼 씨와 나눈 대화로 돌아가서 — 신부님이 조슈아가 탈출에 대해 이야기했다거나, 혹은 딸을 데리러 언제 돌아올지에 대해 언급한 게 있었는지 말해줬어?\n";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = " 그는 그런 말 한 적 없어. 그리고 생각해 봐,\n "+npchar.name+", 만약 네가 감옥에서 도망칠 계획이었다면, 지나가는 사람마다 그걸 떠벌리고 다녔겠어? 저 녀석은 절대 안 그랬을 거야, 그건 내가 장담해.";
			link.l1 = "그러니까, 이 실마리도 결국 아무 소득이 없었네. 뭐, 그래도 시간 내줘서 고마워요, 부인. "+npchar.lastname+". 또 보자.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = " 그는 그런 얘기는 전혀 하지 않았어. 그리고 잘 생각해 봐,\n "+npchar.name+", 만약 네가 감옥에서 탈출할 생각이었다면, 지나가는 사람마다 그걸 말하고 다녔겠어? 저 녀석은 절대 안 그랬을 거야, 그건 내가 확실히 말할 수 있어.";
			link.l1 = "그러니까, 이 단서는 결국 헛수고였네. 음, 시간 내줘서 고마워요, 부인. "+npchar.lastname+". 또 보자.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "꽤 흥미로운 것들을 많이 알아냈어, "+pchar.name+". 하지만 우리는 거의 진전이 없었어, 알지?";
			link.l1 = "우리 사이가 좀 복잡해지기도 했지. 그런데 네 어머니가 돌아가시기 전에 부르던 그 루퍼트라는 사람, 대체 누구일까?\n";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "형제일 수도 있고, 아니면... 가까운 친구일 수도 있지?";
			link.l1 = "친구라고, 그렇구나... 조슈아는 그 사람에 대해 알고 있었을까...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "무슨 말을 하려는 거야, "+pchar.name+"?";
			link.l1 = "이 모든 걸 제대로 생각해봐야 해. 다행히도, 우리가 수색을 도와줄 사람을 찾는 동안 충분한 시간이 있을 거야. 이미 많은 걸 해냈지. 하지만 아직 완전히 끝난 건 아니야. 우리 힘으로는 왕립 해군 사무실에 들어갈 수 없고, 게다가 그곳은 바다 건너 런던에 있잖아... 이 일을 도와줄 만한 사람, 혹시 생각나는 사람 있어?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "세르주 브누아는 어쩌고, 샤를?";
			link.l1 = "아빠트? 인맥이 많은 건 맞지만, 그래도 왕립 해군 기록 보관소에 들어갈 수 있을지는 의심스러워.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "그 사람이 직접 못 한다면, 우리를 할 수 있는 사람에게 연결해 줄지도 모르지, 알지.";
			link.l1 = "그런가 봐. 그러니까, 이제 생피에르로 가는 거지.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "이제 우린 기다리는 수밖에 없어, 알지.";
			link.l1 = "그 사람이 모든 걸 알아낼 거라고 확신해, "+npchar.name+". 시간은 금방 지나갈 거야, 너는 알아차리지도 못할걸. 그리고 지금은 – 우리가 할 일이 있지.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "무슨 특별한 걸 말하는 거야, 자기야?";
			link.l1 = "할 일은 많지만, 우리 그냥 배로 돌아가서 문 잠그고 둘이서 시간 좀 보내는 거 어때? 어때?\n";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "네가 그렇게 말할 줄 알았지, 알겠어! 내 생각은 이거야: 시간 낭비하지 말자!";
			link.l1 = "어서 와, 자기야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "오, "+pchar.name+", 너 정말 몰라, 진짜로 몰라, 내 영혼에서 얼마나 큰 짐이 막 벗겨졌는지, 알지!";
			link.l1 = "상상할 수 있어, 자기야 – 너 완전 빛나고 있잖아, 하하!\n보다시피, 이 모든 게 정말 가치 있었지.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "내 아버지는 유명한 장교였대, 상상이나 돼? 그런데 우리가 한 번도 만난 적이 없다니 정말 아쉬워. 그리고 그분이 본토에 도착했는지조차 우리는 끝내 알지 못했어, 알지...\n";
			link.l1 = "그랬다면, 그는 분명 다시 복무에 나섰을 거고, 누군가, 어딘가에서 그에 대한 소문을 들었겠지, 알지? 그런 사람은 절대 가만히 있지 못해 – 아니면, 네가 그걸 어디서 얻었겠어?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "정말 그 사람이 죽었다고 생각해? 쿠바에서 스페인 놈들 손에 넘어갔거나, 정의의 섬에서 죽임을 당했다는 거야?";
			link.l1 = "나는 현실적으로 보려고 해, "+npchar.name+". 그때만 해도 정의의 섬과 오가는 배가 좀 있었지. 밀수꾼들이 타르탄을 타고 정기적으로 드나들었거든. 그가 정말 떠날 수 있었다면, 분명 언젠가는 널 데리러 돌아왔을 거라고 나는 의심하지 않아.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "거기서 날 데려가려고 했던 거지. 하지만 그랬으면 우리 못 만났을 거야, 알지.";
			link.l1 = "그게 인생이야, 자기야. 뭐를 어디서 찾을지, 또 어디서 잃을지 아무도 모르는 거지. 지금 나랑 여기 있는 걸 후회하지 않았으면 해, 알지?";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "내 평생 이렇게 말도 안 되는 소리는 처음 들어봐, 알지! "+pchar.name+", 너 정말 최고야, 정말 멋져! 이렇게까지 애써서 나를 도와줘서 정말 고마워, 알지! 이게 나한테 얼마나 큰 의미인지 몰라. 그런데 서류들도 한번 보자—혹시 우리 친구가 말 안 한 뭔가가 있을지도 모르잖아...";
			link.l1 = "좋은 생각이야. 지금 바로 시작하자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "음, "+pchar.name+", 재미있는 거라도 봤어?";
			link.l1 = "알지, "+npchar.name+". 뭔가 있어...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "유령이라도 본 것 같은 얼굴이네, 알지?";
			link.l1 = "루퍼트 노스우드라는 사람에 대해 언급하고 있어.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "루퍼트 노스우드?! 진짜 그 사람이야?";
			link.l1 = "조용히 해, "+npchar.name+" - 그렇게 소리치지 마. 흠... 내 생각에도 그래, 맞아 – 그게 바로 치미세가 말하던 사람이야. 달리 될 수 없어 – 이런 우연은 없으니까.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "이 모든 일에 대해 어떻게 생각해, "+pchar.name+"?";
			link.l1 = "이 이야기는 점점 더 복잡해지고 있어. 그러니까... '콘월'호는 플리머스에서 출항했고, '콘월'호도 앤티가에 도착했지만, 정의의 섬 암초에서 난파한 건 '랭글러'호였지 – 그때 조슈아 캐스퍼가 여전히 선장이었고, 어떻게든 해군 본부 몰래 어떤 여자와 비밀리에 결혼까지 했더라고. 그 여자는 죽어가면서까지 루퍼트라는 사람을 애타게 불렀대.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "나는 이 모든 걸 전혀 이해하지 못하겠어. 누가 이 일에 대해 뭔가 밝혀줄 수 있을지조차 모르겠고. 내 아버지에 대해 알아내려고 하면 할수록, 우리는 점점 더 비밀과 미스터리의 늪에 빠져들고 있어, 알지.";
			link.l1 = "이 일에 대해 뭔가 아는 사람이 있다면, 조슈아 캐스퍼 아니면 루퍼트 노스우드일 거야.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "노스우드? 하지만 그는 죽었어, 알지. '콘월'이 세인트 존스에 도착했을 때 제출된 보고서가 조작됐다고 진짜로 생각하는 거야?";
			link.l1 = "아, 너 그 순진함 말이야, "+npchar.name+"... 점점 이 모든 이야기가 거짓으로 가득 차 있다는 생각이 들어. 생각해 봐: 조슈아 캐스퍼는 모범적인 장교였고, 상도 많았고 단 한 번도 징계를 받은 적이 없었어. 그런데 그게 정의의 섬에서 우리가 알게 된 그의 모습과는 전혀 맞지 않잖아. 거기서 그는 아무렇지도 않게 두 사람을 죽음으로 내몰았으니까, 그렇지 않아?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "그는 자신의 아내이자 내 어머니의 목숨을 위해 싸웠어, "+pchar.name+"!";
			link.l1 = "물론이지, 하지만 그렇다면 그녀는 도대체 어디서 온 거야? 그리고 더 중요한 건, 왜 그는 결혼 사실을 해군 본부에 숨겼을까? 평생을 군인으로 살아온 사람이잖아, 의무와 규정을 철저히 지키는 사람이 아니었다면 기록이 그렇게 깨끗할 리도 없고. 그런데 갑자기 이런 일을 저지르다니.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "그리고 이 모든 것 뒤에 아름답고 낭만적인 이야기가 숨어 있다면 어쩌겠어? 그런 일도 있긴 하거든, 알지?";
			link.l1 = "오해하지 마, 메리. 하지만 이건 전혀 사랑 이야기처럼 들리지 않아. 오히려 뭔가 연극 같은데, 아직도 이 모든 게 뭐 때문이었는지 모르겠어. 왜 프로비던스로 가는 길에 배 이름을 바꾼 거야? 그건 전함이잖아—그런 짓을 하면 재판정에 끌려갈 수도 있다고.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "알겠어 – 좋은 질문이야.";
			link.l1 = "그리고 이 루퍼트 노스우드, 뭔가 수상한 게 분명해. 그 전투에서 선원 절반 가까이가 죽었는데, 이상하게도 장교 중에선 그만 빼고 아무도 안 죽었거든. 그리고 왜 테레사가 임종 때 남편인 조슈아가 아니라 루퍼트를 불렀을까?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "그러니까, 네 말은 일등항해사가 스페인 놈들이랑 싸우다 죽은 게 아니라는 거지, 응? 그리고 나는 조슈아 캐스퍼의 딸이 아니라 루퍼트 노스우드의 딸이라는 거고, 그 말이 맞아?";
			link.l1 = "아까도 말했지만, 진실을 아는 사람은 단 한 명뿐이야. 어떤 이유에서인지 테레사를 자기 아내라고 불렀던 조슈아 캐스퍼, 아니면 마찬가지로 알 수 없는 이유로 선장의 이름을 받아들인 루퍼트 노스우드, 둘 중 하나지.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "이런 지독한 엉망진창이네, 알지! 그래서 이제 뭐 할까,\n "+pchar.name+"이제 진실을 더 알고 싶어졌는데, 이미 모두에게서 뽑아낼 수 있는 건 다 뽑아냈잖아, 알지?";
			link.l1 = "만약 답이 있다면, 정의의 섬에 있을 거야\n네 부모님을 잠깐이라도 알았던 사람은, 적어도 이 바다 쪽에는 이제 아무도 남지 않았으니까.\n오렐리 베르틴과 한 번 더 이야기해 보자고 생각해. 우리가 놓친 뭔가를 그녀가 기억해낼지도 몰라.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "하지만 그녀에게서 뭘 더 알아내고 싶은 거야? 그녀가 아는 건 이미 다 말한 것 같은데.";
			link.l1 = "우리가 물어본 것에 대해 그녀는 대답했지만, 중요한 걸 놓쳤을 수도 있어. 네 아버지 얼굴에 흉터가 있었다든가, 손가락이 하나 없었다든가 하는 걸 말이야... 배 이름을 바꾸고, 어쩌면 자기 이름까지 바꿀 생각을 해낸 사람이 그냥 어느 섬이나 카스티야 감옥에서 초라하게 죽었을 거라고는 생각하지 않아.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "어쩌면 네 말이 맞을지도...";
			link.l1 = "그리고 우리가 계속해서 찾아보기로 한다면, 해군 본부의 먼지 쌓인 선반이 아니라 바로 여기, 군도에서 말이야, 이름 하나만으론 부족해. 그것도 가짜 이름으론 더더욱 안 돼.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "있잖아, 이런 거 다 소름 돋는다니까, 알지? 아마 너무... 짜릿해서 그런 걸 수도 있고, 아니면 우리 아버지도 비숍 농장에 있던 그 망할 놈이랑 별로 다르지 않았을지도 모른다는 생각 때문일지도 모르겠어.";
			link.l1 = "어쨌든, 우리가 이 일의 진실을 꼭 밝혀낼 거라고 약속할게. \n그러니까 시간 낭비하지 말자. \n가자!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "가자, "+pchar.name+", 더 이상 시간 낭비하지 말자, 알겠지.";
			link.l1 = "오렐리가 자기 선실에 있으면 좋겠네, 정의의 섬 전체를 뒤지면서 그녀를 찾아다니지 않아도 될 테니까...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "또 운이 없는 것 같네, 그치? 이번엔 그녀가 어디로 간 걸까?";
			link.l1 = "또다시 병이 그녀의 정신을 잠식하지 않았으면 좋겠는데...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "오, 또 왔네. 음, 안녕... 왜, 또 오렐리가 필요해?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "눈치 하나는 빠르네, Jillian. 혹시 그녀가 어디 있는지 알고 있지?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "교회에서 그녀가 막 고해성사를 하려던 참이었어. 서두르면 거기서 그녀를 찾을 수 있을 거야.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "음, 자백을 한다면 분명히 제정신이고 기억도 또렷한 거지, 그치.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "뭐라 말하기 어렵군... 지난 사흘 동안 그녀는 평소와 달랐고, 진정하지도 못했어. 있잖아, 이상하게도 네 배의 돛대가 바깥 고리 너머로 보였을 때 엄청 불안해하더라고.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "무슨 이유로 그런 일이 생긴 걸까?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "글쎄, 네가 또다시 심문할 거란 생각에 그녀가 불안해하는 것도 무리는 아니지. \n하지만 남의 고민에 네가 신경 쓴 적이 있기나 했어?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "나한테 그렇게 말하지 마, 질리안. 이번엔 봐줄게, 하지만 또 그런 말 해봐...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "참 성질이 급한 여자야 – 뭐 하나 마음에 안 들면 늘 예민해지지, 그렇지?";
			link.l1 = "괜히 그녀를 건드리지 않는 게 좋아, "+npchar.name+". 걔가 그 칼을 그냥 장식으로만 차고 다니는 거 아니라는 거 알지.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "그리고 너는 그걸 그냥 두었겠지, "+pchar.name+"?";
			link.l1 = "넌 아직 전투 중인 메리를 본 적이 없지,\n "+npchar.name+". 아니었으면, 넌 아무런 환상도 없었겠지 - 아무것도, 아무도 그녀를 막을 수 없어. 또 보자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "나한테 뭐 물어보고 싶은 거 있지, 알지? "+pchar.name+", 알지...";
			link.l1 = "솔직히, 너희 둘 사이에 무슨 일이 있었는지는 별로 신경 안 써, 알겠지? 그래도 내 생각엔 특정한 누군가가 원인인 것 같아. 정말 그 얘기 하고 싶은 거야?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "너랑 질리안, 뭔가 일로 사이가 틀어진 거야? 아니면, 누군가 때문에 그런 거라고 해야 할까?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "음, 딱히 그렇진 않아, 아니야.";
			link.l1 = "알았어. 이제 오렐리를 찾으러 가자.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "그 작은 피라미는 앨런이 자기 대신 나를 선택한 걸 절대 용서하지 않을 거야. 뭐, 이제 앨런도 없으니 용서할 수도 있었겠지만... 솔직히 말해서,\n "+pchar.name+", 그 얘기는 하고 싶지 않아, 알지?";
			link.l1 = "네, 자기야. 그럼 오렐리를 찾으러 가자.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", 메리! 다시 정의의 섬에 돌아왔구나, 정말 기쁘다!";
			link.l1 = "건강해 보여서 기뻐, "+npchar.name+". 사실, 우리가 정의의 섬에 다시 온 건 그냥 너랑 다시 얘기하고 싶어서야. 근데 걱정하지 마, 오래 걸리진 않을 거야.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "오오, 젊은이들아, 너희는 정말 이 늙은이한테는 조금도 자비가 없구나. 그래도 네가 올 줄은 알았단다. 또 네 부모님 이야기지, 메리?\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "제발, 오렐리. 오랜 시간이 지나서 기억하기 힘든 거 알지만, 나를 위해 한 번만 더 노력해 줘, 알겠지.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "내가 기억하는 건 이미 다 말했어. 더 뭘 짜내고 싶은 건지 모르겠네.";
			link.l1 = "너한테 물어볼 게 몇 가지 있어, "+npchar.name+". 제발, 뭐든 기억나는 게 있다면—아무런 사소한 것이라도 좋아. 우리는 억지로 떠밀지 않을게...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "그리고 그게 바로 네가 지금 하고 있는 일 아니야?";
			link.l1 = "이미 우리를 위해 너무 많은 걸 해줬잖아, "+npchar.name+"... 우리는 그저 네 기억의 미로 어딘가에 우리에게 큰 도움이 될 만한 무언가가 있기를 바랄 뿐이야.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "우린 여기까지 정말 멀리 왔네, "+npchar.name+". 네가 상상도 못할 만큼 많은 노력과 시간이 들었어. 하지만 우리는 길을 잃었고, 이제 오직 너와 너의 기억만이 우리를 진실의 길로 다시 이끌 수 있어.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "추억이라... 남은 게 뭐가 있겠어, 정말로. 어떤 아침엔 내 이름조차 기억이 안 나는데, 너는 나한테 이십 년 전 일에 대해 자세히 말해 달라잖아. 그래도, 물어봐.";
			link.l1 = "우리는 메리의 아버지인 캐스퍼 씨에 대해 관심이 있어. 혹시 그의 외모에서 특별히 기억나는 점이 있어? 얼굴에 흉터가 있다든가, 심하게 절뚝거리며 걸었다든가...\n";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "기억이라... 남은 게 뭐가 있겠어, 정말로. 어떤 아침엔 변소가 어디 있는지도 기억 못 하겠는데, 너는 내게 이 난파선들에서 스무 해 전에 무슨 일이 있었는지 자세히 말해 달라니. 그래, 알았어, 물어봐.";
			link.l1 = "우리는 메리의 아버지인 캐스퍼 씨에 대해 관심이 있어. 혹시 그의 외모에서 특별히 기억나는 게 있어? 얼굴에 흉터가 있었다거나, 심하게 절뚝거리며 걸었다거나...\n";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "아... 이미 말했지만, 나는 그를 완전한 어둠 속에서, 'Ceres Smitty'의 선창에서만 봤어, 거기서 불쌍한 테레사를 위해 침대를 만들어줬거든. 그는 절대 절뚝거리지 않았어—오히려, 꽤나 날쌘 사람이었지.";
			link.l1 = "그의 나이는? 젊었어, 아니면 이미 나이가 좀 있었어?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "그 사람을 늙은이라고 부르진 않겠어, 알지... 하지만 난 사실 그에게 별로 신경 쓰지 않았어 – 테레사가 더 걱정됐거든. 그는 꽤 초췌해 보였어, 마치 유령 같았지. 하지만 기억해, 그 사람은 아내가 곧 아이를 낳을 상황에서 일주일 내내 거의 잠도 못 잤어... 정의의 섬을 이리저리 뛰어다니면서 한시도 쉬지 않았지.";
			link.l1 = "그래서, 그는 아내를 정말 많이 사랑했던 거네. 그리고 너도 그녀랑 시간을 많이 보냈지, 맞지? 그녀가 남편에 대해 이야기한 적 있어?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "테레사는 그에 대해 계속 물었어. 잠을 많이 자기도 했고, 가끔은 헛소리를 하기도 했지. 하지만 정신이 들 때마다 제일 먼저 하는 말이 그가 어디 있냐는 거였어. 불쌍한 애가 그를 그렇게, 그렇게 많이 기다렸지. 그런데 가장 중요한 순간에 – 그는 끝내 오지 않았어.";
			link.l1 = "알겠어. 분명히 두 사람은 서로 사랑했었네... 음, 고마워, 오렐리. 우리에게 큰 도움이 되었어.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "이게 다야? 우리 대화가 적어도 한두 시간은 이어질 줄 알았는데.";
			link.l1 = "우리가 오래 귀찮게 하지 않겠다고 약속했지. 몸조심해, "+npchar.name+". 행운을 빌어.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "잠깐만, 젊은이들! 너희에게 줄 게 하나 더 있어... 아니, 정확히는 너, 메리에게 말이야.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "자, 여기 있어, 내 딸. 받아... 네 배의 돛을 보자마자 이 모자를 챙겼지, 잊어버리지 않으려고 말이야. 하지만 부두까지 내려가는 건... 도저히 용기가 나지 않더구나.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "뭔데, 오렐리? 모자야?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "네 어머니의 모자야, 테레사의 거지. 난파선에서 살아남은 사람들이 ‘세레스 대장간’으로 옮겨졌을 때, 테레사가 그 모자를 가지고 있었어. 테레사가 세상을 떠났을 때, 나는 그녀 침대 옆 바닥에서 그 모자를 주웠지, 알지? 그리고는 그냥 잊고 있었어... 오늘 우리 대화 중에야 그게 생각났네.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "오렐리... 그걸 이 모든 세월 동안 간직하고 있었구나! 그리고... 그리고 버리지도, 팔지도 않았네... 고마워, 정말 고마워! 이게 나한테 얼마나 큰 의미인지 너는 모를 거야, 알지!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "미안해, 메리 — 진작에 너한테 줬어야 했는데... 요즘 내 기억력이 오래된 체처럼 구멍이 숭숭 뚫려서 말이야 — 그래서 그런 거야...\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "지금이 딱이야, 오렐리! 바로 입어볼게, 알지!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "자기야, 나 어때?..";
			link.l1 = "너 정말 예뻐. 그리고 그 모자도... 아직 유행이 안 지났으니까, 정말 잘 어울려.";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "정말이야? 네가 좋아한다니 정말 기뻐!";
			link.l1 = "달리 될 수 있겠어?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "다시 한 번 고마워, 오렐리 – 네 덕분에 오늘이 좀 더 밝아졌어!\n행운을 빌고, 푹 쉬어.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "정말 루퍼트였네. 루퍼트 노스우드, 맞지?";
			link.l1 = "당연하지, 알겠지? 자기야. 그는 자기 아내를, 아니면 사랑하는 여자를 구하려고 할 수 있는 건 다 했어... 뭐, 정확히는 나도 몰라. 사실 그게 그렇게 중요하진 않아. 중요한 건, 이제 우리가 누구를 찾아야 하는지 알았다는 거야.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "그런데 '콘월'호의 선장, 진짜 조슈아 캐스퍼에게는 무슨 일이 있었던 거야?";
			link.l1 = "좋은 질문이긴 한데, 지금 가장 중요한 건 아니야. 루퍼트가 테레사를 그렇게 사랑했다면 왜 너를 데리러 돌아오지 않았는지 – 그게 훨씬 더 흥미롭지. 그게 우리가 그를 만나면 제일 먼저 물어볼 거야. 그가 아직 살아 있고, 우리가 그를 찾을 수 있다면 말이지. 한 가지는 확실해 – 그는 함대로 돌아오지 않았어. 그렇게 위험을 감수할 이유가 없었으니까.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "그가 왜 조슈아 캐스퍼라는 이름을 쓰게 된 걸까? \n'콘월'호에서 무슨 일이 있었던 거지, 그 배가 '랭글러'호가 되기 전에? \n정말 내 아버지가 범죄자일 수도 있는 걸까, "+pchar.name+"?";
			link.l1 = "우리도 그 가능성을 배제할 수는 없을 것 같아, "+npchar.name+". 우리는 정말 어떤 상황이 와도 대비해야 해.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "그건 생각하고 싶지도 않아...";
			link.l1 = "일단은 다른 걸 생각해야 해 – 어디서 그를 찾아야 할지 말이야. 해적이나 밀수꾼 무리에 들어갔을 수도 있고, 아니면 어느 마을에 정착해서 조용히 지내고 있을지도 몰라. 뭐든 가능하지.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "그래서 우리가 뭘 해야 한다는 거야? 어떻게 그 사람을 찾으라는 건데? 모든 식민지에 들어가서 이름을 말하고, 누가 루퍼트 노스우드를 들어봤길 바라는 수밖에 없는 거야?";
			link.l1 = ""아니면 조슈아 캐스퍼일 수도 있지. 그는 아마도 이미 죽었을 옛 선장의 신분으로 계속 살아갈 수도 있었을 거야. 하지만 그건 위험이 따랐지, 누군가 실종된 브리그를 찾으려고 할 수도 있으니까. 특히 그 배에는 프로비던스 주둔군을 위한 은화 상자가 실려 있었으니 말이야."\n";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "네 말이 맞아, 알겠지.";
			link.l1 = "그런데도 아조레스 근처에서 실종된 것으로 알려진 루퍼트 노스우드는 아무에게도 별 관심거리가 되지 않을 거야. 그래도 여기에는 분명 곰곰이 생각해볼 만한 뭔가가 있어.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "이걸로 얼마나 더 시간을 보내야 하는 거야, "+pchar.name+"?! 그 사람 어디든, 어느 식민지에든 있을 수 있어, 알지!";
			link.l1 = "그가 살아남았다면 말이지, 알겠지? 하지만 나는 동의하지 않아. 그가 스페인어를 유창하게 했을 가능성은 낮으니, 쿠바나 히스파니올라는 제외야. 프랑스어를 좀 알았다면 토르투가나 소앤틸리스 제도 중 한 곳으로 갔을 수도 있지. 아니면 서인도 본토에서 영국인 동료들 밑에 들어갔을 수도 있고. 우리가 몇 달을 그를 쫓아다녀도, 결국 허탕칠 수도 있어.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "하지만 포기하고 싶지 않아, "+pchar.name+". 지금은 아니야, 우리 이미 이렇게 많이 알게 됐잖아, 알지!";
			link.l1 = "포기하자는 건 아니야, "+npchar.name+". 하지만 우리가 직접 그를 찾아야 할 필요는 없어. 적당한 인맥이 있는 사람에게 부탁하면 되지. 전에 한 번 통했잖아. 또 해보면 어때?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "우리가 다시 원장님께 도움을 청하자는 거야? 그분이 이 일에 더 이상 기대지 말라고 분명히 말씀하셨잖아, 알지.";
			link.l1 = "그건 좀 너무 대놓고 아버지한테 굴겠네, 맞아.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "그렇다면 우리가 누구에게 의지해야 하지? 이런 일을 할 돈과 인맥이 있는 사람이 누굴까?";
			link.l1 = "음, 수색 자금은 우리가 직접 마련해야겠네, 알지?\n연줄이라면... 파데이 모스코비트가 도와줄 수 있을 거야. 식민지마다 쓸 만한 사람들을 그가 알지도 모르지. 아니면 우리 대신 적임자를 소개해 줄 수도 있고.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "그럼, 우리 바스테르로 가는 거야?";
			link.l1 = "그래, 우리 친구를 한번 찾아가 보자. 내 생각엔, 이 일은 그에게 그렇게 어려운 일 같진 않은데?";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "내일 닻을 올리자, 어때? 오늘 남은 시간과 밤을 너랑 단둘이 'Ceres Smitty'에서 보내고 싶어, 알지?\n";
			link.l1 = "그런 제안을 거절할 사람은 없지, 자기야. 우리도 이제 좀 쉴 자격은 충분히 얻었잖아.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "뭐야, 벌써 정의의 섬을 떠난다고? 장례식에도 안 있고?";
			link.l1 = "장례식?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "아, 그럼 아직 못 들었구나. 그렇군... 오렐리 베르틴이 어젯밤에 세상을 떠났어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "뭐?! 그럴 리가 없어 – 어제만 해도 그녀와 얘기했는데, 아무 이상 없었잖아. 아니면 누가...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "아니야, 메리. 오렐리는 잠든 채로 세상을 떠났어. 오늘 그녀를 보러 갔거든, 줄리안 형제가 만든 관절 연고를 가져다주려고 말이야 – 그때 그녀를 발견했지. 침대에 누워 있었는데, 얼굴엔 이상한 미소가 떠 있었어. 하지만 이미 창백하고 차가웠지.\n지난주 내내 그 노파는 평소와 달랐어, 흑마법사가 쫓아낸 병이 다시 돌아온 건 아닐까 생각하기도 했지. 그래도 정신은 또렷했고, 헛소리를 하는 것 같진 않았어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "적어도 고통스럽진 않았어, 알지.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "그래서, 장례식에 남아 있을 거야? 내일, 가장 먼 암초에서 할 거야\n거긴 충분히 깊고, 게들도 그리 멀리까지는 안 오거든.";
			link.l1 = "우린 남을 거야, 질리안. 오렐리가 메리를 위해 해준 게 너무 많아서, 달리 할 수가 없어. 아무도 이의 없으면, 우리 배에서 장례 행렬을 치르자. 바다에 그녀를 정중히 묻을 거야.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "아무도 이의 제기 안 할 거야. 이게 더 편하고, 결국엔 난파선 잔해를 기어오르는 것보다 더 안전하니까.";
			link.l1 = "그럼 장례 준비를 맡으시오 – 메리가 도와줄 거야. 나는... 누군가와 얘기 좀 해야겠군.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "그리고 또 왔네, 내 소중한 친구! 이번엔 내가 뭘 도와줄까?";
			link.l1 = "안녕, "+npchar.name+". 어젯밤에 무슨 일이 있었는지 들었어?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "오렐리의 죽음 얘기하는 거야? 딱 보면 알겠네. 당연히 들었지. 그녀는 ‘플루토’에서 살았고, 거긴 사실상 리바도스 구역이잖아. 그리고 다른 배 사람들도 그 얘기만 하고 있어.";
			link.l1 = "우리는 그녀를 어제만 해도 봤어, 그리고 그녀는 건강했지—물론, 일주일 내내 뭔가를 걱정하고 있었던 것만 빼면 말이야. \n그리고 우리 배를 보자마자, 그녀는 더 불안해졌어.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "사람은 자신의 인생이라는 강이 메말라 가고 있다는 걸 느낄 수 있어. 어떤 사람은 그걸 주변 모두에게 드러내고, 어떤 사람은 속으로만 감추지만, 누구나 어떻게든 그걸 느끼게 마련이지—특히 자기 마음의 소리에 귀 기울일 줄 아는 사람이라면 더더욱 그래.";
			link.l1 = "내가 보기엔 그녀는 건강해 보였어, 마치 어린 암사슴 같았지, "+npchar.name+". 그리고 뭔가 여기서 영 맞지 않는 게 있어...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "그런데도, 그녀는 분명히 마지막 순간에 처한 건 아니었어, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "친구야, 마음과 몸은 완전히 다른 차원의 것이야. 마음이 몸을 지배하지만, 때로는 몸이 마음을 지배하려 들기도 하지. 둘은 밀접하게 연결되어 있지만, 결코 완전히 하나인 것은 아니야. 겉으로는 아무리 건강해 보여도, 그 영혼은 이미 죽음의 길을 걷고 있을 수도 있어.";
			link.l1 = "네, 너 정말 똑똑하구나, 내 친구야, 아주 똑똑해. 진실이 가까이 있다고 느끼면, 사자가 얼룩말을 쫓듯이 그걸 쫓아가겠지 – 그리고 잡을 때까지 절대 멈추지 않을 거야. 나는 그걸 처음 만났을 때 바로 알아봤어.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "내 친구야, 마음과 몸은 완전히 다른 차원의 것이야. 마음이 몸을 지배하지만, 때로는 몸이 마음을 지배하려 들기도 하지. 둘은 밀접하게 연결되어 있지만, 결코 완전히 하나는 아니야. 겉으론 아무리 건강해 보여도, 그 영혼은 이미 죽음의 길을 걷고 있을 수도 있어.";
			link.l1 = "있잖아, 오렐리가 우리를 기다리고 있었던 것 같다는 생각이 들었어, 마치 우리가 그녀에게 올 걸 알고 있었던 것처럼 말이야. 그 노파는 하루 일찍이나 늦게 죽을 수도 있었는데, 하필이면 메리 아버지에 대해 중요한 말을 해준 직후에 바로 세상을 떠났지."link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "자네 참 똑똑하군, 내 친구. 아주 영리해. 진실이 가까이 있다고 느끼면, 사자가 얼룩말을 쫓듯이 그걸 쫓아가겠지 – 그리고 잡을 때까지 절대 멈추지 않을 거야. 내가 그걸 처음 자네를 봤을 때 바로 알았지.";
			link.l1 = "나는... 잠깐만. 네가 '프로텍터'의 창고에서 했던 그 의식... 오렐리의 병을 늦춘 게 아니었지? 그럼, 대체 뭘 한 거야?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "돌로 강을 메울 수는 있지만, 그렇다고 흐름이 멈추지는 않아. 나는 네가 오렐리에게서 정말 중요한 무언가를 필요로 한다는 걸 알았고, 그걸 바로 얻지는 못하리란 것도 알고 있었지. 하지만 네 여정이 얼마나 오래 걸릴지는 알 수 없었어. 그래서 나는 그녀의 모든 생명력을 끌어모아 병을 막아내는 댐을 쌓았지. 그녀가 자신의 목적을 이루는 순간까지 말이야. 그리고 그 순간, 장벽은 무너졌어...";
			link.l1 = " 그럼, 오렐리... 그녀가 죽는 순간에는 우리가 생각했던 것처럼 아무것도 모르는 상태가 아니라, 전혀 그녀 자신이 아니었던 거야? ";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "그녀는 정신을 맑게 하고 기억을 또렷이 유지하기 위해 온 힘을 다 쏟았어. \n그러다 더 이상 그럴 필요가 없어졌을 때, 병이 거대한 파도처럼 그녀를 덮쳐 죽음의 계곡으로 데려갔지. \n그녀가 평온하게 세상을 떠났는지, 아니면 과거의 유령과 끔찍한 악몽에 시달리며 네 신에게 갔는지는… 나는 알지 못하니, 말할 수 없어.";
			link.l1 = "이렇게 될 줄 뻔히 알았잖아, 알지? 대체 왜 결과에 대해 미리 말 안 해준 거야?! 자, 말해봐!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "네가 뭘 하는지 정확히 알고 있었지, "+npchar.name+". 왜 이런 일이 벌어질 수 있다고 미리 말해주지 않았어?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "내가 너를 돕기로 결심한 건, 친구야, 네가 알아야 할 것을 알게 해주고, 그녀가 자신의 운명을 이루도록 하기 위해서였어. 만약 내가 그녀에게 어떤 일이 닥칠지 미리 말했다면, 너는 끝까지 해내지 못했을 수도 있지—그리고 오렐리는 자신의 비밀을 무덤까지 가져갔을 거야. 그게 무슨 소용이 있었겠어? 그녀는 아무 의미 없이 죽었을 거야. 사자에게 쓰러진 영양처럼, 먹히지도 않고 독수리에게 버려진 채 말이야.";
			link.l1 = "목적, 쓸모... 너, 정말 운명의 달인이구나, "+npchar.name+". 인간의 모습으로 나타난 신.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "내가 너를 돕기로 결심한 건, 친구야, 네가 알아야 할 것을 알게 해주고, 그녀가 자신의 운명을 이루게 하려는 거였어. 만약 내가 그녀에게 어떤 일이 기다리고 있는지 미리 말했다면, 너는 그 일을 끝까지 하지 않았을지도 몰라. 그러면 오렐리도 자신의 비밀을 무덤까지 가져갔겠지. 그게 무슨 소용이 있겠어? 그녀는 아무 이유 없이 죽었을 거야. 마치 사자에게 쓰러진 영양이 먹히지도 못하고, 그냥 버려져서 독수리 밥이 되는 것처럼 말이야.";
			link.l1 = "목적, 쓸모... 너 정말 운명을 쥐락펴락하는 달인이구나, "+npchar.name+". 인간의 모습으로 나타난 신이야.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "네 목소리에서 불만의 기운이 느껴지는군, 친구야. 하지만 아니야, 나는 전혀 신이라고 생각하지 않아—그리고 믿어줘, 신조차도 전능하지 않아. 네가 믿는 그 신도, 우리가 섬기는 신들도 마찬가지지. 신들은 인간에게 태어날 때 주어진 힘보다 더 큰 힘을 줄 수 없어. 우리 주술사들은 그저 그 힘이 어느 방향으로 흐를지 이끌어줄 뿐이야—그 이상은 아니지.";
			link.l1 = "그리고 너는 그녀를 죽음으로 이끄는 길로 몰아넣었지...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "나는 그저 오렐리에게 길을 제시했을 뿐이고, 그녀는 그 길을 따라가면서 메리를 도왔어 — 메리가 태어난 날부터 깊이 연결되어 있던 사람이니까. 결국 네 동료는 그녀 눈앞에서 이 세상에 태어났지. 제발, 내가 미쳤다는 듯이 바라보지 말아줘. 설마 내가 손짓 한 번에 시간의 강을 거슬러 오를 수 있는 자비로운 마법사라고 본 건 아니겠지?\n";
			link.l1 = "무슨 말을 해야 할지 모르겠어, "+npchar.name+". 어쩌면 정말 모든 게 헛된 건 아니었을지도 몰라. 하지만 이렇게 되어서는 안 됐지. 너는 나에게 말했어야 했고, 나는 내가 직접 선택했어야 했어. 그래도 이미 벌어진 일은 어쩔 수 없지. 그럼, 안녕, 내 친구.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "아, 내가 상상했던 마지막 만남은 이런 게 아니었는데, 친구야...";
			link.l1 = "뭐가 그녀가 마지막이라고 생각하게 만든 거야?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "어떤 강은 다른 강으로 흘러들어가 그 일부가 되고, 어떤 강은 말라버리고, 또 어떤 강은—우리 강처럼—거대한 폭포에서 끝을 맞이하지...";
			link.l1 = "또 수수께끼야, 치미셋? 오늘은 이쯤이면 충분한 것 같은데. 우리 또 만나게 될 거야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "여기서 널 찾을 줄 알았지, 알지? 치미셋에게서 뭘 원했던 거야, "+pchar.name+"? 그가 너한테 뭐라고 했어?";
			link.l1 = "내가 기대했던, 아니, 듣고 싶었던 말은 아니야. 하지만 어렴풋이 의심하고 있던 일이었지.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "나한테 말해줄 거지, 그렇지?";
			link.l1 = "아니, "+npchar.name+". 이번엔 아니야. 보호자의 선실에서 한 모든 말은 거기서 끝이야, 나랑 치미셋 사이에서만.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "오랜만에 네 목소리에서 그런 결의를 듣는구나,\n "+pchar.name+". 하지만 말이야, 우리 신경 써야 할 일이 더 있잖아. 장례식은 내일, 해질 무렵, 일곱 시에 열릴 거야.";
			link.l1 = "자, 내가 다 준비하는 거 도와줄게.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "올 사람은 다 온 것 같네, 그치?";
			link.l1 = "사람들이 더 많을 줄 알았어. 적어도 평화로운 이들 몇 명쯤은 있을 거라고 생각했지.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "음, 쿠라나나 리바도스는 아무도 초대하지 않았어. 아봇, 그 거만하고 역겨운 칠면조 녀석은 가톨릭 여자 묻는 것보다 더 중요한 일이 있다고 했고, 로더데일이랑 머스킷도 비슷하게 중얼거렸지. 카셀, 그 야만인은 그냥 안 온다고 했고. 하지만 나머지는 다 와 있어.";
			link.l1 = "어떤 일들은 영원히 내 이해를 벗어나겠지. 뭐, 그런 건 신께 맡기자. 그리고 저기 줄리안 형제가 오네... 이제 모든 게 시작이야.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "비록 우리의 마음이 슬픔으로 무겁지만, 떠나간 오렐리에게 주신 모든 축복에 대해 하나님께 감사드리며 선포합시다: 하나님 아버지, 감사드립니다\n"+"오렐리가 우리와 함께한 모든 세월과 날들을 위해\n"+"거룩한 세례의 큰 은총으로 오렐리가 주님의 딸이 되게 하셨으니\n"+"그녀에게 주신 선물과 지식에 대해\n"+"그녀가 가족과 타인을 위해 헌신한 공로로\n"+"우리의 실수에도 인내해 준 그녀에게\n"+"하느님께 기도합시다. 우리의 떠난 자매 오렐리를 주님의 영광으로 받아주시길, 그리고 함께 외칩시다: 주님, 저희의 기도를 들어주소서\n"+"오렐리의 선행이 풍성한 결실을 맺기를 바라오\n"+"그녀가 시작한 일이 계속 이어지길\n"+"그녀가 저지른 죄를 용서해 주십시오\n"+"그녀의 기억이 우리 마음속에 영원히 살아 있기를\n"+"고통받는 이들의 믿음과 희망이 굳건해지도록 하나님께 기도합시다. 그리고 그분께 간구합시다: 주님, 우리의 믿음을 더해 주소서\n"+"당신의 아들이 사람이 되심으로써\n"+"당신의 아들 예수 그리스도를 통해, 우리를 헤아릴 수 없이 사랑하신 분이시니\n"+"당신의 아드님께서 우리의 죄를 위해 죽음을 받아들이시고 우리의 구원을 위해 다시 살아나셨으니\n"+"당신의 아드님을 통해, 우리에게 하늘로 가는 길을 열어주셨나이다\n"+"우리보다 먼저 하늘의 처소로 떠난 모든 신실한 이들과 함께, 구세주께서 가르쳐주신 대로 기도합시다.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "전능하신 하느님, 부활하신 아드님을 믿는 믿음으로 드리는 우리의 기도를 들어주시고, 이미 떠난 당신의 종과 함께 우리도 부활의 은총을 받게 하시어 희망을 굳건히 하소서. 성령의 일치 안에서 당신과 함께 영원히 살아 다스리시는 당신의 아들, 우리 주 예수 그리스도를 통하여 비나이다. 아멘.";
			link.l1 = "전능하신 하느님 아버지, 십자가의 신비는 우리의 힘이며, 아드님의 부활은 우리의 희망의 기초입니다. 주님의 종이 죽음의 사슬에서 벗어나 구원받은 이들의 무리에 들 수 있도록 해주십시오. 우리 주 그리스도를 통하여 비나이다. 아멘.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", 빨리 선실로 가자, 알지. 나 금방이라도 울 것 같아... 이런 모습 아무도 안 봤으면 좋겠어.";
			link.l1 = "그럼, "+npchar.name+". 가자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "사람이 떠난 뒤에야 진짜 그 소중함을 알게 된다는 말, 들어본 적 있어, "+pchar.name+"?";
			link.l1 = "그래, 여러 번 그랬어. .";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "에릭이 그런 말을 자주 했지. 아마 자기 가족을 두고 한 말이었던 것 같아. 나는 그 가족에 대해 한 번도 물어본 적이 없어—언젠가는 물어볼 시간이 있을 거라고만 생각했거든. 그런데 에릭은 죽어버렸지, 알겠어. 이제 오렐리도 떠나버렸고—이제서야 내가 그녀에게 얼마나 적은 시간과 관심만을 쏟았는지 깨달았어. 그녀가 받을 만한 것보다 훨씬 적게 말이야.";
			link.l1 = "너는 아무 잘못도 없어. 주님께서 언제 우리 사랑하는 이들을 부르실지 우리는 결코 알 수 없어. 그리고 그들과 함께하는 시간은 언제나 부족하지. 절대로 충분하지 않아.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "그럴지도 몰라, 알겠지. 그리고 에릭은 자주 말했어 – 오렐리도 동의했지 – 어떤 곳이든, 가장 중요한 건 그곳의 사람들이라고. 집이나 나무, 길이 아니라, 바로 사람들이야. 지도를 보고 어떤 장소를 떠올릴 때, 제일 먼저 생각나는 건 그곳에 사는 사람들이거든. 아니면, 한때 살았던 사람들이지.";
			link.l1 = "나는 한 번도 진지하게 생각해 본 적 없어. 하지만 에릭이 맞았던 걸지도 몰라—결국 집이란 게 뭐가 중요하겠어, 문을 열고 들어가면 다시는 아버지나 오빠를 볼 수 없다면 말이야?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = " 나는 그렇게 생각하지 않아. 예를 들어, 파리를 떠올리면 거리의 풍경이나 냄새 같은 것들이 먼저 생각나. 내 기억에 남아 있는 사람은 손에 꼽을 정도고, 나머지는 몇 년밖에 지나지 않았는데도 거의 다 잊혀졌어. ";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "에릭이랑 오렐리가 정의의 섬에 대해 얘기했던 것 같아, 알지? 그리고 여기 오래, 아주 오래전에 살았던 사람들에 대해서도 말이야. 난 그땐 그냥 어린애라서 아무것도 이해 못 했는데, 지금은—모든 게 다 보여. 결국, 안토니오, 세실... 그리고 치미세 같은 몇몇 리바도들은 나보다 훨씬 오래 여기 있었지만—난 그 누구와도 가까웠던 적이 없어. 그리고 나머지, 에릭, 오렐리, 앨런, 그리고 수많은 다른 이들은—이제 다 죽었어.";
			link.l1 = "알겠어. 세상이... 조금 더 작아진 것 같지, 그렇지?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "에릭이랑 오렐리가 정의의 섬에 대해 얘기했었지, 알지? 그리고 여기 오래, 아주 오래전에 살았던 사람들에 대해서도 말이야. 나는 그때 그냥 어린애라서 아무것도 이해하지 못했는데, 이제는 모든 게 너무 선명하게 보여. 결국 안토니오, 세실... 그리고 리바도스 중에 치미셋 같은 몇몇은 나보다 훨씬 오래 여기 있었지만, 나는 그 누구와도 가까웠던 적이 없어. 나머지, 그러니까 에릭, 오렐리, 앨런, 그리고 다른 많은 사람들은... 이제 다 떠났어.";
			link.l1 = "알겠어. 세상이... 조금 더 좁아진 것 같네, 그치?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "오히려 텅 비었다고 해야겠지. 이 세상—바깥 고리 안쪽은 말이야. 이제 완전히 비었어, 알지? 그리고 곧—아예 사라질지도 몰라.";
			link.l1 = "무슨 소리야, 메리?";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "느끼지 않았어, "+pchar.name+"응? 방금 전에, 우리가 오렐리의 무덤 옆에 서 있었을 때 말이야.";
			link.l1 = "정확히 뭐가?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "어떻게 설명해야 할지 모르겠어. 폭풍이 오기 전에 공기에서 나는 냄새 알지? 기억나? 네가 여기 처음 왔을 때, 온통 긴장감이 감돌았잖아... 모두가 서로의 목을 물어뜯을 기세였고, 많은 사람들이 화약 냄새랑 피 냄새가 난다고 했지. 네가 채드를 죽인 후엔 모든 게 달라졌어—숨쉬기가 한결 편해진 느낌이었거든... 그런데 지금—그 느낌이 다시 돌아왔어.";
			link.l1 = "나도 비슷한 감정을 느꼈던 것 같아. 하지만 그냥 분위기 때문일지도 모르겠네? 장례식이잖아, 아무래도...\n";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "지쳤네, "+npchar.name+". 좀 쉬어, 그러면 좀 나아질 거야. 그리고 말이지, 장례식장에서 누가 다르게 느낄 수 있겠어?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "에리크랑 정의의 섬에서 온 많은 이들을 바다에 보내던 그때는 이렇지 않았어, 진짜야. 뭔가... 하나 되는 느낌이 있었거든. \n그런데 오늘은—다들 같은 기도를 올리면서도, 몇몇은 서로를 늑대처럼 노려보고 있었어.";
			link.l1 = "레이턴이랑 도널드 말하는 거야?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "에릭이랑 정의의 섬에서 온 많은 이들을 바다에 보내던 그때는 이렇지 않았어, 진짜야. 뭔가... 하나 된 느낌이 있었지. \n그런데 오늘은—다들 같은 기도를 외우면서도, 몇몇은 서로를 늑대처럼 노려보고 있었어.";
			link.l1 = "레이튼이랑 도널드 말하는 거야?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "너도 눈치챘구나, 그치.";
			link.l1 = "그린스펜이 훈련에 끼어들려고 할 때마다 덱스터가 신경을 곤두세우지, 알지? 그럴 만도 하지 않겠어?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "이렇게 끝나면 안 될 텐데, 알지?";
			link.l1 = "그렇다면 오늘은 오렐리 베르틴의 장례식일 뿐만 아니라, 이... 버려진 배들의 도시의 장례식이기도 했던 거네.\n";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "버려진 배들의 도시?";
			link.l1 = "미안해, 메리. 하지만 난 도저히 이곳을 정의의 섬이라고 부를 수가 없어.";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "이제 세상을 보고 얼마나 넓은지 알게 되니까, 이곳이 마치... 감옥처럼 느껴져, 알지? 내가 여기서 자랐다는 게 믿기 힘들어.";
			link.l1 = "이렇게 부서진 배들 사이에서 너처럼 거칠고 아름다운 장미가 피어날 수 있었다니, 정말 믿기지 않아.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "이곳과 작별하고 싶어, "+pchar.name+"... 이제 우리는 여기 다시는 안 올 것 같아, 알지. 나도 그러고 싶지 않아. 여기서 무슨 일이 일어날지 내 눈으로 보고 싶지 않거든.";
			link.l1 = "에디랑 도널드한테 내가 얘기해 볼게. 좀 진정시키는 데 도움이 될지도 몰라, 알지?";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "너는 이해하지 못해... 이건 피할 수 없는 일을 잠깐 미룰 뿐이야, 그러니 애쓸 필요 없어. 우리가 돌아올 날이 올 거야 – 그리고 여기\n이게 최선이야, "+pchar.name+", 알겠어... 이제 나를 붙잡아 두는 건 아무것도 없어.";
			link.l1 = "네, 자기야. 우리가 해야 할 일 다 끝내고 나면, 이곳을 완전히 떠나자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "루퍼트 캐스퍼? 조슈아 노스우드?";
			link.l1 = "가는 내내 그 생각만 했어, "+npchar.name+". 그리고 나는 네 아버지가 이미 썼던 이름과 성으로 숨어들지는 않았을 거라는 결론에 도달했어. 동시에, 진짜 이름이나 성을 포기할 용기는 없었을지도 몰라. 혹시라도 중요한 순간에 가짜 이름에 대답하지 못할까 봐, 그렇지?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "자기가 뭐라고 불러도 됐을 거야, 알지.";
			link.l1 = "물론 그럴 수도 있었지. 어쩌면 정말 그렇게 했을지도 몰라. 밀수꾼 타르탄을 타고 쿠바에 도착해서 살아남았다면 말이야. 거기까지 무사히 갔고, 정의의 섬의 게밥이 되지 않았다면 말이지. 이제 우리가 할 수 있는 건 기다리는 것뿐이야 – 적어도 지난번만큼 오래 걸리진 않을 거야. 한 달쯤은 충분히 버틸 수 있을 것 같아.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "내 아버지가 살아 계셔, "+pchar.name+". 난 항상 알고 있었지, 알겠어!";
			link.l1 = "나랑 똑같지, 자기야. 자, 이제 그 제롬을 만나러 갈 시간이야 – 빨리 갈수록 좋겠지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "드디어 도착했네, 그치. 그래서, 이제 뭐하지, "+pchar.name+"?";
			link.l1 = "제롬을 찾아야 해. 그 녀석은 선술집 방에서 빈둥거리거나 집을 빌려서 쉬고 있을 거야 – 돈은 충분히 있으니까, 확실해.";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "파데이가 그에게 얼마나 많은 돈을 줬는지 생각해 보면... 내 생각엔 분명히 두 번째 선택을 했을 거야.";
			link.l1 = "알겠어. '유리눈' 주인한테 그 사람에 대해 물어보거나, 아니면 마을 사람들한테 그냥 물어보면 되지. 가자, 시간 아까우니까.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "오, 오, 오... 여기 우리 사랑꾼들이 있네. 자, 얘들아, 얼른 끝내고 그 사람한테 보고하자.";
			link.l1 = "제롬 수베르니에? 대체 여기서 무슨 일이 벌어지고 있는 거야?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "아, 이 자식들, 크-크. 뭐, 괜찮아...";
				link.l1 = "네 목숨이 아깝다면 말조심하는 게 좋을 거야... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "그것도 그래. 이제 말해 봐, 도대체 무슨 이유로 우리를 공격한 거야, 그것도 수브니에랑 같이...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "네 소브레니에는 욕심 많고 겁쟁이인 놈이야. 카스퍼가 제대로 혼쭐내고 돈 좀 쥐여주겠다고 하니까, 바로 착한 아이처럼 편지를 휘갈겨 쓰더라, 크흠...\n";
			link.l1 = "그래서 결국 그가 정말로 찾아냈네.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "찾았다, 찾았어. 이제 곧 죽게 될 거다. 네 그 작은 여자 친구도 마찬가지지. 캐스퍼가 너희 둘 다 갈기갈기 찢어버릴 거야, 헤헤. 나는 이미 죽은 목숨이나 다름없지만, 네 최후를 도와주지. 네가 그한테 붙잡혀서 살려달라고 애원하는 소리를 못 듣게 되는 게 아쉽군...\n";
			link.l1 = "알겠지, 나도 이 세상에 오래 못 있을 거야, 맞아. 그러니까 내가 마지막 숨을 거두기 전에 빨리 말해.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "그를 만나고 싶다면 체투말 만으로 가. 거기가 그가 사는 곳이야, 알지? 네가 그를 찾으려고 애쓸 필요 없어, 그가 직접 널 찾아올 테니까.";
			link.l1 = " 훌륭하군. 천천히 죽어도 괜찮아. 우리는 여기서 끝이야.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "그러길 바란다. 이제 지옥이나 가.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "오, 맙소사, "+pchar.name+"... 믿을 수가 없어, 정말 못 믿겠어, 알지! 우리 아버지가 이랬다고?!";
			link.l1 = "그런 것 같네, 알겠지? "+npchar.name+". 그 사람을 움직인 게 뭔지, 대체 누군지도 전혀 모르겠어, 알지... 하지만 또 다른 루퍼트 캐스퍼일 리는 없다고 생각해. 그런 우연은 세상에 없어.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "그럼 이제 우리 뭐해야 하는 거야? 내가 그 사람 눈을 똑바로 보고 뭐라고 말해야 하지?";
			link.l1 = "먼저, 그에게 접근해야 해. 아마 지금은 무법자가 됐을 거야, 그를 찾으려 했을 때... 그렇게 신경질적인 반응을 보였으니까. 그래도 어쨌든 그는 네 아버지잖아. 그리고 우리는 그를 찾으려고 엄청난 노력과 시간, 돈을 쏟아부었지.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "근데 만약 그 사람이 우리랑 말조차 안 하려고 하면 어쩌지? 왜 우리를 죽이라고 명령한 거야?";
			link.l1 = "적어도, 그가 자신을 노리는 사람이 정확히 누구인지 몰랐을 수도 있어. 파데이가 네 이름만 넘기고, 너에 대한 세부사항은 빼먹었을 수도 있고. 그렇지 않았다면, 우리가 지금 칼에 피를 묻힐 일도 없었겠지.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "이제 어쩌지? 우리 체투말 만으로 가는 거야? 근데 만약 그가 여기서 우리한테 함정을 파놨다면... 거기엔 또 뭐가 기다리고 있을지 누가 알아?";
			link.l1 = "그가 여기서 무슨 일이 일어났는지 알아차리기 전까지는 시간이 우리 편이야. 이 시간을 잘 활용하자.\n우리는 만으로 항해하고, 장교 중 한 명이 이끄는 분견대를 육로로 보내 지원하게 하자.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "그럴듯하네, 알겠어. 그런데 누가 이끌 건데?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "티칭이투. 그는 육상 전투의 베테랑이야. 그 누구도 그보다 더 잘 해낼 수 없어.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "클로드. 물론 좋아하진 않겠지만, 곧 괜찮아질 거야.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "에르퀼. 이런 일은 어떻게 처리하는지 그 사람은 정확히 알고 있어.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "토미. 무슨 일이 잘못돼도, 저 녀석은 어떻게든 빠져나올 거야, 믿어.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "롱웨이. 정글에서 적을 추적하는 건 이번이 처음이 아니야.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "알론소. 칼을 잘 다루고, 바보도 아니야.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "티칭이투가 잘 듣고 있어, 선장 "+pchar.name+".";
			link.l1 = "친구야, 네 앞에 중요한 임무가 있어. \n 체투말 만에 악당 무리가 숨어 있거든. \n 그놈들을 찾아내서 모조리 없애야 해. \n 우리는 배를 타고 바다에서 접근할 거야.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "우리 사람들로 구성된 분대를 이끌고 정글을 통해 저 놈들 뒤로 돌아갈 거야. 나한테 물어볼 거 있어?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "인디언은 질문이 없어. 내일 정오에 일행이 자리에 있을 거고, 거기서 매복해서 기다릴 거야.";
			link.l1 = "좋아, 티칭기투. 행운을 빌어.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = " 부르셨나요, 선장? ";
			link.l1 = "클로드, 너한테 시킬 일이 있어.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "우리는 전사들로 분대를 꾸려서 정글을 지나 체투말 만으로 가야 해. 거기서 루퍼트 캐스퍼라는 자가 이끄는 무리가 우리를 기다리고 있어. 놈들이 우리에게 고약한 함정을 준비해 놨지. 하지만 우리가, 아니, 네가 놈들을 놀라게 해 줄 거야. 내 신호에 맞춰 공격해. 질문 있나?\n ";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "정글을 헤치고 다니는 건 정말 싫어. 그래도 명령은 명령이니까, 알지? 내일 정오쯤에 거기서 보자. ";
			link.l1 = "행운을 빌어, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = " 듣고 있어, 선장. ";
			link.l1 = "에르퀼, 네가 할 일이 있어.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "멍청한 놈 머리에 총알 몇 발 박아줄 사람 필요해? 그게 나야, 항상 준비돼 있지, 알지?";
			link.l1 = "맞췄네. 우리 배에서 온 전투원들을 이끌고 정글을 지나 체투말 만까지 가야 해. \n거기서 우리가 올 거라고 기다리고 있을 그 갱단을 매복해서 덮쳐야 해.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "난 좀 더 어려운 걸 생각했거든, 선장. 하지만 이건 그냥 선술집 나들이잖아, 알지? 내일 정오까지 우리가 꼭 도착할 테니까 믿어도 돼.";
			link.l1 = "거기서 보자. 행운을 빌어, 에르퀼.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = " 하, 선장님, 왜 그렇게 심각해? 장례식이라도 가는 거야, 뭐? ";
			link.l1 = "항상 웃기는 녀석이지, 토미? 나도 한마디 해줄게 – 이번 달 월급 못 받아. 다음 달도 마찬가지고. 왜 그렇게 긴장했어?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "농담도 못 하겠네...";
			link.l1 = "모든 일에는 때가 있는 거야, 토미. 너 아직 배울 게 많아. 이제 잘 들어: 네 분대를 모아서 정글을 지나 체투말 만으로 가. 도착하면 내 신호를 기다려.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "정글을 헤치고 간다고? 아무리 빨라도 내일 정오 전에 도착 못 해.";
			link.l1 = "그러면 내일 정오에 거기서 만나자. 명령 없이는 싸우지 말고, 자리에서 이탈하지 마. 알겠지? 그래, 알아들었군. 이제 가서 준비해.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "오래 들었네, 선장.";
			link.l1 = "이봐, 너한테 줄 일이 있어.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "우리 사람들 중 일부를 이끌고 정글을 지나 체투말 만까지 가게 될 거야.\n거기서 적을 만날 수도 있으니, 네 사람들이 준비되어 있도록 해.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "롱웨이는 다 이해했으니 걱정 마, 선장. 내일 정오쯤 목적지에 도착할 거야.";
			link.l1 = "가, 그리고 조심해.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "저 불렀어요, 선장님?";
			link.l1 = "알겠지? 잘 들어, 알론소.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "너는 전사들 분대를 이끌고 정글을 지나 체투말 만까지 가게 될 거야.\n거기에는 악당 무리가 기다리고 있을 가능성이 높아.\n내가 신호를 주면, 너희는 자리를 잡고 뒤에서 그놈들을 공격해야 해.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "식은 죽 먹기죠, 선장님. 하지만 내일 정오 전에 만에 상륙하지 마세요\n저랑 제 선원들이 그때쯤이나 되어야 도착할 수 있으니까요.";
			link.l1 = "준비해, Alonso. 그리고 신의 가호가 있기를.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "찰스, 그거 봤어?";
			link.l1 = "벌써 우리를 기다리고 있는 것 같아. 저 굽이만 돌면 분명히 매복하고 있을 거야.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "그래도 우린 아직 멀쩡히 서 있잖아. 쟤네는 우리한테 총도 안 쏘려고 해, 알지. ";
			link.l1 = "아직 우리랑 먼저 얘기할 생각이 있을지도 몰라. 괜히 자극하지 말자 – 우리가 직접 가고, 우리 선원들이 뒤를 봐줄 거야. 자, 이제 이 모든 걸 끝내자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "거기서 멈춰! 한 발짝도 더 오지 마! 얘들아, 저 멋쟁이가 꼼짝이라도 하면 구멍 숭숭 뚫어버려. 여자애는 건드리지 마.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "아빠?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = " 음... 내 길고 험난한 인생에서 정말 많은 걸 봤지. 이제 더 이상 놀랄 일도 없겠다고 생각할 때마다, 인생이 꼭 아니라고 보여 주더라고. 그런데 네가 진짜 살아남았구나... 게다가 테레사의 모자까지 지켰네. 다시 그걸 볼 줄은 정말 몰랐어. ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = " 음... 내 길고 험난한 인생에서 정말 많은 걸 봤지. 이제 더 이상 놀랄 일은 없겠다고 생각할 때마다, 인생은 꼭 내 생각이 틀렸다는 걸 보여 주더라고. 그래서, 네가 진짜 살아남았구나, 줄리아... ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "오렐리가 내게 줬어, 그녀가... 세상을 떠나기 전에.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "정말 감동적이네... 눈물이 나올 것 같아. 난 그 모자가 테레사와 함께 묻혔다고 생각했거든. 내가 그걸 준 이후로 단 한 순간도 손에서 놓지 않았지. 네 어머니는, 그냥 하녀였지만, 모험심이 넘쳐서 귀에서 흘러나올 정도였어. Fleur-de-Lys를 점령할 때 그걸 발견하고, 테레사가 분명히 좋아하리란 걸 바로 알았지. 그 모자를 쓴 모습이 우스꽝스러웠지만, 신경도 안 썼어. 잠잘 때만 벗었으니까. 그런데 너, 줄리아, 너한테는 정말 잘 어울린다.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "줄리아? 아니야, 착각한 거야, 내 이름은 메리야...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "흠, 그래? 그래서 그 놈들이 내 말을 무시하고 제멋대로 행동했다는 거군. 뭐, 그 가톨릭 개새끼들한테 더 기대할 것도 없지.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "너... 너... 정말 내 아버지야?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "글쎄, 그게 아니었으면 너랑 네 친구는 이미 땅바닥에 총알 박힌 채로 누워 있었을 거야. 나는 신도 악마도 오래전에 안 믿게 됐지만, 어쩌면 진짜 있을지도 모르겠네. 적어도 신은 확실히 있겠지—네게 테레사의 얼굴을 줬으니까. 그 덕분에 네 목숨이 방금 살아난 거라고. 그 말이 뭐더라... 신의 뜻은 참으로 오묘하다, 알지? 하하하!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "아빠... 나... 난 잘 모르겠어, 알지...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = " 당연히 모르지. 어떻게 알겠어...";
			link.l1 = "딱히 딸을 만나서 기뻐하는 얼굴은 아니네요, 캐스퍼 나리. 방금 자기 딸이라고 인정해 놓고서 말이죠.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "재치가 부족하진 않네, 멋쟁이... 이름이 뭐였더라?";
			link.l1 = ""+GetFullName(pchar)+". 우리가 당신을 찾는 동안, 그동안 어떻게 지내왔는지 계속 궁금했어요. 살아남기나 했는지 말이에요. 그런데 여기서 꽤 잘 자리 잡으신 것 같네요, 노스우드 나리.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "아, 그것까지 파헤쳤구나. 뭐, 내 존경을 표하지. 개구리 먹는 나리, 내가 모든 꼬리를 다 잘라뒀다고 생각했는데, 더 할 말이 뭐 있겠어.";
			link.l1 = "아직 더 있어. 우리는 '콘월'호와 그 화물에 대해 알고 있고, 네가 한동안 빌려 썼던 조슈아 캐스퍼라는 이름에 대해서도 알아. 그리고 그 성씨—그건 영영 네 것이 된 것 같네.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "브라보(박수). 감탄했어. 혼자서 다 알아낸 거야, 아니면 내 소중한 아이도 도와줬어?";
			link.l1 = "메리 없이는 해낼 수 없었어. 그녀는 자기 부모님에 대해 모든 걸 알아내겠다고 결심했거든. 테레사에게 무슨 일이 있었는지는 금방 알아냈지만, 널 찾아내는 데는 꽤 오래 걸렸지...\n";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "이거 참 감동적이네, 눈물이 다 날 뻔했어. \n그래, 딸아, 이제 만족하니? 행복해? 아빠한테 안기고 싶어?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "이해가 안 돼요, 아버지... 왜 저를 이렇게 괴롭히는 거예요? 도대체 왜요?! \n(소리치며) 저를 거기에—그 난파선들에—버려둔 건 바로 아버지였잖아요! 그리고는 다시 돌아올 생각조차 안 했잖아요, 알겠죠! 왜요? 대체 아버지는 누구고, 저 뒤에 서 있는 사람들은 또 누구예요?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "말해 봐, "+pchar.lastname+", 저 아이는 항상 저렇게 성질을 부리나? 그건 엄마를 닮아서 그래. 테레사는 정말 멋진 여자였지, 내가 만난 사람 중 최고였어. 하지만 화가 나면 정말 소리 지르며 난리를 쳤다니까... 뭐라 할까... 아일랜드 사람이잖아.";
			link.l1 = "그녀를 모욕할 생각 하지 마! 메리는 네 불행에 아무런 잘못이 없고, 이런 대접을 받을 이유도 전혀 없어.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "나를 입 다물게 하려는 거냐, 꼬마?!";
			link.l1 = "반대로요. 당신의 이야기를 우리에게 들려줬으면 해요. 그건 메리가 꼭 알아야 할 중요한 일이거든요. 하지만 메리를 모욕하게 두진 않을 거예요. 그러니 언행을 조심하세요.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "네가 내가 너한테 속마음을 털어놓고 싶어서 안달 난 줄 알아? 내 인생은 이렇게 흘러왔고, 너희 교황파들이 자주 하는 말처럼—하느님이 증인이시다—나는 아무것도 후회하지 않아. 그때 테레사를 잃은 것만 빼고—그 여자 때문에 말이야. 내가 너를 미워하냐고, 내 딸? 예전엔 그랬을지도 모르지. 하지만 지금은 너한테 아무런 감정도 없어.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "엄마가 돌아가신 게 내 탓이라고?! 그게 말이 돼? 내가 뭘 했는데 - 태어난 게 죄야? 그게 내 죄냐고? 좋아, 아버지. +pchar.name+이 맞아 - 그냥 다 말씀해 줘요. 그 다음엔 우리가 떠날게요. 다시는 제 얼굴 볼 일 없을 거예요... 그게 원하시는 거라면... (울기 시작한다)";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "아아, 테레사랑 똑같군. 마치 내가 이십 년 전으로 돌아간 기분이야, 알겠지? 에라, 네가 원하는 대로 해. 그 모든 기억을 다시 떠올리는 게 즐겁진 않을 거야... 그러니까, 이 얘기가 끝날 때쯤 내가 네 머리에 총알을 박고 싶어진다면, 자기야 - 그건 네 탓이야.";
			link.l1 = "그럼 너도 총알 맞게 될 거야, 루퍼트. 네 계획에 그건 없겠지 – 네 목숨을 꽤 소중하게 여기는 사람처럼 보이거든.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "내 인생이 얼마나 가치 있는지는 알아, 꼬마야. 하지만 그걸 소중히 여기는 건 또 다른 문제지. 근데 네가 그걸 알기나 하겠어? 좋아, 본론으로 들어가자. 전부 다 듣고 싶다고? 그럼 들어. 나는 1611년에 이스트번 근처 농장에서 태어났어. 채널 해안에 있는 작은 마을이지. 뭐, 1년쯤 오차가 있을 수도 있지, 누가 알아—우리 어머니는 날짜 같은 건 제대로 기억 못 하셨거든. 술을 얼마나 퍼마셨는지 생각하면 그럴 만도 하지.";
			link.l1 = "힘든 어린 시절이었어? 알겠어.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "네가 듣고 싶다 했으니, 잘 들어, 그리고 입 다물고 똑똑한 척하지 마. 난 아버지란 사람 한 번도 없었고, 왜 그런지도 몰랐어—하지만 너랑은 달라, 꼬마야, 난 그런 거 신경도 안 썼지. 그 사람한테 받은 성씨만으로도 난 충분했어. 내가 열세 살 때였지, 어느 날 밤에 덩케르크 사략선들이 해안에 상륙했어. 알지, 지금은 다들 그 얘기 꺼내기 싫어하지만, 그때 고생한 건 네덜란드인들만이 아니었어, 우리도 그랬지—영국 할멈 동쪽 해안에 살던 우리도 말이야.";
			link.l1 = "그 얘기 들었어. 그 놈들은 한 명도 살려두지 않았다며. 너는 어떻게 살아남은 거야?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "그들이 남기고 간 끔찍한 일들을 나도 알아. 늙은이도, 아이도 아무도 살려두지 않았지. 그런 네가 살아남았다는 게 더더욱 놀라워.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "그날 밤, 그 교황 추종자 돼지들이 여러 농장을 불태웠어, 우리 집도 포함해서. 나는 간신히 빠져나왔지만, 내 엄마는 사과주를 너무 퍼마셔서 자기 뚱뚱한 엉덩이를 침대에서 일으키지도 못하고 그냥 거기서 타 죽었지. 물론 그건 전적으로 엄마 잘못이었어. 그래도, 내 엄마였잖아.";
			link.l1 = "그때부터 너는 모든 가톨릭 신자들을 미워하게 된 거야?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "그날 밤, 그 가톨릭 돼지놈들이 여러 농장을 불태웠어, 우리 집도 포함해서 말이야.\n나는 간신히 빠져나왔지만, 우리 엄마는 사과주를 너무 퍼마셔서 자기 뚱뚱한 엉덩이를 침대에서 끌고 나오지도 못하고 그냥 거기서 타 죽었지.\n물론 그건 다 엄마 잘못이야 – 그래도 내 엄마였어.";
			link.l1 = "그때부터 모든 가톨릭 신자들을 미워하게 된 거야?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "그때 나는 굶주림을 증오하게 됐지, 잘난 척 좀 그만해. 너는 아마 진짜로 굶주림이 뭔지 몰랐겠지만, 나는 뼛속까지 느꼈거든. 나는 북쪽, 수도로 갔고, 해군에 지원했어—거기선 밥보다 채찍질을 더 자주 줬지. 하지만 몇십 대 맞고 나니 정신이 번쩍 들더라. 그 뒤로는 익숙해졌고—바다에서의 삶을 사랑하게 됐어. 특히, 지루할 틈이 없었으니까...\n";
			link.l1 = "그럴 만하네. 왕립 해군의 명성은 따로 말할 필요도 없지.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "1633년에 나는 중위 시험에 합격해서 코른월 브리그에 배치되었어.";
			link.l1 = "조슈아 캐스퍼의 지휘 아래.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "아, 맞아... 조슈아 캐스퍼... 그 자식보다 더 나쁜 놈은 함대 전체를 뒤져도 없을걸. 그렇게 많은 세월이 지났는데도, 그 돼지는 아직도 내 꿈에 나타나 괴롭혀.";
			link.l1 = "그럼 그는 뭘 했는데? 네가 너무 열성적이라고 추가 경계 근무를 시켰어? 아니면 사실은 몰래 가톨릭 신자였던 거야?\n";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "그 잔인한 자식이 선원들을 그렇게 혹독하게 굴려서, 사람들은 완전히 탈진해서 바다에 떨어지기도 했어. 네가 그 자의 이름을 알고, '콘월'의 지휘관이었다는 것도 아는 걸 보니, 분명히 그의 서류도 봤겠지—고양이 혀로 핥은 엉덩이처럼 번쩍거리는 서류 말이야. 우리 영웅 조슈아는 훈장 상자를 통째로 갖고 있었지. 너처럼 순진한 젊은이들이 그 밑에서 복무하고 싶어 했어—뭐라 해도, 그 사람은 비 온 뒤 젖은 풀밭을 예리한 낫으로 베듯이 너희 개구리 먹는 놈들을 쓸어버렸거든, 알지?—하지만 한 번 '콘월'에 올라타고 나면, 다들 금방 실수했다는 걸 깨달았지.   우린 그 꼴을 더는 못 참겠더라고, "+pchar.lastname+". 어떤 이들은 전출 청원서까지 썼지\n하지만 그건 해군성의 선반 위에서 사라지거나, 아니면 그들의 화로 속에서 사라졌어. 그래도 인생은 우리에게 기회를 줬지\n우리를 '콘월'에서 내보내진 않았지만, 대신 다른 누군가를 태웠거든. 존 로손 – 크롬웰의 총애를 받던 자, 너도 들어봤을 거야.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "그때도 이미 아첨하는 법은 잘 알고 있었지 — 아마 그 녀석이랑 캐스퍼가 잘 지냈을지도 모르는데, 내가 그걸 못 하게 막았어. 내가 꼬마 조니를 함정에 빠뜨렸고, 조슈아는 사정을 다 알지도 못한 채 분노에 휩싸여 지팡이로 그를 두들겨 팼지.";
			link.l1 = "장교로서는 정말 굴욕이지. 그리고 로슨이 자기 아버지한테 전부 말했어?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "물론 그랬지 – 그게 내 계획이었으니까. 그런데 말이야, 시스템이 자기 자신을 삼킬 수는 없어. 결국 모든 게 조용히 덮였어 – 로슨은 조기 승진을 제안받았고, 조슈아와 '콘월'은 그림자 속으로 밀려났지 – 우리는 런던에서 영국 남쪽 플리머스로 전출됐어. 계속 너희 개구리 먹는 놈들을 괴롭힐 수도 있었겠지만, '콘월'은 보급선으로 바뀌어서, 아일랜드의 작은 마을 던도크로 군수 물자를 나르게 됐지.";
			link.l1 = "그리고 거기서 테레사를 만난 거야?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "처음으로 거기에 정박했었지. 테레사 오패트, 그곳 선술집의 바텐더였어. 우리가 서로를 위해 태어났다는 걸 깨닫는 데 사흘이나 걸렸지. 너도 무슨 말인지 알겠지, 알지? "+pchar.lastname+", 그렇지?";
			link.l1 = "그런가 봐.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "지금 너를 보면, '사랑'이란 말의 뜻조차 모를 것 같아.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "나는 그 누구보다도 더 멋진 사람을 만난 적이 없어 – 그 전에도, 그리고 그 후 스무 해가 지나도록 한 번도 없었지. 내 인생에서 처음으로 진정한 행복을 느꼈고, 그녀도 그랬어 – 아니, 적어도 그녀는 그렇게 말했지.";
			link.l1 = "그리고 네가 그녀에게 같이 떠나자고 했어?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "나는 그 누구보다도 더 멋진 사람을 만난 적이 없어 – 예전에도, 그리고 그 후로 스무 해가 지나도록 말이야. 내 인생에서 처음으로 진짜 행복하다고 느꼈고, 그녀도 그랬어 – 아니, 적어도 그녀는 그렇게 말했다고 했지.";
			link.l1 = "그리고 너는 그녀에게 같이 떠나자고 했어?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "당연히 아니었지 – 그건 불가능했어, '콘월'은 여전히 사생아 선장이 이끄는 군함이었으니까. 영원처럼 느껴진 일주일이 지난 후, 우리 브리그는 플리머스로 다시 출항했어. 두 달 뒤에야 던독으로 돌아왔지 – 그리고 테레사가 내게 깜짝 소식을 전했어: 그녀가 임신했다는 거야.";
			link.l1 = "그래, 여자랑 같이 자면 그런 일 생기기 마련이지.";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "똑똑한 척하지 마, 이 녀석아. 테레사가 내 어깨에 기대서 흐느끼고 있었고, 나는 뭘 해야 할지 고민하고 있었지. 정말로 그녀 곁에 있고 싶었어, 정말 그랬어 – 하지만 그때조차도, 그 아이에게서 좋은 일이 일어날 것 같지는 않았어.\n아직 늦지 않았을 때 테레사에게 아이를 지우라고 설득하려고 했지 – 하지만 돌아온 건 더 심한 히스테리 발작뿐이었어. 그땐 우리 둘 다 뭘 해야 할지 몰랐지 – 그래서 우리는 두 달만 더 기다렸다가, 다음에 ‘콘월’이 던독에 돌아올 때까지 기다리기로 했어. 그때까지만 해도 해군성은 카스퍼에게 내린 분노를 자비로 바꾸지 않았으니까\n우리가 돌아온 뒤에 나는 곧바로 그녀를 찾지 못했어 — 테레사의 임신은 이미 눈에 띄게 드러났고, 그녀가 일하던 선술집 주인 말로는, 그녀 아버지라는 인간이 그녀를 때리고 집에 가둬버렸다는 거야. 말할 것도 없이, 나는 그 늙은이를 아주 심하게 다뤄서 거의 창자가 쏟아질 뻔했지. 당연히, 그녀가 그 집에서 계속 살 수 있다는 건 있을 수 없는 일이었어.";
			link.l1 = "그리고 그녀를 '콘월'호에 데려왔어?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "나는 빠르게 결정을 내려야 했어. 카스퍼가 배에 여자가 타는 걸 절대 용납하지 않을 거란 걸 알고 있었거든. 그래서 우리가 출항한 다음 날 밤에 보트를 훔쳐서, 우현 쪽에 있을 더블린으로 가려고 했지.";
			link.l1 = "그래서 어떻게 됐어? 잡힌 거야?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "맞아. 캐스퍼는 이미 위스키를 듬뿍 따라 마시고 있었거든, 그래서 어떤 애원도 들으려 하지 않고 그냥 그 여자애를 바다에 던지라고 명령했어. 내가 아무리 애원해도, 그는 숨이 넘어가라 웃기만 했지—젠장, 이 얘기를 하면서도 아직도 그 웃음소리가 머릿속에서 들려...\n";
			link.l1 = "그래서 그때 반란을 일으키기로 한 거야?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "달리 선택지가 없었어. 근처 경비의 허리띠에서 권총을 낚아채 그 자식 이마에 구멍을 뚫었지. 바로 그 자리에서 학살이 벌어졌어 — 아무도 선장을 좋아하진 않았지만, 재판에 대한 두려움이 더 컸거든. 그 일로 선원 중 거의 3분의 1이 목숨을 잃었어 — 우리가 겨우 정신을 차렸을 땐, '콘월'의 갑판 전체가 피로 뒤덮이고 죽은 동료들의 시체로 가득했지.";
			link.l1 = " 그 후로는, 영국으로 돌아가는 건 물 건너갔겠네. 거기 가면 너희 전부 교수형 당할 테니까.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "나는 ‘콘웰’을 타고 대서양을 건널 수 있을 거라 확신했어. 여기서는 우리 얼굴을 아는 사람이 아무도 없었고, 그 덕분에 새로운 삶을 시작할 기회가 생겼지. 다른 장교들을 설득하는 건 별로 어렵지 않았어 — 내 권위 때문이 아니라, 평범한 선원들은 전혀 모르는 몇 개의 궤짝 안에 든 물건들 덕분이었지. 선원들은 결정했어 — 조슈아 캐스퍼는 살려두기로. 우리, 하이랜드 출신 장교들은 시간을 벌기로 하고, 궤짝 하나를 희생해서 앤티과에 들어가 내가 그의 이름을 쓰기로 했지. 그 다음엔 프로비던스로 향할 계획이었어.\n 실제로 그렇게 됐어: 아무도 바뀐 걸 눈치채지 못했지. 하지만 프로비던스까지 이틀쯤 남았을 때, 어떤 자식이 두 번째 궤짝 얘기를 떠벌려서 선원들 사이에 분열이 일어났어.";
			link.l1 = "그래서 이제 그들이 반란을 일으킨 거야?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "아니, 하지만 우리 영광스러운 왕을 위해 계속 복무하겠다는 사람 수가 빠르게 줄었어. 그리고 해적이 되겠다고 나서는 사람도 별로 없었지. 그래서 우리는 중간 길을 택했어 - 프랑스 항구에 정박해서 배를 팔고, 판매금과 보물상자 돈을 나눠 가진 다음 각자 갈 길을 가기로 했지.";
			link.l1 = "그리고 네가 그렇게 싫어하는 가톨릭 신자들 사이에서 살아야 한다는 건 신경도 안 썼어?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "그때는 어디에 닿든 상관없었어. 테레사는 용감한 척했지만, 석 달 내내 흔들리는 배에서 지내다 보니 임신한 여자라면 누구나 그럴 법하게 힘들어했지. 그리고 석 달 전과 마찬가지로, 내가 가톨릭 신자들한테 둘러싸여 있든 말든, 그녀와 함께라면 아무래도 상관없었어.";
			link.l1 = "하지만 카리브해 북서쪽에는 프랑스 식민지가 없었고, 원래부터 없었어.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "'콘월'호에서 상황이 극에 달했을 때쯤엔, 우리는 이미 순풍을 타고 항로의 절반을 지나왔고, 그때쯤이면 세인트 크리스토퍼로 방향을 바꿀 수도 없었지...";
			link.l1 = "그리고 목적지로 토르투가를 선택한 거야?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "그때는 그냥 작은 마을이었지. 혹시라도 관헌이 쫓아올까 봐, 선미에 달린 명판을 바꿨어—그래서 '콘월'이 '랭글러'가 된 거야.";
			link.l1 = "그런데 왜인지, 너는 거북이섬에는 결국 도착하지 못했지.\n토르투가가 아니라 쿠바 서쪽까지 그렇게까지 항로를 벗어날 수는 없었을 텐데, 그렇지?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "알아두라고 하는데, 나는 경험 많은 항해사야—대부분보다 더 잘하지. 실수는 없었어, 우리는 정확히 북쪽으로 꾸준히 항해하고 있었지. 그런데 윈드워드 해협에 들어서자마자 끔찍한 돌풍이 우리를 덮쳤어. 아직도 어떻게 우리가 쿠바 해안에 부딪히지 않고, 오히려 해안을 따라 끌려갔는지 궁금해...\n";
			link.l1 = "진짜 기적이야, 그 이상도 그 이하도 아니지.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "흐느끼는 테레사를 꼭 안고, 나는 온 마음을 다해 주님께 우리에게 구원을 내려 달라고 간절히 기도했어. 그리고 정말로 주님께서 우리를 도와주셨지.";
			link.l1 = "너는 정의의 섬에 표류해서 밀려왔어.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "정의의 섬 – 맞아! '랭글러'가 암초에 부딪혔을 때 배가 두 동강이 났지만, 어떻게든 가라앉지 않고 버텼지 – 다른 난파선들이 쌓여 있던 곳까지 떠밀려갈 만큼은 말이야. 폭풍은 거의 이틀이나 더 계속됐고, 마침내 잠잠해졌을 때 – 그 불쌍한 작은 섬의 사람들이 우리를 구해줬어.";
			link.l1 = "너, 테레사, 그리고 선원 두 명 더. 그 다음에 무슨 일이 있었는지는 대충 알고 있어. 이제 감옥에서 어떻게 나와서 섬을 떠났는지 말해 봐.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "그때 그냥 나를 쏴버렸으면 좋았을 텐데...\n앞에 무슨 일이 기다리고 있는지 알았다면, 난 그 쇠창살에 몸을 묶고 한 치도 움직이지 않았을 거야.";
			link.l1 = "타르탄 배가 브리그보다 정말 덜 편했어, 알지? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "너도 타르탄 타고 가다가 폭풍에 휘말렸다고만은 말하지 마, 알겠지?";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "타르탄? 하하하... 맞아, 그게 내 계획이었지. 난 운이 좋다고 생각했어. 감옥 경비대장은 영국 해군의 전직 장교였는데, 나를 불쌍히 여겼거든. 그는 쿠바 밀수업자들의 타르탄에 대해 전부 말해줬고, 그들이 나를 처형할 계획이라는 것도 알려줬어. 명예로운 사람이라고 해야 할까—내 운명을 운에 맡기라고 나를 풀어주겠다고 제안한 것도 그 사람이었으니까.";
			link.l1 = "이해가 안 돼... 타르탄선을 타지 않았다면, 그럼 어떻게 섬을 떠난 거야?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "타르탄? 하하하... 맞아, 그게 내 계획이었지. 난 운이 좋다고 생각했어. 감옥 경비대장은 영국 해군 출신의 전직 장교였는데, 내 불운을 안타까워했거든. 쿠바 밀수업자들의 타르탄에 대해 알려준 것도 그 사람이었고, 그들이 날 처형할 계획이라는 것도 말해줬어. 어쩌면 그 사람은 명예로운 사람이라고 할 수 있을지도 몰라—직접 날 풀어주겠다고 제안했으니까, 내 운명을 운에 맡기라고.";
			link.l1 = "이해가 안 돼... 타르탄 배가 아니라면, 그럼 어떻게 섬을 떠난 거야?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "그냥 조용히 듣기만 하면 이해할 거야. 나는 타르탄 쪽으로 헤엄치고 있었어, 오랫동안 헤엄쳤지—비의 장벽 너머로 빛이 보일 때까지. 그건 정말 믿을 수 없는 일이었어, 젠장. 반쯤 가라앉은 갈레온의 갑판 위에서 태양처럼 빛나고 있었지, 그래서 나는 곧장 그쪽으로 갔어. 그게 내 인생에서 최악의 실수라는 걸 아직은 몰랐지. 승선 사다리를 타고 물에서 올라왔고—빛과 마주하게 됐어. 그 빛은 황금 조각상 위에서 반짝이고 있었고...\n";
			link.l1 = "쿠쿨칸의 우상이지. 맞아, 그때는 'San Jeronimo'가 아직 침몰하지 않았었지...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "그래서, 너도 그를 봤구나, "+pchar.lastname+"?";
			link.l1 = "그냥 본 게 아니야. 그걸로 공간을 여행했거든, 한두 번이 아니었지, 알지?";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "거짓말이야! 몇 번이나 죽을 뻔했다고, 그렇다면서?! 그런데 어떻게 이렇게 멀쩡하게, 이렇게 생기 넘치게 서 있을 수가 있어?!";
			link.l1 = "내가 옮겨진 후에 인디언 약을 마셨는데, 그게 내가 살아남고 힘을 되찾는 데 도움이 됐어.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "아, 그래서 그런 거였구나. 내가 다시 힘을 되찾는 데 얼마나 오래 걸렸는지 알아? 알기나 해?!";
			link.l1 = "짐작할 수 있을 것 같아. 우상에 손을 댔고, 그게 널 도미니카로 보냈지 – 인디언 마을로, 거기서 널 그 동상에게 제물로 바쳤고, 그 다음엔 본토에 떨어진 거지, 맞지?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "맞아. 그때 그 동상 옆에 누워서 느꼈던 고통은 평생 처음이었어. 뭐에 비유해야 할지도 모르겠네. 돌로 만든 집이 무너져서 깔린다 해도, 그 정도로는 고통스럽지 않을 거야. 정신을 차리자마자 원주민들이 또 몰려오는 게 보였지. 내가 그들의 말을 할 줄 알았다면—진짜 맹세코, 그 자리에서 날 죽여 달라고 빌었을 거야.";
			link.l1 = "근처 마을에서 온 미스키토 인디언들이었어?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "저놈들이야. 놈들이 나를 오두막 중 하나로 끌고 갔는데, 거기서 이상한 원주민 하나가—다른 애들이랑은 달라 보였어—뭔가를 내 입에 바로 부어 넣더라고. 통증이 좀 가라앉긴 했지만 완전히 사라지진 않았어. 저녁쯤엔 나를 불가로 끌고 나가더니, 그 칠한 자식이 무슨 의식을 시작하더라고. 한심한 놈.";
			link.l1 = "스네이크 아이... 네 목숨을 구해준 거, 그 사람한테 고마워했어야지.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "구출?.. 3년, "+pchar.lastname+". 3년 동안 나는 거의 움직이지도 못한 채 누워 있었어, 오줌과 똥을 지리고, 토한 데서 깨어나곤 했지\n— 그 역겨운 냄새 나는 약과 물약들을 자꾸 내 목구멍에 쑤셔 넣으니까 도저히 견딜 수가 없었거든! 그리고 나서 또 거의 1년을 다시 걷는 법을 배우는 데 썼어.";
			link.l1 = "가슴 아픈 이야기네. 그런데 솔직히, 너한테 거의 동정심이 들 정도야.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "네 동정심은 네 교황 그 뚱뚱한 가톨릭 엉덩이에나 쑤셔 넣어. 난 아무도 동정할 필요 없어. 계속 말해줄까, 아니면 잠깐 울 시간이라도 필요해, 꼬마 공작아?\n";
			link.l1 = "이번 항해로 네 예의가 나아진 것 같진 않네. 뭐, 메리를 위해서라면 참아줄게. 그래도 우리가 이미 중요한 건 알게 됐지만, 끝까지 네 얘기를 들어보자.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "어떻게든 다시 일어나서, 나는 저주받은 마을을 떠나 해안, 아마티케 만으로 향했어. 거기서 근처에 정박해 있던 밀수꾼들을 만났고, 그들과 합류했지. 그때 나는 내 이름을 루퍼트 캐스퍼라고 했어 — 내 이름을 포기하고 싶진 않았지만, 내 인생을 망친 자들 중 한 명의 성은 그대로 썼지. 내가 왜 여기까지 오게 됐는지 절대 잊지 않으려고 말이야.";
			link.l1 = " 너한테는 모두가 잘못했지, 노스우드... 너 자신만 빼고 말이야. 그래도 이해는 가. 수년간의 굴욕과 고생 끝에, 이제는 이 숲에 갇혀버렸으니. 누가 정신이 멀쩡하겠어? ";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "너도 고생 많았지, 노스우드. 그건 의심할 여지가 없어. 그리고 지금, 네가 어디에 있는지 봐... 숲속, 문명의 끝자락이야. 여기서 정신줄 놓을 일은 없을 거야...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "내가 이 숲의 주인이야, "+pchar.lastname+". 15년이 넘는 세월 동안, 나는 밀수선의 비참한 선원에서 그들의 우두머리로 올라섰지. 그냥 작은 배의 선장이 아니라, 아마티케 만에서 죽음의 만까지 해안을 모두 지배하는 주인이 되었어.";
			link.l1 = "음, 그건 정말 대단한 반격이네, 인정할게.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "나는 이 숲의 주인이야, "+pchar.lastname+". 15년이 넘는 세월 동안, 나는 밀수선의 비참한 선원에서 그들의 우두머리로 올라섰어. 그냥 작은 배의 선장이 아니라, 아마티크 만에서 죽음의 만까지 해안 전체를 지배하는 주인이 되었지.";
			link.l1 = "음, 그건 정말 대단한 반격이네, 인정할게.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "어떤 놈들은 여기가 숲의 악마의 영역이라고 하더라... 참 뻔뻔한 거짓말이지 – 여긴 내 땅이야. 그리고 스벤손도 그걸 알아, 하하하. 그 자가 부하들을 여기로 여러 번 보냈지, 내가 누군지 알아내려고 말이야 – 근데 한 놈도 살아서 돌아간 적 없어, 크크. 내가 밀수꾼으로 처음 이름을 알렸던 시절을 아는 놈이나, 이 숲 어디에 내가 사는지 아는 놈은 손에 꼽을 정도지.";
			link.l1 = "그래서 이제 다른 이름을 쓰는구나. 누가 루퍼트 캐스퍼를 찾는다고 하니까 네가 당황한 것도 무리가 아니지.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "당황한다고? 진심이야, 꼬마? 여기서 당황하는 건 너 하나뿐이야 – 내 구역에서, 내 사람들한테 둘러싸여, 완전히 내 손아귀에 있잖아! 내가 너한테 뭘 하든 내 마음이야. 그리고 저 여자도 마찬가지지 – 내가 그 모든 고통을 겪게 만든 이유니까!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "너 완전히 미쳤어, 그냥 미친 거야, 알지? 너를 고칠 약도, 의사도 난 몰라, 루퍼트 노스우드! 네가 지옥을 겪은 건 알지만... 그렇다고 그걸 다 내 탓으로 돌릴 수는 없잖아?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "이미 말했잖아 – 너 아니었으면 이런 일은 아무것도 일어나지 않았을 거야. 그냥 인정해, 알지?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "그만 놔둬, "+npchar.name+". 이제 충분히 들었어. 어떤 길은 정말 끝까지 가면 안 되는 법이지. 우리가 이 일에 끼어들기로 했을 때부터 불길한 예감이 들었거든. 그런데도 그걸 무시했지. 아쉽네.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "그래, 그랬다면 너희 둘 다 여기 이렇게 갇혀서 아무것도 할 수 없는 신세가 되진 않았겠지. 이제 네가 직접 느껴 봐라, 딸아, 내가 겪었던 걸!";
			link.l1 = "누가 우리가 아무것도 못 한다고 했어? 대에에열, 무장해!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "무슨 일이야, 풋내기? 누굴 잃었나? 하하하... 하하하. 하하하하하하하!!! 야, 지금 네 얼굴 좀 봐라, 이 바보야! 이봐, Mason, 손님들한테 줄 내 선물 좀 가져와.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "이 자식아! 내 사람들은 어디 있지?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "나를 기습할 수 있다고 생각한 그 한 줌의 바보들 말하는 거야? 내 친구인 주점 주인이 네가 마을에 온 걸 제때 알려줘서, 놈들에게 딱 어울리는 환영을 해줬지... 몇몇은 간신히 도망쳤어. 하지만 걱정 마 – 한 놈은 살아서 붙잡았거든. 오늘 네 앞에 어떤 운명이 기다리고 있는지 직접 확인할 수 있을 거야.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "이 악당! 이 일에 반드시 대가를 치르게 될 거야! (울먹이며) 맹세해, 알겠지!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "알론소! 너를 다시 보게 되어 정말 기뻐!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "나도 너를 다시 보게 되어 정말 반갑다, 선장! 누가 그 악당에게 네가 쫓고 있다는 걸 귀띔해줬는지, 가는 도중에 포도탄 세례를 받았어. 간신히 몇몇 남자들과 후퇴해서 바로 항구로 달려가 널 경고했지. 다행히도, 당직 경비병이 내가 급히 마을에서 산 바크를 타고 오는 걸 보고 바로 상황을 파악했어. 그는 재빨리 사람들을 모았고 — 우리가 여기로 달려와 도우러 온 거야.";
			link.l1 = "고마워, 친구야. 네가 우리를 확실한 죽음에서 구해줬어.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "그건 아무것도 아니야. 다음엔 뭐하지, 선장?";
			link.l1 = "선원들을 모아서 배로 가. 메리랑 나는 단둘이 있을 시간이 좀 필요해.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "맙소사, "+pchar.name+"... 아직도 못 믿겠어, 정말로. 내 아버지가... 괴물이라니... 왜 나한테 이런 짓을 한 거지? 정말로 미쳐버린 걸까?";
			link.l1 = "그는 끔찍한 고통을 견뎌야 했어. '콘월'호에서의 반란, 대서양을 건넌 탈출, 폭풍, 그리고 네 어머니의 죽음까지. 코만치의 약 없이 그 우상들의 문을 어떻게 통과했는지 상상도 할 수 없어 – 하지만 바로 그게 그의 정신을 망가뜨린 거야.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = ""만약 그 사람이 원래부터 그런 사람이었다면 어쩌지? 아니면, 똑같이 악당이었지만 조금 더 부드럽고, 정말로 우리 어머니를 사랑했을 수도 있잖아? 어쩌면 이 모든 일이 그 안에 있던 걸 그냥 풀어준 것뿐일 수도 있고. 그리고 만약 그렇다면... 나한테도 그 사람의 무언가가 있는 건 아닐까? 그럴 수도 있지,"\n "+pchar.name+", 알지?";
			link.l1 = "너, 확실히 그 사람한테 뭔가 배웠네, "+npchar.name+". 오늘 싸움에서 봤어 – 너는 그 사람처럼 똑같은 결의와, 눈빛 속의 불꽃, 그리고 그 분노까지도 지니고 있더라. 하지만 그의 광기는 없어. 너는 완전히 다른 사람이야. 살아 있고, 마음을 숨기지 않고, 모든 걸 드러내지. 바로 그게 내가 너를 사랑하게 된 이유야. 그리고 노스우드가 맞았던 것 같아: 너는 네 어머니의 기개를 온전히 물려받았어.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "정말 그렇게 생각해, 자기야?";
			link.l1 = "물론이지, 내 사랑. 그냥 우연히 그 사람을 만났더라면, 그가 누구인지 몰랐다면, 네가 그와 가족이라는 건 절대 몰랐을 거야.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "있잖아, 정의의 섬에는 딱히 재미있는 게 없어. 어릴 때부터 펜싱을 좋아했거든—처음엔 나무 막대기로 남자애들이랑 싸웠고, 나중엔 어른 남자들이랑 진짜 칼로 겨뤘지, 알지? 항상 그들과 동등해지고 싶었어... 그런데 이상하게도, 내가 이겼을 때조차도 늘 더 약하다고 느꼈어. 그래서 그냥 집에 가서 연습을 더 했지. 손이 떨릴 때까지 몇 시간이고 훈련했어, 알지? 네가 말하는 그 불꽃이 이런 거야? 네가 말하는 그 분노?";
			link.l1 = "어떻게 보면… 맞아. 나는 그 불꽃이 네가 생각하는 것보다 훨씬 더 큰 힘을 준다고 생각해. 그리고 네가 좋아하든 말든, 그건 네 아버지에게서 받은 선물이야. 그분이 일부러 주려고 한 건 아니더라도 말이야.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "우리가 과거를 파헤친 게 정말 옳은 일이었다고 생각해?";
			link.l1 = "이제 모든 걸 알게 됐으니... 더 이상 그렇게 좋은 생각 같진 않아. 그래도 진실을 알고 싶다면, 그게 마음에 들지 않을 수도 있다는 걸 각오해야 해.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "네 말이 맞아, "+pchar.name+", 알겠지... 여기서 좀 더 있어 보자. 아직은 배로 돌아가고 싶지 않아. 그냥... 이렇게 조용히 앉아 있고 싶어.";
			link.l1 = "물론이지, 자기야. 나도 막 그 얘기하려던 참이었어.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name + ", 딱 맞춰 왔네, 선장 " + pchar.name + ".";
			link.l1 = "네가 믿을 만한 친구라는 거 알고 있었어. 고마워 — 아무도 너만큼 잘 해낼 수 없었을 거야.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "정글은 " + npchar.name + "의 집이야. " + npchar.name + " 정글에서 싸울 수 있어 기뻐. 정글은 힘을 주지 " + npchar.name + ".";
			link.l1 = "그래서 내가 너를 분대장으로 세운 거야. 그리고 그 결정이 옳았지 — 보다시피, 그들이 우리를 두 팔 벌려 환영했잖아.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "어떤 선장 " + pchar.name + " 다음엔 뭐할 생각이야?";
			link.l1 = "메리랑 나, 잠깐만 단둘이 있을 시간이 필요해. 부상자들을 모아서 배로 데려가. 죽은 자들도 함께 데려가라 — 바다에 묻어줄 거야. 그리고, " + npchar.name + "... 알론소에게 메리의 아버지는 여기, 제대로 된 신교 방식으로 묻혀야 한다고 전해 줘. 이건 너랑 알론소만 알아야 해. 아무도, 심지어 메리조차도 알면 안 돼. 이미 충분히 고생했으니 더 고통받게 할 필요 없어.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name + " 알겠어, 선장 " + pchar.name + ". 티칭기투가 다 할 거야.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "거친 놈들이었지... 그래도 우리가 한 수 위였잖아, 하하! 여기서 썩게 두고, 다시는 우리한테 덤빌 생각 못 하게 해 주자.";
			link.l1 = "고마워, " + npchar.name + ", 정말 잘해줬어. 내가 너를 우리 뒤를 지키라고 보내지 않았다면 메리에게... 아니면 나에게... 무슨 일이 일어났을지 생각만 해도 아찔해...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "하, 선장, 당신이라면 어떻게든 해냈겠지 — 내가 알잖아. 그들의 두목이 들고 있던 그 커다란 칼 봤어? 난 눈을 뗄 수가 없더라. 만약 마음에 안 든다면, 나한테 선물해도 기분 안 상할 거야.";
			link.l1 = "흠... 두고 보자고, 친구. 일단은 살아남은 자들을 모아서 배로 가. 쓰러진 이들도 데려와라 — 바다에 보내줄 거다. 그리고... 그 우두머리, 그는 메리의 아버지였지. 알론소를 데려가서 여기 어딘가에 개신교 방식으로 제대로 묻어 줘. 무덤이 어디 있는지는 아무도 몰라야 해. 특히 메리는 절대 알면 안 돼. 그런 아픔은 필요 없어.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "알겠어, 선장님. 잠깐만... 다시 생각해보니까... 됐어. 내가 갈게.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "여기 진짜 더워, 선장. 그 자식들 딱 벌받았지. 우리가 나타났을 때 그 꼬마 녀석 얼굴 일그러진 거 봤어?";
			link.l1 = "그 녀석은 분명 이런 일이 일어날 줄 전혀 몰랐지. 나랑 메리도 그가 그렇게 비열한 놈일 줄은 예상 못 했고. 그래도 우리가 뒤를 맡기로 했을 때 내 직감은 틀리지 않았어.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "카리브 해가 처음은 아니잖아, 선장. 여기 기어 다니는 쓰레기들엔 이제 익숙해졌을 테고, 멀리서도 골칫거리는 냄새 맡을 줄 알게 됐겠지. 이제 뭐 할 거야? 우리 배로 돌아가는 거야?";
			link.l1 = "부상자들을 모으고, 죽은 자들을 수습해서 모두 배에 태워라. 우리가 잃은 이들은 바다의 진정한 자식답게 바다에 보내줄 것이다. 메리와 나는 잠시 남아 있을 테니, 우리 둘만의 시간이 필요하다. 한 가지 더 있다: 메리의 아버지는 프로테스탄트 방식으로 묻어라. 필요하면 알론소도 데려가고. 단, 아무도 묻은 자리를 모르게 해라. 특히 메리는 절대 알면 안 된다. 그녀가 그 기억에 시달리는 일은 없게 해라.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "맞아. 여기 다시 와서 눈물만 흘릴 필요는 없지. 걱정 마 — 우리가 제대로 처리할 테니, 살아 있는 누구도 이 일에 대해 듣지 못할 거야.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "선장 나리, 보고드립니다: 매복 성공, 쓰레기들은 처치 완료, 선장은 확보했습니다.";
			link.l1 = "지금은 정말 빈정거릴 때가 아니야, 그리고 웃기려고 하는 거라면... 별로 좋은 생각 아니거든. 선원들 앞에서 갑판 청소하고 싶진 않을 거 아냐? 아, 걔네들 그거 보면 엄청 좋아할걸... 오늘은 내 인내심 시험하지 않는 게 좋을 거야.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "어... 있잖아, 나 *진짜로* 장교이긴 하고, 그리고...";
			link.l1 = "지금은 그렇지. 오늘은 장교 — 내일은 갑판원, 그 다음날엔 거지가 되는 거야.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "알겠어: " + GetFullName(pchar) + " 여긴 진지한 선장이야. 농담은 끝. 명령은, 나리?";
			link.l1 = "부상자들을 모아서 배에 태워라. 알론소에게 선원들을 데리고 가서 우리 사람들의 시신을 수습하라고 전해. 그들은 바다에 보내줄 거다.\n그리고 메리 아버지는 개신교 전통에 따라 묻어주라고 해. 묘지 위치는 알론소와 그를 돕는 자들만 알도록 해라. 메리는 알 필요 없어. 그녀가 기억에 괴로워하는 일은 없었으면 한다.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "알겠어, 알겠어... 맡겨만 줘. 그리고 걱정 마, 나 입 무겁거든.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "선장님, 나리, 우리가 해냈습니다. 한 놈도 못 도망쳤습니다.";
			link.l1 = "잘했어, " + npchar.name + ", 고마워. 네가 믿음직하다는 거 알고 있었어. 모든 생존자를 모아서 배로 돌아가. 메리랑 나는 좀 더 육지에 남아 있을게.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "죽은 자들의 시신을 어떻게 해야 할까?";
			link.l1 = "우리는 그들을 바다에 보내자. 알론소에게 준비를 맡기라고 전해라.\n그리고 한 가지 더, 메리 아버지는 신교식으로 이 정글 어딘가, 남의 눈에 띄지 않는 곳에 묻으라고 해라. 무덤이 어디 있는지는 아무도 몰라야 한다 — 특히 메리는 안 된다.\n메리를 생각하면, 분명 다시 이곳에 오고 싶어 할 테지만, 그건 메리에게 좋지 않을 거야.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "알겠어. 또 뭐 필요한 거 있어, 나리?";
			link.l1 = "그게 다야, 친구. 가서 쉬고 상처 잘 돌봐.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "지옥 같은 피바다였네... 괜찮아, 선장?";
			link.l1 = "나는 괜찮아... 메리랑 내가 방금 그녀의 아버지를 죽여야만 했다는 사실만 빼면 말이야...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "겉보기엔, 정말 개자식이었던 것 같아...";
			link.l1 = "맞았어, " + npchar.name + ". 그래도 그는 제대로 묻혀야 해 — 신교식으로. 직접 처리해 줬으면 해. 무덤 위치는 아무도 몰라야 해. 특히 메리는 절대 알면 안 돼.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "그녀에게 나쁜 기억을 남기고 싶지 않은 거야?";
			link.l1 = "그리고 쓸데없는 고통은 그만. 다른 사람들은 모두 배로 보내서 회복하게 해. 쓰러진 이들도 배에 실어라 — 메리와 내가 돌아오면 바다에 묻어 주자. 지금은, 우리 둘만 있어야 해.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "애들한테 널 건드리지 말라고 할게.";
			link.l1 = "고마워, " + npchar.name + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
}
