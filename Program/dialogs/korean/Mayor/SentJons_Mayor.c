// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 몸인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내가 마음을 바꿨소...","지금은 아니오. 때와 장소가 맞지 않소\n"),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 있다가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "각하, 머큐리호의 실종에 관한 정보를 제가 가지고 있음을 알려드리고자 합니다.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "정보요? 또 무슨 일에 관해서입니까?";
			link.l1 = "브리건틴입니다, 각하. 우편물을 운송하고 있습니다. 매우 중요한 문서 등입니다. 조사가 있다는 소식을 들었고, 당연히 영국 왕실의 충성스러운 친구로서 도와드리고 싶습니다.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "훌륭하군요! 코트니 바로넷께서 당신을 맞이하게 되어 매우 기뻐하실 것입니다! 즉시 만남을 주선하겠습니다.";
			link.l1 = "감사합니다, 나리. 지금 급히 처리해야 할 일이 있으니, 이 일이 신속히 진행되면 감사하겠습니다.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "걱정하지 마시오, 시간은 충분히 있을 것이오. 경비병들! 저자를 잡아라!";
			link.l1 = "감사... 잠깐, 뭐라고? 이게 농담이오?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
