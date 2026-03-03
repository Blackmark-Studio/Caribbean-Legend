// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많으니, 네가 나를 방해하고 있구나. "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"드릴 말씀이 없습니다, 죄송합니다.","나중에 물어볼게. 용서해 주십시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "신부님, 마리사 칼데라를 찾고 있습니다. 그녀가 신앙심이 깊고 교회에 자주 다녔다고 들었습니다. 어디서 그녀를 찾을 수 있는지 알려주실 수 있습니까?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "마리사는 우리 교회에서 가장 신실한 신도 중 한 명이었고, 진정으로 교회의 영혼과도 같았소. 그녀의 부재는 신도들에게 큰 상실이오. 무엇이 그녀를 사라지게 했는지는 모르겠지만, 분명히 말할 수 있소. 그녀는 부당한 시련을 겪었으며, 그 뒤에는 악마와 그의 하수인들이 개입했을 것이오\n가끔 그녀가 마을에서 목격되었다는 소문을 듣긴 하지만, 그 이상은 아무것도 없소. 우리가 할 수 있는 일은 오직 주님의 뜻을 믿고 언젠가 그녀가 돌아와 다시 교회 지붕 아래에서 위안을 찾기를 바라는 것뿐이오.";
			link.l1 = "혹시 그녀에 대해 더 잘 아는 사람을 알고 있소?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("아들아","딸아")+", 말해 보시오, 왜 마리사를 찾는 거요? 가끔씩 사람들이 그녀를 찾아오는데, 그들 모두가 의로운 사람처럼 보이지는 않소. 세상에는 유혹이 가득하고, 그녀를 쫓는 자들 모두가 선한 의도로 그러는 것은 아니오. 내가 한마디라도 하기 전에, 그대가 그녀나 그녀와 관련된 사람들에게 해를 끼칠 생각이 없다는 걸 확실히 해야 하오.";
			link.l1 = "신부님, 염려하시는 건 알지만, 분명히 말씀드리죠: 저는 나쁜 의도가 없습니다. 그저 그녀에게 너무 오래 전달되지 못한 편지를 전하고 싶을 뿐입니다. 혹시 모르지요—그녀에게 중요한 내용이 들어 있을지도요. 여기, 한번 보시죠.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;

		case "LFD_Church_1_3":
			dialog.text = "그래, 이 편지는 네 손에 닿기까지 수많은 폭풍을 견뎌낸 것 같구나. 그 안에 무엇이 들어 있는지, 또 읽힌 뒤 어떤 결과가 따를지는 아무도 알 수 없지... 하지만 네가 이 편지를 정당한 주인에게 돌려주는 것은 매우 고결한 행동이네, 선장. 만약 지금 마리사가 어디 있는지 아는 사람이 있다면, 그녀가 유일하게 신뢰했을지도 모를 친구 돌로레스 몬호뿐일 것이네\n그녀의 집은 항만청 왼편에 있네. 이 편지가 마리사에게 더 이상의 고통을 주지 않기를 바라네. 그녀는 이미 충분히 많은 고통을 겪었으니.";
			link.l1 = "감사합니다, 신부님. 주님께서 신부님을 지켜주시길 바랍니다.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;

		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
