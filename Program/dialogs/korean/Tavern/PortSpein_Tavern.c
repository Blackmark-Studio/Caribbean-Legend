// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안만 해도, 이 질문을 벌써 세 번째 꺼내는군...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "자네 요새에서 결핵이 창궐하고 있다는 소문을 들었네. 그 역병이 마을까지 퍼질 거라 생각하나?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "요새 사령관에 대해 뭐 아는 거 있어?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말해 봐, 'Juan'이라는 이름이 너한테 의미가 있나?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "이봐, 1654년 4월에 미겔 디초소 선장이 지휘하는 프리깃이 너희 항구에 정박했었지. 그런데 그 뒤로 그가 사라졌어. 혹시 그 일에 대해 아는 게 있나?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "말해 봐, "+npchar.name+", 이 하비에르 카스티요가 누구지?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "하비에르에게 영향을 줄 수 있는 남자에 대한 이야기로 다시 돌아가자.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта

		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "사령관이 위험 없다고 하더군. 너무 궁금해하는 놈들은 결국 감옥에 갇히게 되지. 나는 그런 놈 아니야, 미안하지만.";
			link.l1 = "그래? 소문 듣기 싫어하는 주점 주인이라니, 참 신기하군! 혹시 페소 소리가 다시 호기심을 자극하지 않을까?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "은화가 유혹적이긴 하지, 물론. 하지만 내 목숨이 더 소중해. 혹시 다른 얘기를 해줄까, 나리? 사실 난 언제든 얘기하는 거 좋아하니, 그냥 말만 걸어!";
			link.l1 = "그래서 일이 이렇게 풀리는 거군... 좋아, 이 주머니엔 3,000피스의 에잇이 들어 있으니, 우리 날씨에 대해 한바탕 수다나 떨어보자고, 어때?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "오, 집요하구만, 나리. 이 대화는 없었던 일로 하시오. (속삭이며) 나는 벌써 1년째 계속 듣고 있소, 우리 감옥에서 사람들이 시름시름 앓다 죽어나간다는 소문을. 폐병으로 죽는다고들 하오. 누구는 관헌을, 누구는 신을, 또 누구는 악마를 탓하지만, 대부분은 운이 나빠서 그렇다고 하지. 이 빌어먹을 병이 사람 목숨을 순식간에 앗아가오. 멀쩡하던 사람도 거기 들어가면 일주일, 이주 만에 그대로 죽어버리니...";
			link.l1 = "이런 젠장... 벌써 한 해가 지났다니? 그런데 아무도 나서서 뭔가 해보려는 놈이 없었다고?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "누가 신경이나 쓰겠어, 나리? 죄수 따위 누가 신경 써? 사회의 쓰레기라지, 비단옷 입은 대인네들이 하는 말이지. 지하 감옥에서 일하던 의사가 있었어. 불쌍한 영혼들을 치료하려고 했지. 오래 못 버텼어; 병이 그 사람도 데려간 모양이야.\n지금은 사령관이 아무도 들이지 않고, 우리 관리들은 그런 일에 관심도 없어. 특히 감옥 식량값을 덜 낼 수 있을 때는 더더욱 그렇지.";
			link.l1 = "흥미로운데, 그런데 이 병에 대해 뭐가 그리 두려워서, 이렇게 안전한 벽 안에 갇혀 있으면서도 고해성사실의 수녀들처럼 속삭이고 있는 거지?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "말하기 좀 어렵지만, 여기 한 녀석이 있었지. 밀수로 잡혀 들어가서 동료들이 몸값을 치를 때까지 반 년쯤 감옥에 갇혀 있었어. 뭐, 알잖아—필요한 놈한테는 금을 저울질해서 내주고, 시키는 대로 돈을 내고, 결국 그 녀석이 풀려났지. 근데 그 뒤로는 완전히 미쳐버렸어.";
			link.l1 = "선창의 쥐보다 더 미쳤다고?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "그런 것 같소. 그때부터 그는 동료들에게 아무 쓸모도 없었지. 하루 종일 여기서 술만 마시며 죽어가고 있었소. 뭔가 머릿속에서 지워버리고 싶은 게 있었던 모양이오. 술에 취할 때마다, 사람을 조용히 데려가는 그 '소모증' 이야기를 하곤 했지\n그게 그의 정확한 말이었소. 그의 말로는, '소모증'이 남자에게 일어날 수 있는 최악의 일이라고 하더군.";
			link.l1 = "주정뱅이의 헛소리다. 그래서 뭐 어쩌라고?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "별일 없었지. 그냥 술기운 좀 얻더니 점점 말이 많아지더라고. 그러다 갑자기 누가 목을 그어버리고 시궁창에 내던졌지... 누가 그랬든, 왜 그랬든 나한텐 다 똑같아.";
				link.l1 = "사령관에 대해 뭐라고 할 수 있지?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "별일 없지, 그냥 그 녀석이 용기가 붙어서 점점 말이 많아지더니, 어느 순간 누가 목을 그어 하수구에 던져버렸다는 거야... 누가 왜 그랬는지는 나한텐 다 똑같아. (목소리를 높이며) 그래, 이 근처 만이랑 암초는 정말 위험하다고, 나리. 대앤틸리스 제도에서 폭풍이 몰아치면 조심해야 해, 바람을 놓치면 끝장이지! 푹 쉬고 가시오, 나리, 들러줘서 고맙네!";
				link.l1 = "폭풍... 그렇지. 고맙다, 너도.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "그 사람에 대해 뭐라 할 수 있겠나? 그는 대령이고, 몇 해 전에 유럽에서 이 직책을 받고 왔지. 구세계에서 뭔가 수상한 일로 강등당했다는 소문이 있었어. 그게 사실인지는 모르겠지만, 처음엔 그런 얘기가 돌았지. 하지만 소문 없는 사람이 어디 있겠나, 안 그래?";
			link.l1 = "더러운 짓거리라니... 흥미로운데. 또 뭐 있나?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "글쎄, 뭐라고 해야 할까... 대령은 자기 안전에 몹시 신경 쓰는 사람 같아. 물론 이 근방은 해적, 도적, 인디언, 그리고 온갖 잡놈들 때문에 위험하지. 하지만 코만단 나리는 경호원 몇 명 없이는 절대 집을 나서지 않아\n저택도 이 도시에 있는데, 완전히 작은 요새로 만들어 놨어. 하인들도 무장 잘했고, 창문도 단단히 잠가 두지.";
			link.l1 = "하지만 낮에는 감옥에서 근무하지 않나?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "그래, 하지만 그 저택은 사실상 매복이나 침입을 기다리고 있는 셈이지. 아무튼, 코만단 나리께서는 거기로 자주 돌아가지 않는다고 하더군 — 진짜 요새가 더 취향이시라네, 허허.";
			link.l1 = "고마워, 정말 큰 도움이 됐어. 나중에 보자, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "후안? 누구 말이야? 여기 그런 사람 많아, 보통은 성도 있지... 아니면 최소한 별명이라도...";
			link.l1 = "나 방금 생각했는데... 혹시 그의 별명이 '소모'라는 거 들어본 적 있어?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "오, 맙소사, 또 그 얘기 하는 거야! 아니, 다행히도 못 들었어. 맹세해! 이제, 화제 좀 바꾸자. 제발!";
			link.l1 = "알았어, 알았다고, 심장마비나 일으키지 마...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "하비에르는 카드 도박꾼이자 사기꾼, 협잡꾼이지. 항상 선술집 근처를 맴돌면서 몇 페소라도 뜯어낼 사람을 찾고 있어.";
			link.l1 = "그래서, 다른 수상한 거래에서는 눈에 띄지 않았단 말이지? 혹시 적이라도 있나?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "글쎄, 그 자는 목을 비틀고 싶어 하는 놈들이 친구보다 훨씬 많다고만 해두지. 하지만 정말로 그 자에게 영향력을 행사할 수 있는 사람의 이름이 필요하다면, 천 페소는 내야 해. 돈을 내면 전부 다 말해주지.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "좋아, 돈 가져가, 이 늙은 갈취꾼아.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "이 이야기는 나중에 다시 하자. 지금은 그 돈이 없어.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "선장님, 천 페소 가져오셨습니까?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "가졌다. 가져가, 이 늙은 갈취꾼아.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "젠장. 곧 돌아올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "이제야 제대로 된 얘기군. 자, 하비에르는 단순히 도박빚만 있는 게 아니야. 한때 골동품 장사에 손을 대기로 했었는데, 예상하다시피 그 끝은 좋지 않았지. 처음엔 제법 잘 풀리는 듯했지만, 어느 날 희귀한 물건을 손에 넣을 기회가 생겼거든\n그 생각에 완전히 불타올라서 돈을 구하러 온갖 전당포를 다 돌아다녔지. 당연히 아무도 한 푼도 빌려주지 않았어. 그러다 골동품에 미친 또 다른 놈을 찾아내서, 그놈에게서 무려 십오만 페소를 빌렸지. 그 다음은, 뭐, 너도 짐작할 수 있을 거야\n결국 사기를 당했고, 지금 그 빚이 목에 돌덩이처럼 매달려 있지. 겨우 푼돈만 갚았고, 빚쟁이가 사람들까지 고용해서 겁을 줘도 나머지는 갚을 생각이 없어 보여\n그가 돈을 빌린 사람은 펠리페 알라르콘이야. 그의 집은 은행 맞은편에 있는데, 입구에 기둥이 있는 웅장한 저택이라 금방 알아볼 수 있을 거야.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "그 사람 기억나. 내 선술집에 자주 들렀지만 말이 별로 없었지. 럼 몇 잔 마시고, 손님 몇몇과 속삭이다가 그냥 갔어. 아주 침울하고 진지했지, 그 프리깃에 탄 사람들 모두가 그랬어. 칼을 항상 뽑을 준비가 된 위험해 보이는 용병들이었지\n프리깃에 보물이 가득하다는 소문이 돌았지만, 난 그런 얘기 안 믿어. 값진 화물은 호위 없이 한 척 배에 실어 나르지 않거든. 여기서 하루 머물다가 떠났어. 유럽으로 갔다더군. 내가 아는 건 그게 다야.";
			link.l1 = "알겠소. 뭐, 그나마 다행이군...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
