// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안만 해도, 이 질문을 세 번째로 꺼내는군...","질문이 더 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 이번이 정말 세 번째야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "나는 전직 형리였던 레이먼드 베이커를 찾고 있어. 그가 살아 있는지, 그리고 어디서 찾을 수 있는지 아나?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "나는 Jones 씨를 찾고 있어. 내 수색을 도와줄 수 있겠나, 친구?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "이봐, 이 마을에 연금술사가 왔는지 들었나, 의사 말이야? 이탈리아 사람이고, 서른 살쯤 된 남자인데 이름이 지노 그비네일리야. 그에 대해 뭐 들은 거 없어?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "우리 뚱보 친구가 이제는 폭스 대령보다 더 유명해졌지! 그 친구 아직 살아 있어, 불쌍하게도. 하지만 지금은 도시에 없어. 너 같은 무서운 사람들이 관심을 가진다는 걸 레이몬드가 알자마자, 허겁지겁 자기 오두막을 헐값에 팔아치우고 바람처럼 사라졌거든.";
			link.l1 = "바람과 함께 사라졌다고? 어디로?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "오, 누가 알겠어. 그는 지나가던 첫 번째 배에 배의 의사로 일하러 갔지. 그런데 그 배가 오늘 막 돌아왔는데도 아직 아무도 베이커가 상륙하는 걸 못 봤어.";
			link.l1 = "선장을 어떻게 찾을 수 있지?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "왜 그를 찾으려고 하는 거지? 분명 평소처럼 선실에서 이미 술에 취해 있을 거야. 그 구멍 난 양동이 이름이 '캘로우 매기'라지. 선장이 그러하니, 배 이름도 그런 거지...";
			link.l1 = "도와줘서 고마워, 친구!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "존스 씨? 농담하지 마, 친구. 이 섬에 존스라는 놈이 얼마나 많은지 알아? 좀 더 구체적으로 말해 줘야겠어.";
			link.l1 = "그에게는 누나 몰리가 있어. 사람들이 말하길, 그녀는 놀랄 만큼 아름답대.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "아니. 그런 건 전혀 생각나지 않아. 미안하다, 친구...";
			link.l1 = "좋아, 모르면 모르는 거지...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "아니, 못 들었어. 그리고 우리 마을에는 연금술사가 한 명뿐이야, 약사 존 머독. 그 사람 약은 정말 대단해 - 어떤 병도 낫게 해주지.";
			link.l1 = "저자가 저 약을 직접 만든다고 생각해?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "좋은 질문이군. 나도 가끔씩 그런 생각을 하지. 존은 약병이나 약초, 가루의 감식가처럼 전혀 안 보여. 오히려 전직 군인이나 용병에 더 가까워... 그게 진실에 더 가깝지.";
			link.l1 = "글쎄, 그 남자는 너무 유능한 것 같군...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "어쩌면 그럴지도 몰라. 하지만 내가 확실히 아는 게 하나 있어: 누군가 그의 2층에 살고 있다는 거야. 창문은 항상 가려져 있고, 존이 아래층에 있을 때도 유리병이나 약병이 부딪히는 소리가 들려. 끓는 약초 냄새도 나고, 밤에도 불이 꺼지지 않아. 그래서 나는 그 방에 사는 사람이 존의 약을 만들어 파는 장본인이라고 의심하는 거지.";
			link.l1 = "흠. 흥미로운 지적이군. 고마워, 친구!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
