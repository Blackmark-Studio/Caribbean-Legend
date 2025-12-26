void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "슬픈 이야기지, 그렇지 않아?";
				link.l1 = "너 누구야?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "안녕하시오, 선장.";
				link.l1 = "잠깐! 우리 전에 만난 적 있잖아!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "하나. 둘. 셋.";
				link.l1 = "이 연극은 그만두자. 너 누구야?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "넷.";
				link.l1 = "두 명 남았어?";
				link.l1.go = "DiegoDeLanda_Meeting_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "이 무덤이 왜 특별한지 아나? 여기에는 피로 이어진 두 영혼이 누워 있지. 알라메다 가문의 부자(父子)야. 한 명은 죄인들의 손에 쓰러졌고, 다른 한 명은... 흠, 주님의 곁으로 갔지.";
				link.l1 = "돈 페르난도 일기가 나를 여기로 이끌었어.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "레이디 비숍을 봤어? 안타까운 운명이지, 그렇지 않아? 하지만 어쩌면 당연한 결과였을지도 몰라.";
				link.l1 = "엘리자베스를 알아?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "모티머 그림.";
				link.l1 = "당연히 그를 알았겠지?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_ClockTower"))
			{
				dialog.text = ""+GetCharacterName("Hendrik")+" "+GetCharacterName("van Doorn")+".";
				link.l1 = "네 의뢰인?";
				link.l1.go = "DiegoDeLanda_ClockTower_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\n세 명 더. 여섯이 되면 모든 걸 알게 될 거야.";
			link.l1 = " 지금 당장 분명한 대답을 듣지 못하면, 그때는 내가...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\n잘하고 있군, 선장. 내 이름을 알 자격이 있지. 나는 디에고 데 란다다.";
			link.l1 = " 정말 신부 맞소?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "무엇보다도, 나는 예술가야. 하지만 서두르지 말자...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		
		case "DiegoDeLanda_Meeting_Fourth_2":
			dialog.text = "\n맞아요, 선장. 이제 3막이 시작되네.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "아... 일기 말이오. 참으로 놀라운 것이지 — 글이라는 건. 마치... 어둠 속의 길과 같소. 그 길이 계시가 기다리는 곳으로 이끌지. 돈 페르난도는 우리 본당에 자주 들렀소. 특히 지난 1년 동안은 더 그랬지.";
			link.l1 = "이 지역 본당에서 일하시오? 돈 페르난도를 알았소?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "나... 그의 길을 지켜봤어. 그리고 네가 가져간 그 책 말이야. 그게 뭐가 특별한지 알고 있나?";
			link.l1 = "오래돼 보여.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "늙었다고? 아니야. 이건... 깨우침이야. 도네 알라메다 시니어의 성경이지. 그 안의 모든 말씀이 어둠 속의 등불 같아. 가져가. 그리스도의 형제들을 도와주고, 그러면 어쩌면... 이 책이 너를 더 위대한 무언가로 이끌지도 몰라.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "아, 그래. 불쌍한 여자지. 남편이... 그리 친절한 사람은 아니야. 그의 플랜테이션이 바베이도스에서 가장 생산적이라고들 하지. 그리고 가장 잔인하다고도. 거기서 한 달에 노예가 몇 명이나 죽는지 알아? 얼마 전엔 영국에서 온 진짜 의사를 때려죽였어 — 머리도 좋고 재능도 뛰어난 사람이었지. 하지만 그녀의 운명도 별반 다르지 않아, 내 말 믿어.";
			link.l1 = "꽤 잘 알고 있는 것 같군.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "사람들이 고해성사를 하러 내게 옵니다, 선장. 그들은 사랑하는 이에게조차 말하지 못하는 것들을 내게 털어놓지요. 그들의 두려움, 죄악... 그리고 고통까지.";
			link.l1 = "박해가 두렵지 않소? 영국 땅에서 가톨릭 신부로 산다는 건 쉽지 않으니.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "내 두려움은 자네가 방금 저 문 뒤에 두고 온 것에 비하면 아무것도 아니지. 그리고 자네가 그 불쌍한 여자에게서 가져간 그 작은 책... 만약 두려움에 형태가 있다면, 바로 그것과 똑같을 거야.\n"+
		"좋은 하루입니다, 선장님.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "호랑이여, 호랑이여, 불타오르는 그 빛이여\n"+
			"밤의 숲 속에서,\n"+
			"어떤 불멸의 손이나 눈이\n"+
			"그대의 두려운 균형을 누가 만들 수 있을까?\n"+
			"물론 그를 알았지, 선장. 하지만 자네는 알았나?";
			link.l1 = "나는 저보다 더 비극적인 운명을 가진 남자를 본 적이 없어.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "너는 이미 가지고 있지만, 아직 깨닫지 못했지.\n"+
			"그럼 너는 그림을 몰랐던 거야. 네가 그의 해골을 손에 쥐고 있으면서도.";
			link.l1 = "뭐라고?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "죽은 자를 그렇게 대하는 건 기독교답지 않지. 자, 이 작은 사후 지침을 받아라. 내가 너에게 주는 선물이야.\n"+
			"좋은 하루입니다, 선장님.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Башня с часами
		case "DiegoDeLanda_ClockTower_2":
			dialog.text = "재치 있군, 선장. 자네는 그의 의뢰인이었고, 그는 내 의뢰인이었지.\n"+
			"너희 정말 닮았구나.\n"+
			"네가 어떻게 명부에 오르게 됐는지 잊지 않았겠지? 처음엔 윌렘스타드의 영광스러운 도시에 도움을 줬지. 그런데 나중엔 그 도시의 많은 아들들을 피로 물들였잖아.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_3";
		break;
		
		case "DiegoDeLanda_ClockTower_3":
			dialog.text = "하지만 헨드릭은 그걸 해내지 못했지. 까다로운 손님이야, 아주 까다로워. 여기, 예를 들어. 시간 날 때 읽어봐 — 완전히 수수께끼야.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_4";
			// получаем документы Маартена
			ClockTower_AddVisserKey();
			
		break;
		
		case "DiegoDeLanda_ClockTower_4":
			dialog.text = "모든 사람은 하나의 건물이지. 그들을 진짜로 움직이게 하는 게 뭔지 알고 싶어? 지하실을 들여다봐.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_5";
		break;
		
		case "DiegoDeLanda_ClockTower_5":
			dialog.text = "여기.";
			if (CheckAttribute(pchar, "questTemp.ClockTower_GotHint"))
			{
				link.l1 = "지하실 열쇠? 난 이미 거기 다녀왔어.";
				link.l1.go = "DiegoDeLanda_ClockTower_6";
			}
			else
			{
				link.l2 = "네 지하실에 뭐가 있지?";
				link.l2.go = "DiegoDeLanda_ClockTower_7";
			}
		break;
		
		case "DiegoDeLanda_ClockTower_6":
			dialog.text = "\n그렇다면 더 이상 논의할 것이 없군, 선장.";
			link.l1 = "기분 상했나? 네 지하실엔 뭐가 있길래?";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		case "DiegoDeLanda_ClockTower_7":
			dialog.text = "\n우리가 나누는 대화 하나하나가 그곳으로 내려가는 발걸음이오, 선장.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			ClockTower_AddBook_FromDiegoDeLanda(); // получаем ключ от подвала
		break;
		
		//<-- Башня с часами
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "말해 봐... 왜지? 그건 위험하고 어리석은 짓이었어. 대체 무엇이 널 움직이게 하지, 선장? 네 안의 불꽃은 뭐야?";
				link.l1 = "네가 신경 쓸 일 아니야.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "둘째.";
				link.l1 = "지난번엔 수수께끼만 늘어놨지. 또 그럴 거야?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "잠깐, de Landa. 그냥 가져가고 떠나게 둘 수는 없어.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "힌트만 있고, 요란하기만 하며, 행동은 없군\n"+
				"적어도 나는 그렇지. 너는 이미 충분히 싸웠잖아.";
				link.l1 = "그걸 해결할 방법이 있어.";
				link.l1.go = "DiegoDeLanda_Leaving_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "이해가 안 돼. 다른 놈들은 그렇다 쳐. 하지만 너는 아니야. 아직은.";
			link.l1 = "나머지 놈들은?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "예를 들어, 한 명은 정의를 추구하지. 또 다른 놈은... 죽음의 어두운 바다에 집착하고 있어. 사람들은 욕망에 너무 쉽게 자신을 잃어버리지. 그렇지 않나?";
			link.l1 = "이상한 신부군요, 신부님.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "가야겠다.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "물론이지. 네 일은 이제 시작일 뿐이야, 선장.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\n진짜 수수께끼가 내 앞에 있군. 이미 유물 두 개를 모았지... 이런 것들 모으는 걸 좋아하나? 수집가라도 되는 거야?";
			link.l1 = "어떻게 알았지?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "전리품 사냥꾼인가?";
			link.l1 = "내 질문을 다시 묻지. 어떻게 알고 있는 거지?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "스릴을 좇는 자인가?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\n아. 물론이지. 당연하지. 그럼, 선장, 더 이상 붙잡지 않겠네.";
			link.l1 = "잠깐만요, 신부님. 아직 제 질문에 답하지 않으셨습니다.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "아, 선장님. 나는 못 하겠소. 때로는 답이 무지보다 더 상처가 되오. 평안히 가시오. 그리고 당신의 전리품... 그 수집품들도 잘 챙기시오. 앞으로의 여정에 쓸모가 있을지도 모르니.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "자, 이제 오시오, 선장. 흥미롭지 않소? 재미없소? 전리품은 충분하오?\n"+
			"그게 바로 당신의 불꽃이오, 선장. 다음에 무슨 일이 일어날지 궁금해하지. 아름다운 배와 신기한 장신구를 사랑하잖소.\n"+
			"그냥 전부 모으지 않을 수가 없지.\n"+
			"\n"+
			"지금 당장 나를 쏴도 돼.";
			link.l1 = "뭐?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "가 봐라. 하지만 그러면 모든 걸 알 수 없고, 전리품도 전부 얻지 못할 거다. 그래도 배는 전부 얻게 되겠지...\n"+
			"좋은 하루입니다, 선장님.";
			link.l1 = "(놔둬)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(쏴라)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_Fourth_2": // Четвёртое прощание
			dialog.text = "\n이미 늦었소, 선장. 날 쏠 기회가 있었지. 그것도 대단한 기회였는데! 셋을 세자: 하나, 둘, 셋... 그리고 아무 일도 없었지. 하지만 걱정 마. 여섯이 되면 제대로 보여주지. 이제 얼마 안 남았어.\n"+
			"좋은 하루입니다, 선장님.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 