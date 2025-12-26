// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많으니 네가 나를 방해하고 있군, "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"할 말이 없소, 미안하오.","나중에 물어보겠소. 용서하시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "신부님, 토마스 모리슨의 딸에 대해 말씀드리고 싶습니다.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "신부님, 토마스가 회개의 길을 받아들이겠다고 전해 달라고 했습니다. 선행에 헌신할 것이며, 어떤 대가를 치르더라도 본당에 새 종을 마련하겠다고 했습니다.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "말해 보아라, 내 아이야. 듣고 있다.";
			link.l1 = "나는 네가 집시가 그 소녀를 돕는 걸 반대하는 거 안다. 하지만 어떻게 아버지에게 딸을 구할 수 있는 작은 가능성마저 거부하라고 강요할 수 있겠나? 그녀의 방식이 의심스러울 수는 있지만, 도움이 될 만한 지식을 가지고 있지.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "아들아, 소녀를 치유하실 수 있는 분은 오직 주님뿐이다. 그분의 계획을 믿는 신앙이 시련을 이겨내게 해 준다. 토마스가 정성껏 기도하고, 하나님의 말씀을 따르며, 교회에 아낌없이 헌금한다면, 주님께서 그의 기도를 들으시고 자비를 베푸실 것이다.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(믿을 만한) 하지만 그대도 인정해야 하오, 주님께서는 사람을 통해 일하시지. 만약 그 집시가 그분의 뜻을 이루는 도구라면 어찌하겠소? 그분의 계획이 너무도 심오하여 우리 같은 필멸자는 이해할 수 없다면? 주님의 뜻은 오묘하니, 그렇지 않소?";
				link.l1.go = "dwh_pastor_VD_1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l1 = "아버지로 하여금 딸이 시들어가는 모습을 지켜보게 하면서, 구할 기회조차 주지 않는 것이 자비로운 일인가?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				Notification_Perk(false, "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "현명한 말씀입니다, 선장님. 하지만 여전히, 이단이 우리 신도들의 마음에 스며들어 가장 독실한 신자의 신앙을 흔드는 것은 허락할 수 없습니다.";
			link.l1 = "그가 딸을 잃는 것보다 더 그의 신앙을 흔드는 일은 없을 것이오. 하지만 그에게 죄악으로 여겨지는 방법까지 모두 쓰게 허락한다면, 그의 신앙은 약해지기는커녕 오히려 더 강해질 것이오.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "하지만... 그러면 다른 신도들에게 어떤 본보기가 되겠소?";
			link.l1 = "교회가 무턱대고 벌을 내리는 것이 아니라, 참된 회개로 이끌고 인도한다는 본보기지. 성경에서도 진심 어린 회개와 선행이 죄를 속죄할 수 있다고 가르치지 않는가? 교회에 대한 넉넉한 헌금이 구원의 첫걸음이 될 수 있네.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "어쩌면 선장 말이 맞을지도 모르겠소. 나는 토마스에게 이번 기회를 주겠소. 하지만 명심하시오—그가 올바른 길에서 벗어나 믿음을 잃는다면, 그 책임은 선장도 함께 져야 하오! 기부에 관해서라면—교회는 부를 필요로 하지 않소, 우리는 필요한 만큼 가지고 있소. 다만... 스페인 놈들의 습격 때 종이 망가졌지 뭐요...\n";
			link.l1 = "당신의 말씀을 토마스에게 전하겠습니다. 시간 내주셔서 감사합니다, 신부님. 주님의 가호가 함께하시길.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "이것은 무정함이 아니라 믿음입니다, 선장님. 우리는 그 소녀의 운명을 버리는 것이 아니라 주님의 손에 맡기는 것입니다. 토마스가 기도하고, 믿으며, 겸손히 기다린다면, 분명 주님께서 우리의 기도를 들으시고 그녀를 치유해 주실 것입니다.";
			link.l1 = "있잖아, 총독을 포함한 이 섬의 귀족들조차 집시의 도움을 받았어. 그런데도 그들은 파문당하지 않았지. 그런데 왜 토마스에게만 그렇게 엄격하게 구는 거야?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "물론 알고 있지, 아들아. 하지만 그들은 아직 주님의 참된 빛을 받지 못한 길 잃은 영혼들이란다. 토마스는 우리 신도들의 기둥이며, 가장 훌륭한 이들 중 하나지. 악이 그의 신앙을 좀먹게 두는 것은 교회 전체를 위태롭게 하는 일이니, 그런 중대한 죄를 나는 결코 용납할 수 없다.";
			link.l1 = "그럼 아주 작은 기회조차 주지 않겠다는 건가? 그게 정말 정의로운 일이오?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "네가 구원이라 부르는 것이 오히려 파멸로 이끌 수도 있지. 내가 직접 겪어 봤으니 하는 말이야. 한때, 내 의지와는 달리 저 여자 같은 치유사가 내 조카를 치료한 적이 있었지. 어린 소녀였는데, 고통 속에서 죽었어. 그리고 그 의식들 때문에 그녀의 영혼이 저주받았는지는 오직 주님만이 아시지. 나를 설득하려 들지 마라—헛수고일 뿐이니.";
			link.l1 = "좋소. 그게 마지막 대답이라면 더 이상 말하지 않겠소. 주님께서 그대를 지켜주시길.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			LAi_CharacterEnableDialog(sld);
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "훌륭하구나, 아들아. 새 종은 그의 주님과 교회에 대한 헌신의 상징이 될 것이다. 필요한 일을 하게 하되, 반드시 상기시켜라—전능하신 분의 눈은 모든 행위를 지켜보고 계시며, 그분의 뜻을 벗어나는 것은 아무것도 없다는 것을.";
			link.l1 = "그러하옵니다, 신부님. 안녕히 계십시오.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
			LAi_RemoveLoginTime(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
