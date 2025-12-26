// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 해봤잖아 "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","봐라, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 나를 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에는 관심이 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// НСО пошив мундира Xenon-->
		case "Tailor":
			dialog.text = "예, 잘 알아들었으니 소리칠 필요 없습니다. 하지만 이미 말씀드렸듯이, 이번에는 평소보다 서신과 우편물이 훨씬 많았습니다. 걱정 마십시오, 당신의 자료는 분실되지 않을 것이며 다음 배달선으로 전달될 것입니다.";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_02";
			Lai_SetPlayerType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "글쎄요, 분명히 더 중요한 소포들이 있었겠지요. 그리고 배에 과적할 수도 없으니 말입니다. 하지만 우편이 어떻게 배분되는지는 저도 잘 모릅니다. 부디 진정하시고 흥분하지 마십시오. 다시 말씀드리지만, 당신의 모든 물품은 온전하게 도착할 것이니, 다만 조금 늦을 뿐입니다.";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
		break;
		
		case "Tailor_03":
			npchar.dialog.currentnode = "First time";
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_04";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		// <-- пошив мундира
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
