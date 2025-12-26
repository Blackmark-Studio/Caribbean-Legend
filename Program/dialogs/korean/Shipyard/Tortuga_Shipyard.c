// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했었지...","이 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없어.","질문이 왜 이렇게 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "가이우스 마르셰이를 찾고 있어. 마지막으로 들은 소식은 그가 자기 갤리온 '산타 마르가리타'를 당신에게 수리 맡기려고 정박시켰다는 거였어...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "자기 갈레온이 있다고? 허허, 그거 참 웃기는 농담이군, 선장. 가이우스 마르셰는 반쯤 죽은 슬루프밖에 없었지... 사략선이 되기로 결심한 뒤에야 전리품으로 갈레온을 하나 잡았거든. 운 좋은 놈이지, 첫 번째 습격에 그런 전리품이라니\n내가 그 배에 좋은 값을 제안했는데도 거절하더군, 믿어지나? 대신 자기 초라한 슬루프를 얼마 안 되는 돈에 팔고, 그걸로 갈레온을 수리했지! 새 돛, 새 도장, 새 이름까지 붙였는데, 보통 그건 별로 좋은 징조가 아니야\n물론 그 이름이 너무 가톨릭 냄새가 났지만, 내 딸 이름도 마르가리타라서 결국 괜찮다고 생각했지... 그는 이제 폭력은 지긋지긋하다며 상인이 되겠다고 했어. 그리고 운도 따랐지...";
			link.l1 = "상업이라면 아마 한가하겠지. 하지만 교황파 갤리온이 슬루프한테 쉽게 잡히진 않잖아. 그리고 그 자의 배, 지금은 이름이 뭐지?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'감탄스러워'... 그럴 만도 하지! 새 갤리온을 마치 신부라도 쫓는 것처럼 여기저기 뛰어다니며, 감탄을 멈추질 못하더군.";
			link.l1 = "알겠소. 가이우스가 지금 토르투가에 있소?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "아니. 그는 새 배를 타고 출항했고 아직 토르투가로 돌아오지 않았어. 어디로 갔는지도 모르니, 이 일은 도와줄 수 없어.";
			link.l1 = "정말 성가시군... 그가 정말 필요해. 그의 '훌륭한' 배를 위해 한잔 해야겠어. 어쨌든, 정보 고마워.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "오, 문제없소. 또 들르시오, 선장. 그리고 잊지 마시오, 수리가 필요하면 언제든 당신 배를 위한 정박 자리가 여기 있소!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
