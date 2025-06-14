// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";

		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avez-vous entendu ? On dit que la fille de Thomas Morrison est clouée au lit depuis six mois. Les médecins sont totalement impuissants face à sa maladie. La seule qui pourrait lui venir en aide est une gitane célèbre pour ses potions qui remettent sur pied même les plus malades. Mais elle a catégoriquement refusé de faire quoi que ce soit pour la pauvre enfant.";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avant-hier, il y a eu une tentative d'assassinat audacieuse contre le chef de l'autorité portuaire ! L'assassin l'attendait à la sortie du bureau, mais il a réussi à appeler à l'aide. Un mousquetaire est arrivé à temps et a blessé l'agresseur, mais le criminel a réussi à s'échapper de la ville\nOn dit que le chef du port offre une généreuse récompense pour sa tête ! Jusqu'à présent, aucune âme brave ne s'est manifestée.";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avez-vous entendu la nouvelle?! C'est un scandale sanglant! Pas une goutte de rhum ou de vin dans la taverne - comment trouver du réconfort sous cette chaleur maudite? Le tavernier nous abreuve de promesses creuses depuis une semaine que les boissons couleront à nouveau, mais toujours rien! Devons-nous donc assécher nos gosiers jusqu'au Jugement Dernier?";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Les rumeurs du port racontent que Julie d'Armagnac, la nièce du gouverneur, n'est plus que l'ombre d'elle-même. Autrefois rayonnante et pleine de vie, elle erre maintenant dans les rues, le visage marqué par une tristesse indéniable. Les habitants chuchotent et s'interrogent sur ce qui a pu lui arriver, mais personne n'en connaît la vérité. Peut-être qu'un gredin lui a brisé le cœur ?"+GetSexPhrase(" C'était peut-être vous, capitaine ?","")+"";
			link.l1 = ""+GetSexPhrase("J’en doute. ","")+"Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Le bruit court que le pêcheur Pierre Carno a disparu sans laisser de trace. Il y a deux aubes, il a pris la mer et depuis, pas le moindre signe de lui. Sa femme, Lea, est folle d'inquiétude. Jour et nuit, elle monte la garde sur le quai, les youux rivés sur les eaux infinies, priant pour apercevoir la voile de son bien-aimé.";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitaine, avez-vous entendu ? Une nouvelle serveuse travaille dans notre taverne. On dit que c'est une vraie beauté. Des hommes de partout accouraient juste pour l'apercevoir. Mais il y a trois jours, elle ne s'est pas présentée au travail, ce qui a grandement contrarié le tavernier qui réalisait d'énormes profits depuis son arrivée. On dit qu'il est même prêt à payer quiconque pourra la retrouver.​";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("towngirl", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix

		string posrep1, posrep2, answ1, answ2, answ3, answ4;

		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Voilà les nouvelles...", " Peut-être que cela vous amusera.");
			posrep2 = " Et vous, capitaine, avez-vous des nouvelles pour notre colonie ?";

			answ1 = RandPhraseSimple(RandSwear() + "Tu racontes des choses intéressantes, " + GetFullName(NPChar) + ".", "Alors raconte-moi encore...");
			answ2 = RandPhraseSimple(RandSwear() + "C'est très intéressant ! Voilà ce que je voulais encore" + GetSexPhrase("", "e") + " te demander...", "Encore une question.");
			answ3 = RandPhraseSimple("Il arrive tant de choses dans le monde. Désolé, mais je n’ai aucune nouvelle.", "Je suis un peu pressé(e), on en reparlera une autre fois.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Il ne se passe presque jamais rien ici. Mais dès qu’il se passe quelque chose d’inhabituel, tout le monde en parle.";
			posrep2 = " Donc pas de nouvelles. Mais peut-être que le " + GetAddress_Form(NPChar, false) + " capitaine sait quelque chose ?";

			answ1 = RandPhraseSimple("Alors raconte-moi plutôt autre chose...", RandSwear() + "Tu ne sais rien ! Bon, voilà ce que je voulais encore" + GetSexPhrase("", "e") + " te demander...");
			answ2 = RandPhraseSimple("Tu dis ne rien savoir, alors dis-moi...", "Tu ne m’as pas beaucoup aidé" + NPCharSexPhrase(NPChar, "", "e") + ", mais peut-être sais-tu autre chose ?");
			answ3 = RandPhraseSimple("Je ne pense pas savoir quoi que ce soit qui puisse vous intéresser.", "Je serais ravi(e) de vous raconter quelque chose, mais une autre fois.");
			answ4 = "";
		}

		Dialog.Text = NPCStringReactionRepeat(
			srum,
			srum + posrep1,
			srum + posrep2,
			RandPhraseSimple("Malheureusement, je ne sais rien d’autre, permettez-moi de partir.", "Vous me fatiguez avec vos questions, pardonnez-moi, mais j’ai à faire."),
			"block", 1, npchar, Dialog.CurrentNode
		);

		link.l1 = HeroStringReactionRepeat(answ1, answ2, answ3, answ4, npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Merci, je dois prendre congé.", "Portez-vous bien.");
		link.l2.go = "exit";
		break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";

		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avez-vous entendu ? On dit que la fille de Thomas Morrison est clouée au lit depuis six mois. Les médecins sont totalement impuissants face à sa maladie. La seule qui pourrait lui venir en aide est une gitane célèbre pour ses potions qui remettent sur pied même les plus malades. Mais elle a catégoriquement refusé de faire quoi que ce soit pour la pauvre enfant.";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//--> Тёмные воды исцеления
		
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avant-hier, il y a eu une tentative d'assassinat audacieuse contre le chef de l'autorité portuaire ! L'assassin l'attendait à la sortie du bureau, mais il a réussi à appeler à l'aide. Un mousquetaire est arrivé à temps et a blessé l'agresseur, mais le criminel a réussi à s'échapper de la ville\nOn dit que le chef du port offre une généreuse récompense pour sa tête ! Jusqu'à présent, aucune âme brave ne s'est manifestée. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avez-vous entendu la nouvelle?! C'est un scandale sanglant! Pas une goutte de rhum ou de vin dans la taverne - comment trouver du réconfort sous cette chaleur maudite? Le tavernier nous abreuve de promesses creuses depuis une semaine que les boissons couleront à nouveau, mais toujours rien! Devons-nous donc assécher nos gosiers jusqu'au Jugement Dernier?";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Les rumeurs du port racontent que Julie d'Armagnac, la nièce du gouverneur, n'est plus que l'ombre d'elle-même. Autrefois rayonnante et pleine de vie, elle erre maintenant dans les rues, le visage marqué par une tristesse indéniable. Les habitants chuchotent et s'interrogent sur ce qui a pu lui arriver, mais personne n'en connaît la vérité. Peut-être qu'un gredin lui a brisé le cœur ?"+GetSexPhrase(" C'était peut-être vous, capitaine ?","")+"";
			link.l1 = ""+GetSexPhrase("J’en doute. ","")+"Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Le bruit court que le pêcheur Pierre Carno a disparu sans laisser de trace. Il y a deux aubes, il a pris la mer et depuis, pas le moindre signe de lui. Sa femme, Lea, est folle d'inquiétude. Jour et nuit, elle monte la garde sur le quai, les youux rivés sur les eaux infinies, priant pour apercevoir la voile de son bien-aimé.";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        } 
		//<--  В плену великого улова andre39966
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitaine, avez-vous entendu ? Une nouvelle serveuse travaille dans notre taverne. On dit que c'est une vraie beauté. Des hommes de partout accouraient juste pour l'apercevoir. Mais il y a trois jours, elle ne s'est pas présentée au travail, ce qui a grandement contrarié le tavernier qui réalisait d'énormes profits depuis son arrivée. On dit qu'il est même prêt à payer quiconque pourra la retrouver.​";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("townman", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix

		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Voilà tout...", " Cela pourrait vous intéresser.");
			posrep2 = " Dites-moi, capitaine, avez-vous des nouvelles pour notre colonie ?";
			
			answ1 = RandPhraseSimple(RandSwear() + "C’est très intéressant, " + GetFullName(NPChar) + ".", "Alors raconte-moi...");
			answ2 = RandPhraseSimple(RandSwear() + "Intéressant ! J’ai encore une question à poser...", "Encore une question.");
			answ3 = RandPhraseSimple("Eh bien, tout peut arriver dans ce monde. Désolé, mais je n’ai rien de spécial à vous raconter.", "Je suis assez pressé, alors une autre fois peut-être.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Il ne se passe pas grand-chose ici. Donc quand quelque chose arrive, tout le monde en parle.";
			posrep2 = " Rien d’intéressant. Peut-être que " + GetAddress_Form(NPChar) + " capitaine sait quelque chose ?";
			
			answ1 = RandPhraseSimple("Alors parle-moi d’autre chose...", RandSwear() + "Tu ne sais rien ! Très bien, changeons de sujet...");
			answ2 = RandPhraseSimple("Peu importe, dis-moi simplement autre chose...", "Oui, tu ne m’as pas beaucoup aidé, as-tu autre chose à me dire ?");
			answ3 = RandPhraseSimple("Je doute d’avoir quelque chose qui pourrait vous intéresser.", "Ce serait avec plaisir, mais parlons-en une autre fois.");
			answ4 = "";
		}

		Dialog.Text = NPCStringReactionRepeat(
			srum,
			srum + posrep1,
			srum + posrep2,
			RandPhraseSimple("Hélas, je n’ai rien de plus à vous dire, laissez-moi passer.", "Assez de questions, excusez-moi, j’ai d’autres choses à faire."),
			"block", 1, npchar, Dialog.CurrentNode
		);

		link.l1 = HeroStringReactionRepeat(answ1, answ2, answ3, answ4, npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Merci, je dois y aller.", "Adieu.");
		link.l2.go = "exit";
		break;
	
	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("townman", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix

		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Voilà tout...", " Cela pourrait vous intéresser.");
			posrep2 = " Dites-moi, capitaine, avez-vous des nouvelles pour notre colonie ?";

			answ1 = RandPhraseSimple(RandSwear() + "C’est très intéressant, " + GetFullName(NPChar) + ".", "Alors parle-moi de ça...");
			answ2 = RandPhraseSimple(RandSwear() + "Peu importe, raconte-moi simplement autre chose...", "Ouais, tu ne m'as pas beaucoup aidé, tu as autre chose à partager ?");
			answ3 = RandPhraseSimple("Eh bien, tout peut arriver dans ce monde. Désolé, je n’ai rien de spécial à raconter.", "Je suis un peu pressé, donc peut-être une autre fois.");
			answ4 = "";
		}
		else
		{
			posrep1 = " C’est plutôt ennuyeux ici. Alors quand quelque chose arrive, tout le monde en parle.";
			posrep2 = " Rien d'intéressant. Peut-être que " + GetAddress_Form(NPChar) + " capitaine sait quelque chose ?";

			answ1 = RandPhraseSimple("Alors raconte-moi...", RandSwear() + "Tu ne sais rien ! Très bien, un autre sujet...");
			answ2 = RandPhraseSimple("Peu importe, raconte-moi simplement autre chose...", "Ouais, tu ne m’as pas beaucoup aidé, tu as autre chose à partager ?");
			answ3 = RandPhraseSimple("Je doute d’avoir quelque chose d’intéressant à vous dire.", "Ce sera avec plaisir, mais parlons-en une autre fois.");
			answ4 = "";
		}

		Dialog.Text = NPCStringReactionRepeat(
			srum,
			srum + posrep1,
			srum + posrep2,
			RandPhraseSimple("Hélas, je n’ai rien de plus à vous dire, laissez-moi passer.", "J’en ai assez de vos questions, excusez-moi, j’ai beaucoup d’autres choses à faire."),
			"block", 1, npchar, Dialog.CurrentNode
		);

		link.l1 = HeroStringReactionRepeat(answ1, answ2, answ3, answ4, npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Merci, je dois y aller.", "Adieu.");
		link.l2.go = "exit";
		break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Les rumeurs du port racontent que Julie d'Armagnac, la nièce du gouverneur, n'est plus que l'ombre d'elle-même. Autrefois rayonnante et pleine de vie, elle erre maintenant dans les rues, le visage marqué par une tristesse indéniable. Les habitants chuchotent et s'interrogent sur ce qui a pu lui arriver, mais personne n'en connaît la vérité. Peut-être qu'un gredin lui a brisé le cœur ?"+GetSexPhrase(" C'était peut-être vous, capitaine ?","")+"";
			link.l1 = ""+GetSexPhrase("J’en doute. ","")+"Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
       if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Voilà tout...", " Cela pourrait vous intéresser.");
			posrep2 = " Dites-moi, capitaine, avez-vous des nouvelles pour notre colonie ?";

			answ1 = RandPhraseSimple(RandSwear() + "C’est très intéressant, " + GetFullName(NPChar) + ".", "Alors parle-moi de ça...");
			answ2 = RandPhraseSimple(RandSwear() + "Peu importe, raconte-moi simplement autre chose...", "Ouais, tu ne m'as pas été très utile, tu as autre chose à me dire ?");
			answ3 = RandPhraseSimple("Eh bien, tout peut arriver dans ce monde. Désolé, je n’ai rien de spécial à vous raconter.", "Je suis un peu pressé, donc une autre fois peut-être.");
			answ4 = "";
		}
		else
		{
			posrep1 = " C’est plutôt ennuyeux ici. Alors quand quelque chose se passe, tout le monde en parle.";
			posrep2 = " Rien d'intéressant. Peut-être que " + GetAddress_Form(NPChar) + " capitaine sait quelque chose ?";

			answ1 = RandPhraseSimple("Alors parle-moi de ça...", RandSwear() + "Tu ne sais rien ! Très bien, un autre sujet...");
			answ2 = RandPhraseSimple("Peu importe, raconte-moi simplement autre chose...", "Ouais, tu ne m’as pas beaucoup aidé, tu as autre chose à me dire ?");
			answ3 = RandPhraseSimple("Je doute d’avoir quelque chose d’intéressant à vous raconter.", "Ce serait un plaisir, mais parlons-en une autre fois.");
			answ4 = "";
		}

		Dialog.Text = NPCStringReactionRepeat(
			srum,
			srum + posrep1,
			srum + posrep2,
			RandPhraseSimple("Je pense avoir été clair – j’en ai fini.", "J’en ai assez de vos questions, capitaine. Trouvez-vous quelque chose de mieux à faire !"),
			"block", 1, npchar, Dialog.CurrentNode
		);

		link.l1 = HeroStringReactionRepeat(answ1, answ2, answ3, answ4, npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Merci, je dois y aller.", "Adieu.");
		link.l2.go = "exit";
		break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Les rumeurs du port racontent que Julie d'Armagnac, la nièce du gouverneur, n'est plus que l'ombre d'elle-même. Autrefois rayonnante et pleine de vie, elle erre maintenant dans les rues, le visage marqué par une tristesse indéniable. Les habitants chuchotent et s'interrogent sur ce qui a pu lui arriver, mais personne n'en connaît la vérité. Peut-être qu'un gredin lui a brisé le cœur ?"+GetSexPhrase(" C'était peut-être vous, capitaine ?","")+"";
			link.l1 = ""+GetSexPhrase("J’en doute. ","")+"Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
       if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple("Voilà tout...", " Cela pourrait vous intéresser.");
			posrep2 = " Dites-moi, capitaine, avez-vous des nouvelles pour notre colonie ?";

			answ1 = RandPhraseSimple(RandSwear() + "C’est très intéressant, " + GetFullName(NPChar) + ".", "Alors parle-moi de ça...");
			answ2 = RandPhraseSimple(RandSwear() + "Peu importe, raconte-moi simplement autre chose...", "Ouais, tu ne m'as pas été très utile, tu as autre chose à me dire ?");
			answ3 = RandPhraseSimple("Eh bien, tout peut arriver dans ce monde. Désolé, je n’ai rien de spécial à vous raconter.", "Je suis un peu pressé, donc une autre fois peut-être.");
			answ4 = "";
		}
		else
		{
			posrep1 = " C’est plutôt ennuyeux ici. Alors quand quelque chose se passe, tout le monde en parle.";
			posrep2 = " Rien d'intéressant. Peut-être que " + GetAddress_Form(NPChar) + " capitaine sait quelque chose ?";

			answ1 = RandPhraseSimple("Alors parle-moi de ça...", RandSwear() + "Tu ne sais rien ! Très bien, un autre sujet...");
			answ2 = RandPhraseSimple("Peu importe, raconte-moi simplement autre chose...", "Ouais, tu ne m’as pas beaucoup aidé, tu as autre chose à me dire ?");
			answ3 = RandPhraseSimple("Je doute d’avoir quelque chose d’intéressant à vous raconter.", "Ce serait un plaisir, mais parlons-en une autre fois.");
			answ4 = "";
		}

		Dialog.Text = NPCStringReactionRepeat(
			srum,
			srum + posrep1,
			srum + posrep2,
			RandPhraseSimple("Je pense avoir été clair – j’en ai fini.", "J’en ai assez de vos questions, capitaine. Trouvez-vous quelque chose de mieux à faire !"),
			"block", 1, npchar, Dialog.CurrentNode
		);

		link.l1 = HeroStringReactionRepeat(answ1, answ2, answ3, answ4, npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Merci, je dois y aller.", "Adieu.");
		link.l2.go = "exit";
		break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avant-hier, il y a eu une tentative d'assassinat audacieuse contre le chef de l'autorité portuaire ! L'assassin l'attendait à la sortie du bureau, mais il a réussi à appeler à l'aide. Un mousquetaire est arrivé à temps et a blessé l'agresseur, mais le criminel a réussi à s'échapper de la ville\nOn dit que le chef du port offre une généreuse récompense pour sa tête ! Jusqu'à présent, aucune âme brave ne s'est manifestée. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Merci, je dois prendre congé.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("sailor", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix

		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Voilà les nouvelles...", " Peut-être que cela vous amusera.");
			posrep2 = " Et vous, capitaine, avez-vous des nouvelles à partager avec notre colonie ?";

			answ1 = RandPhraseSimple(RandSwear() + "Tu racontes des choses intéressantes, " + GetFullName(NPChar) + ".", "Alors raconte-moi encore...");
			answ2 = RandPhraseSimple(RandSwear() + "C’est très intéressant ! Voilà ce que je voulais encore" + GetSexPhrase("", "e") + " te demander...", "Encore une question.");
			answ3 = RandPhraseSimple("Il se passe tellement de choses dans ce monde. Désolé, je n’ai aucune nouvelle à partager.", "Je suis un peu pressé(e), donc une autre fois peut-être.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Il ne se passe presque jamais rien ici. Mais si quelque chose d’inhabituel arrive, tout le monde en parle.";
			posrep2 = " Donc pas de nouvelles. Mais peut-être que le " + GetAddress_Form(NPChar, false) + " capitaine sait quelque chose ?";

			answ1 = RandPhraseSimple("Alors raconte-moi autre chose...", RandSwear() + "Tu ne sais rien ! Très bien, voilà ce que je voulais encore" + GetSexPhrase("", "e") + " te demander...");
			answ2 = RandPhraseSimple("Tu dis ne rien savoir, alors dis-moi...", "Tu ne m’as pas beaucoup aidé" + NPCharSexPhrase(NPChar, "", "e") + ", mais peut-être sais-tu autre chose ?");
			answ3 = RandPhraseSimple("Je doute d’avoir quelque chose qui pourrait vous intéresser.", "Je serais ravi(e) de vous raconter quelque chose, mais une autre fois.");
			answ4 = "";
		}

		Dialog.Text = NPCStringReactionRepeat(
			srum,
			srum + posrep1,
			srum + posrep2,
			RandPhraseSimple("Malheureusement, je ne sais rien de plus, laissez-moi partir.", "Vous m’épuisez avec vos questions, excusez-moi, mais j’ai des choses à faire."),
			"block", 1, npchar, Dialog.CurrentNode
		);

		link.l1 = HeroStringReactionRepeat(answ1, answ2, answ3, answ4, npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Merci, je dois prendre congé.", "Portez-vous bien.");
		link.l2.go = "exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(chante) Un jour j’ai croisé un navire de Hambourg. Sur ses mâts – cloportes et moisissure, la coque pourrie – et des coquillages à l’arrière. La cale pleine de punaises, les cuisines – une horreur... Alors, matelot" + GetSexPhrase("", "te") + ", raconte ! Comment ça va là-bas, sur la mer ?";
            link.l1 = "En mer, tout comme toujours – humide et salé. Dis-moi plutôt, tu sais où est passé mon ami qui louait une chambre ici récemment ? Il s’appelle François Gontier.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(chante) Je reme-ercie le whisky pour mon nez cramoisi, et sur ses co-onseils j’ai mis mon manteau en gage... Allez, sers, matelot" + GetSexPhrase("", "te") + " ! Je suis revenu d’un voyage juste hier, alors je suis encore un peu vaseux.";
            link.l1 = "Sers-toi, l’ami ! Alors, comment ça va en mer, tu as vu quelque chose d’intéressant ?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Ah, la mer, la mer... Comme j’aimerais être à ta place !";
            link.l1 = "Alors qu’est-ce qui t’en empêche, mon ami ? Viens donc matelot sur mon navire.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Bois un rhum, sois courageux, et t’auras cent amis ! Ha-ha !", "Vide une bonne chope – même le geôlier semblera gentil ! Ha-ha !", "Rhum et ale te montrent le paradis – verse et bois ! Ha-ha !");
            link.l1 = "À la tienne, camarade... Dis-moi, l’ami, est-ce qu’un homme nommé " + pchar.GenQuest.FindFugitive.Name + " est passé par ici ? C’est un ancien compagnon de route. On m’a dit qu’il aurait mis le cap sur votre village...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Alors, quelles nouvelles avons-nous ici ? *Hic* T’as rien entendu ? Nos gardes ont attrapé un espion français. Il faisait semblant d’être marchand, le gredin, mais... *hic* – avec notre commandant, on ne plaisante pas !";
            link.l1 = "Sans blague ! Et qu’est-ce que ce foutu grenouille cherchait ici ?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Ah, " + GetAddress_Form(pchar) + ", dans quel monde vivons-nous... Plus rien de sacré chez les gens de nos jours !";
			link.l1 = "Qu’est-ce que tu veux dire par là, l’ami ?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы

		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Vous avez entendu ? C’est incroyable ! Le célèbre capitaine Fleetwood a été sauvagement assassiné à Londres ! Il cherchait la gloire, et il a trouvé la mort... S’il était resté ici, il serait encore en vie. Parfois il vaut mieux apprécier ce qu’on a, au lieu de courir après l’argent ou les titres, souvenez-vous-en, monsieur !";
            link.l1 = "Nom de Dieu, quelle nouvelle !... Dis-moi, l’ami, tu sais sûrement qui habite où dans cette ville, non ?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов

		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Alors, ton nouveau héros, le capitaine Edgardo Sotta – qu’en dit-on en ville ? Et toi, tu en penses quoi ? J’avais tellement envie de le voir.";
			link.l1.go = "Sotta1";
			link.l2 = "Dis-moi, pourquoi tu bois tout seul ici, l’ami ? Tout le monde est dehors à regarder ce bavard de Matt se balancer.";
			link.l2.go = "Lutter1";
			break;
		}

		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Dis-moi, l’ami, je cherche un certain Sepp van der Wink. J’ai quelque chose à lui remettre. Tu saurais à quoi il ressemble, ou tu pourrais me dire quelque chose sur lui ?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"

		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2){
			dialog.text = "Avez-vous entendu ? On dit que la fille de Thomas Morrison est clouée au lit depuis six mois. Les médecins sont totalement impuissants face à sa maladie. La seule qui pourrait lui venir en aide est une gitane célèbre pour ses potions qui remettent sur pied même les plus malades. Mais elle a catégoriquement refusé de faire quoi que ce soit pour la pauvre enfant.";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avant-hier, il y a eu une tentative d'assassinat audacieuse contre le chef de l'autorité portuaire ! L'assassin l'attendait à la sortie du bureau, mais il a réussi à appeler à l'aide. Un mousquetaire est arrivé à temps et a blessé l'agresseur, mais le criminel a réussi à s'échapper de la ville\nOn dit que le chef du port offre une généreuse récompense pour sa tête ! Jusqu'à présent, aucune âme brave ne s'est manifestée. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Avez-vous entendu la nouvelle?! C'est un scandale sanglant! Pas une goutte de rhum ou de vin dans la taverne - comment trouver du réconfort sous cette chaleur maudite? Le tavernier nous abreuve de promesses creuses depuis une semaine que les boissons couleront à nouveau, mais toujours rien! Devons-nous donc assécher nos gosiers jusqu'au Jugement Dernier?";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "Le bruit court sur les quais que notre tavernier est dans de beaux draps ! Quelqu'un a subtilisé son gin ! Pas seulement une bouteille, notez bien, mais un tonneau entier - du genre qu'on ne trouve nulle part ailleurs dans ces îles ! Importé tout droit d'Europe, à ce qu'on dit. Le vieux renard ne veut pas dire pour qui il le gardait, mais une chose est sûre : si ce tonneau ne réapparaît pas bientôt, ce sera l'enfer pour le pauvre bougre !";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Старые счёты
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Les rumeurs du port racontent que Julie d'Armagnac, la nièce du gouverneur, n'est plus que l'ombre d'elle-même. Autrefois rayonnante et pleine de vie, elle erre maintenant dans les rues, le visage marqué par une tristesse indéniable. Les habitants chuchotent et s'interrogent sur ce qui a pu lui arriver, mais personne n'en connaît la vérité. Peut-être qu'un gredin lui a brisé le cœur ?"+GetSexPhrase(" C'était peut-être vous, capitaine ?","")+"";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Le bruit court que le pêcheur Pierre Carno a disparu sans laisser de trace. Il y a deux aubes, il a pris la mer et depuis, pas le moindre signe de lui. Sa femme, Lea, est folle d'inquiétude. Jour et nuit, elle monte la garde sur le quai, les youux rivés sur les eaux infinies, priant pour apercevoir la voile de son bien-aimé.";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова
		
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitaine, avez-vous entendu ? Une nouvelle serveuse travaille dans notre taverne. On dit que c'est une vraie beauté. Des hommes de partout accouraient juste pour l'apercevoir. Mais il y a trois jours, elle ne s'est pas présentée au travail, ce qui a grandement contrarié le tavernier qui réalisait d'énormes profits depuis son arrivée. On dit qu'il est même prêt à payer quiconque pourra la retrouver.​";
			link.l1 = RandPhraseSimple(RandSwear() + "Cela mérite une autre chope...",
                                 "Très bien. Servons-nous une autre chope de rhum.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Merci, je dois prendre congé.",
									 "Ah, ce rhum corsé... Bon, il est temps pour moi de partir. Passez une bonne soirée.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		
		Dialog.Text = LinkRandPhrase("Well... hic! ","Ah, good rum! ","Well... ")+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Thanks, I should go.",
                                 "Eh, helluva rum. Fine, I should go, have fun here.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader != 3 )
			strum = SelectRumourEx("trader", NPChar);
			else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Oui. Je ne me souviens de rien d'autre.",
				strum+" Et maintenant, je dois retourner à mes affaires.",RandPhraseSimple("Je vous ai dit que je n'ai pas de temps pour bavarder !","Je suis un homme occupé, pas de temps pour les ragots !"),"block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "C’est très intéressant ! Mais passons aux affaires","Merci, j’ai une autre affaire à discuter."),
			pcharrepphrase(""+ GetSexPhrase("Que je crève","Tonnerre de Brest") +" ! Tu mens bien. Mais j’ai encore une question.","Alors ne perdons pas de temps et allons à l’essentiel."),
			pcharrepphrase(RandSwear() +" Encore une affaire et je m’en vais.","Vous avez raison, le temps c’est de l’argent."),
			pcharrepphrase("Tu ne penses qu’à ton profit. D’accord, calme-toi.","Pardonnez-moi. Revenons aux affaires."),npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("À plus, vieux pochard.",
		"Bonne journée, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),pcharrepphrase("Caramba ! Ne bouge pas. Je reviendrai.","Heureux de vous voir, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+" ! Au revoir !")),NPCharRepPhrase(npchar,pcharrepphrase("Larguez les amarres !","Au revoir, cher ami."),pcharrepphrase("Hé ! Tu caches du rhum là ? Non ?! Bon, je vais boire un coup.","Veuillez m’excuser, j’ai des affaires urgentes en ville.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh ! On se reverra !","Je dois partir. Adieu, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+" !"),pcharrepphrase("Ne me contrarie pas ! Je n’ai pas le temps de discuter avec toi !","Je devrais vérifier le navire. Adieu, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+" !")),NPCharRepPhrase(npchar,pcharrepphrase("Qu’est-ce qui te prend, vieux ? C’est moi - " +GetFullName(pchar)+ " ! Dessoûle-toi, je reviendrai.","Je crains que ton foie ne te tue avant que je repasse."),pcharrepphrase("Compte ton argent, filou ! Je reviendrai.","Heureux"+ GetSexPhrase("","e") +" de vous avoir vu, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+" !")),npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I want to ask...",
                                     "One more question.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Thanks, I should go.",
                                     "Farewell.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I want to ask...",
                                     "One more question.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Thanks, I should go.",
                                     "Farewell.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
			if(startHeroType == 4)
			{
				Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Tu connais le tarif. L’information, c’est comme une chambre, un repas ou un verre. Ça te coûtera mille pesos.",
				"Tu connais le tarif. L’information, c’est comme une chambre, un repas ou un verre. Ça te coûtera mille pesos.",
				"Tu connais le tarif. L’information, c’est comme une chambre, un repas ou un verre. Ça te coûtera mille pesos."),
				"Je n’ai rien à ajouter. Et maintenant, excuse-moi, j’ai du travail.",
				"", "", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("En fait, pourquoi je paierais ? Je peux poser la question à quelqu’un d’autre. Désolé(e) pour le dérangement.",
												 "En fait, pourquoi je paierais ? Je peux poser la question à quelqu’un d’autre. Désolé(e) pour le dérangement."), "", "", "", npchar, Dialog.CurrentNode);
				link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);
				NextDiag.CurrentNode = NextDiag.TempNode;

				if (makeint(pchar.money) >= 1000)
				{
					link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Je sais, bien sûr. Voici ma commande.", "Je sais, bien sûr. Voilà pour toi."),
					"", "", "" , npchar, Dialog.CurrentNode);
					link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				}
				else
				{
					link.l2 = HeroStringReactionRepeat("Je n’ai pas cette somme.", "", "", "", npchar, Dialog.CurrentNode);
					link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				}
			}
			else
			{
				Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("L’information a un prix. Pour 1000 pesos, je te dis tout ce que je sais.",
				"J’ai un trou de mémoire... mais peut-être que 1000 pièces raviveront mes souvenirs.",
				"Je suis prêt à tout raconter. Mais pas gratuitement – 1000 pesos, pas un de moins."),
				"Je n’ai rien à ajouter. Et maintenant, excuse-moi, j’ai du travail.",
				"", "", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "Payer pour des commérages ? Trouve quelqu’un d’autre.",
												 "À ce prix-là, je me débrouillerai tout(e) seul(e)."), "Parlons d’autre chose.", "Parlons d’autre chose.", "Parlons d’autre chose.", npchar, Dialog.CurrentNode);
				link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);
				NextDiag.CurrentNode = NextDiag.TempNode;

				if (makeint(pchar.money) >= 1000 )
				{
					link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Tu les auras si ce que tu me dis vaut vraiment le coup.", "Je paierai, mais à condition d’avoir quelque chose de vraiment utile."),
					 "", "", "" , npchar, Dialog.CurrentNode);
					link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				}
				else
				{
					link.l2 = HeroStringReactionRepeat("Je n’ai pas cette somme.", "", "", "", npchar, Dialog.CurrentNode);
					link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				}
			}
		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text =  "Récemment, notre patrouille a coulé une goélette appartenant à un contrebandier français nommé Morel, et l’a capturé vivant. Il est maintenant en prison en attendant son procès. Le commandant est persuadé que toute la cargaison de contrebande n’était pas à bord, et il tente de lui faire avouer le reste. Une fois qu’il saura... ce sera fini pour le Français.";
					link.l1 = "Très intéressant... Très bien, tu as mérité ton argent – le voilà. Tu ne sais rien d’autre de notable ?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "Il y a peu, il y a eu une grande fête au palais du gouverneur. Don Carlos de Millar est revenu, un vieil ami de Son Excellence. Il avait été capturé par les Français lors d’un combat naval, mais il a réussi à s’échapper en convainquant un lieutenant français. Don Carlos est un homme astucieux, et généreux aussi : ce lieutenant, Jean Deneau, a été intégré à l’armée avec le rang de capitaine et un commandement sur un navire nommé 'Serio'. On dit même qu’il a reçu une petite plantation. Maintenant, on l’appelle don Juan. Eh oui !";
				link.l1 = "Très intéressant... Très bien, tu as mérité ton argent – le voilà. Tu ne sais rien d’autre de notable ?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "Notre commandant a renforcé les patrouilles dans la jungle et la sécurité en ville. Il paraît que les Anglais préparent une opération pour pénétrer à Philipsburg et libérer des officiers emprisonnés.";
				link.l1 = "Vraiment ? Les Anglais oseraient une telle chose ?... Et ces officiers, tu sais qui c’est ?";
				link.l1.go = "FMQN_r";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "Ces derniers jours, notre ville a été en émoi. Un officier d’une goélette de guerre s’est saoulé ici à la taverne, a tenté de violer une femme mariée, a roué de coups son mari qui tentait de la défendre, tout en menaçant avec son sabre dégainé. Et tout cela sous le regard complaisant de la garde ! On dit que les corbeaux ne se crèvent pas les yeux... Les soldats détournaient les yeux pendant que cet énergumène faisait ses saletés.\nMais il a été maîtrisé – devine par qui ? – des marins d’un navire marchand. Ils ont failli l’attraper, mais il s’est échappé et a regagné son navire. Le commandant et l’alcalde voulaient étouffer l’affaire, mais le mari, un citoyen respectable, s’est adressé à Son Excellence don Diego de Toledo. Cela a soulevé l’indignation des notables. L’officier a été arrêté.\nOn raconte que le capitaine du navire, Esberto Cabañas, homme d’honneur, en apprenant ce que son officier avait fait, l’a fait immédiatement arrêter et l’a livré aux autorités. Le fauteur de trouble est maintenant en prison, où il passera un bon moment. Ensuite, on dit qu’il sera rétrogradé au rang de simple soldat – pour l’exemple.";
				link.l1 = "Qu’as-tu dit ? Le capitaine Esberto Cabañas ? Hm... histoire très intéressante !... Très bien, tu as mérité ton argent – le voilà. Tu ne sais rien d’autre de notable ?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "On raconte que des criminels ont été débarqués sur l'une des îles désertes ! Apparemment, ce sont des monstres si féroces que ni le bourreau ni les hommes d'Église ne voudraient avoir affaire à eux ! Mais pourquoi les amène-t-on toujours ici ?";
				link.l1 = "Hmm... intéressant ! Peut-être que je pourrais les trouver et les recruter — j’ai toujours besoin de types désespérés... Pourquoi tu pâlis ? Je plaisante, je plaisante... Tu as gagné ton argent — le voilà. Tu ne connais rien d’autre d’intéressant ?";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
			string RumText = SelectRumourEx("tavern", NPChar); //fix

			if(!RumourHasInformation(RumText))
			{
				Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "Tu ne sais rien, on dirait. Je n’aurais jamais pensé que tu essaierais de me tromper. Ce ne serait pas très malin. Bon, salut.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Je ne paierai pas pour des ragots inutiles, adieu.", "Tes informations ne valent rien — tu n’auras rien.");
				}
				link.l1.go = "Exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "Vraiment ? Intéressant, merci. Bon, il est temps pour moi de partir, à bientôt.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Merci, voici ton argent. Tu te souviens d’autre chose ?", "Très bien, tu as gagné ton argent — le voilà. Tu as autre chose ?");
					link.l1.go = "rumours_tavern";
				}
				NextDiag.CurrentNode = NextDiag.TempNode;    
			}
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Tu aurais pu m'aider avec un peu d'argent. Contrairement à toi, je n'ai pas le soutien du baron de la Fraternité, Hélène.";
				link.l1 = "Tu as tout un établissement. Et moi, j’ai tout obtenu par moi-même. Enfin, il m’a juste acheté un navire. Et des canons. Et engagé l’équipage. Et équipé le tout. Bon, peu importe.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Comprenez-moi bien, je dois nourrir ma famille.";
				link.l1 = "Parlons d'autre chose.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Merci, je "+ GetSexPhrase("dois","dois") +" prendre congé.",
										 "Tout le meilleur", "Au revoir.");
				link.l2.go = "Exit";
			}
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Oui, c’est intéressant. J’ai encore une question...",
										"Hmm, j’aimerais aussi te demander une autre chose...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Bon, adieu, commerçant.",
										"Bonne chance, l’ami.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Je n’ai plus rien à dire, j’ai déjà tout raconté.", 
					"Je n’ai rien entendu de plus, désolé...");
				Link.l1 = RandPhraseSimple("Je vois. Eh bien, bonne chance.",
										"D’accord. À bientôt, l’ami...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

		case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Oui, c’est intéressant. J’ai encore une question...",
										"Hmm, j’aimerais aussi te demander une autre chose...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Bon, adieu, commerçant.",
										"Bonne chance, l’ami.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Je n’ai plus rien à dire, j’ai déjà tout raconté.", 
					"Je n’ai rien entendu de plus, désolé...");
				Link.l1 = RandPhraseSimple("Je vois. Eh bien, bonne chance.",
										"D’accord. À bientôt, l’ami...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("Je vois...",
										"Compris...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("Je n’ai plus rien à dire, j’ai déjà tout raconté.", "Je n’ai rien entendu de plus, désolé..."), 
					RandPhraseSimple("Désolée, mais je vous ai déjà tout dit.", "Je n’ai rien entendu de plus, pardonnez-moi..."));
				Link.l1 = RandPhraseSimple("Je comprends" + GetSexPhrase("","e") + ".", "Très bien, à bientôt.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Ah capitaine ! Je suis toujours content de discuter. Vous savez, parfois, on s’ennuie terriblement ici tout seul...", "Je vis ici seul, les visiteurs sont rares. Alors échanger quelques mots avec quelqu’un est toujours une joie pour moi."), 
												  "Vous aimez parler, capitaine ? Peut-être que je me rappellerai autre chose...", 
												  "Si vous revenez me voir, apportez une bouteille de rhum. L’alcool rend les conversations bien plus agréables...", 
												  "Malheureusement, j’ai tout dit. Je n’ai rien de plus à ajouter.", 
												  "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Alors partage ton information. Moi aussi, tu sais, j’aime bien bavarder...", "Allez, raconte ! Celui qui détient l’info détient le pouvoir, non ?"), 
											   "Par exemple ?", 
											   "Bien sûr ! Alors, qu’as-tu encore entendu ?", 
											   "Très bien, on a déjà bien parlé.", 
											   npchar, Dialog.CurrentNode);
			link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;

		case "rumours_lighthouse_yes":
			RumText = SelectRumourEx("tavern", NPChar);
			if(!RumourHasInformation(RumText))
			{
				Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
				link.l1 = RandPhraseSimple("Merci ! As-tu entendu autre chose ?", "Très intéressant ! Tu ne te souviens de rien d’autre ?");
				link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Merci ! C’était très instructif...", "Merci pour l’information !");
				link.l2.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = RumText;
				link.l1 = RandPhraseSimple("Merci ! C’était très intéressant... Tu n’as rien d’autre à dire ?", "Très intéressant ! Tu ne te souviens de rien d’autre ?");
				link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Merci ! C’était très instructif...", "Merci pour ce récit intéressant !");
				link.l2.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;    
			}
		break;

		case "rumours_lighthouse_void":
			Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
			link.l1 = RandPhraseSimple("Merci ! As-tu entendu autre chose ?", "Très intéressant ! Tu ne te souviens de rien d’autre ?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = RandPhraseSimple("Merci ! C’était très instructif...", "Merci pour ce récit intéressant !");
			link.l2.go = "exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "Mais où est le paquet ? Vous ne l'avez pas ?";
				link.l1 = "Hmm... j'étais censé vous le livrer. Mais pour être honnête, on me l’a tout simplement... arraché. Je n’ai pas pu résister à l’attaque et je leur ai donné le paquet.";
				link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}

			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4) //раскрыли обман
			{
				dialog.text = "Hmm. Attendez, ce paquet a déjà été ouvert ! Je le vois clairement. Le sceau a été apposé une seconde fois...";
				link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", je vous ai apporté le paquet tel que je l’ai reçu à l’administration portuaire de " + XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen") + ", et je n’en sais pas plus...";
				link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}

			if (pchar.questTemp.WPU.Postcureer == "late") //опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));
				dialog.text = "Je vous attendais. Mais vous êtes en retard de " + FindRussianDaysString(iTime) + " ! L’information contenue dans ce document a déjà largement perdu de sa valeur... Mais elle reste utile — je vous paierai donc pour votre travail, même si ce sera moins — " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Voici votre paiement, et adieu.";
				link.l1 = "Merci tout de même.";
				link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("","а"));
				break;
			}

			if (pchar.questTemp.WPU.Postcureer == "lost") //опоздали совсем
			{
				dialog.text = "C’est donc vous ! Et pourtant je ne vous attendais plus, j’ai déjà pris les mesures appropriées — vous savez, les chasseurs d’informations importantes ne manquent pas. Donnez-moi le paquet. Bien qu’il ne me soit plus d’aucune utilité, à cause de votre retard... Je le garderai tout de même.\nComme vous vous en doutez, vous ne recevrez aucun paiement. Tout ce que je peux faire, c’est prendre des mesures pour rétablir votre réputation.";
				link.l1 = "Merci tout de même. Pardonnez mon retard, je le regrette vraiment. Adieu.";
				link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}

			dialog.text = "Je vous attendais. Vous êtes arrivé à temps — l’information que vous avez apportée est très utile. Voici votre paiement — " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Merci pour votre réactivité.";
			link.l1 = "Merci à vous aussi. Au revoir !";
			link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "Ah, je le savais, ça allait forcément finir comme ça... J’aurais dû engager un service de messagerie militaire au lieu de me fier à des capitaines civils... Bon, " + GetAddress_Form(NPChar, false) + ", je ne vais pas vous blâmer — après tout, vous n’êtes pas un soldat. Adieu.";
			link.l1 = "Au revoir, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;

		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "Monsieur, je connais personnellement le chef du port de " + XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen") + ", c’est un homme d’une grande intégrité. Il n’aurait eu aucune raison d’ouvrir ce message. " + GetAddress_Form(NPChar, false) + ", vous êtes un escroc ! Je ne vous paierai rien. Sortez d’ici !";
			link.l1 = "Ghm-m...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = "Il avait l'air d’un vrai va-nu-pieds, probablement un mendiant ou un sans-abri. Où il est allé ? Je ne peux pas vous dire, je n’avais pas le temps de le suivre. Il est parti quelque part, mais Dieu seul sait où.";
			link.l1 = "C’est déjà une information — c’est mieux que rien. Merci ! Je pars à sa recherche !";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			DelLandQuestMark(npchar);
			Dialog.Text = "Il n’y a pas si longtemps, un navire anglais a été capturé au large de Saint-Martin, et à son bord se trouvaient plusieurs officiers militaires de haut rang. On a décidé de les transférer à Willemstad, mais pour l’instant, ils ont été enfermés en prison. On raconte qu’un soldat prisonnier de ce navire a révélé au commandant, en échange de sa liberté, que les Anglais comptaient envoyer un groupe de sabotage pour organiser l’évasion des détenus. Ils avaient même un plan prêt. Voilà pourquoi notre brave commandant est sur le qui-vive. Car si des oiseaux de ce calibre s’échappent — il sera sûrement rétrogradé simple soldat. Voilà !";
			link.l1 = "Très intéressant... Très bien, tu as mérité ton argent — le voilà. Tu n’as rien d’autre à signaler ?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
           Dialog.Text = RandPhraseSimple("Très bien. J’ai un paquet prêt pour vous, que vous devez remettre en main propre à la personne désignée. Le voici.\nNe me parlez plus et ne vous approchez pas de moi, cela pourrait éveiller des soupçons. Soyez prudent...", 
                               "Hmm, parfait. Je vous remets ce paquet, souvenez-vous qu’il doit être livré en main propre à la personne que vous avez mentionnée.\nMaintenant, adieu, et ne m’approchez plus — c’est dangereux.");
			link.l1 = RandPhraseSimple("J’ai compris" + GetSexPhrase("","e") + ". Adieu...", "Adieu et bonne chance.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       case "Man_FackYou":
			dialog.text = LinkRandPhrase("Un vol en plein jour !!! Mais qu’est-ce que c’est que ça ?! Tu vas voir, " + GetSexPhrase("mon gars", "ma fille") + "...", 
										 "Hé, qu’est-ce que tu fabriques là ? Tu veux me voler ou quoi ? Tu es foutu" + GetSexPhrase("", "e") + "...", 
										 "Attends, où tu vas comme ça ?! Mais tu es un" + GetSexPhrase("", "e") + " voleur" + GetSexPhrase("", "se") + ", en fait ! Tu peux dire adieu, mon" + GetSexPhrase(" gars", " amie") + "...");
			link.l1 = LinkRandPhrase("Diable !!", "Caramba !!", "Ahh, zut !");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Bug évident. Veuillez le signaler à l'AT.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, Monsieur le Gouverneur est un homme remarquable. Il dirige habilement notre colonie — depuis sa fondation, nous n'avons connu aucun conflit majeur\nSon seul défaut, c'est qu'il est... hmm... très économe. Mais peut-être est-ce une qualité, après tout.";
	STR_MAYOR[1] = "Oh, Monsieur le Gouverneur est un homme remarquable. Il dirige habilement notre colonie — depuis sa fondation, nous n'avons connu aucun conflit majeur\nSon seul défaut, c'est qu'il est... hmm... très économe. Mais peut-être est-ce une qualité, après tout.";
	STR_MAYOR[2] = "Hélas, notre gouverneur est un homme bon... mais sans caractère. S'il avait un peu plus de fermeté, nos marchands bénéficieraient de quelques allègements fiscaux... Et des subventions pour la réparation du fort auraient déjà été allouées.";
	STR_MAYOR[3] = "Hmm... Il est récemment devenu notre gouverneur. Il est assez jeune et donc très entreprenant — sous sa direction, notre colonie prospère.";
	STR_MAYOR[4] = "Notre gouverneur est encore relativement jeune. On dit qu'il est le fils cadet indiscipliné d'un comte espagnol, envoyé loin de la cour pour cesser de déshonorer sa famille. Il a été nommé ici récemment et n'a pas encore eu l'occasion de se distinguer.";
	STR_MAYOR[5] = "Hmm... Il est récemment devenu notre gouverneur. Il est assez jeune et donc très entreprenant — sous sa direction, notre colonie prospère.";
	STR_MAYOR[6] = "Euh... Je ne peux rien dire de mal à son sujet.";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hmm, je ne confierais pas mes biens à ce filou. Ne vous méprenez pas, mais il me semble être la personne la moins fiable de notre ville. On dit qu'il fricote avec des contrebandiers et des pirates – et sa taverne est constamment fréquentée par toute une bande de vauriens !";
	STR_TAVERNKEEPER[1] = "Que dire de lui ! Il est plutôt lâche et pas très futé. En plus, il est avide d'argent, ce qui le met souvent dans des situations délicates ! Mais il est toujours au courant des dernières nouvelles.";
	STR_TAVERNKEEPER[2] = "Un type assez sympathique. Sa taverne est toujours agréable, et il a un bon sens de l'humour. Surtout, il veille à l'ordre et ne permet pas aux ivrognes de déranger les citoyens respectables.";
	STR_TAVERNKEEPER[3] = "Un homme étonnant. Il devrait être informateur pour la chancellerie secrète plutôt que de tenir une taverne. Parfois, on dirait qu'il sait absolument tout ce qui se passe en ville. C'en est presque effrayant.";
	STR_TAVERNKEEPER[4] = "Je ne sais pas quoi vous dire à son sujet. C'est un homme comme un autre. Il tient une taverne et est donc au courant de toutes les nouvelles de notre île.";
	STR_TAVERNKEEPER[5] = "On dit qu'on peut compter sur lui. D'un autre côté, j'ai entendu dire qu'il évite les risques inutiles et gère ses affaires de manière calculée. Et il ne semble pas impliqué dans des affaires louches.";
	STR_TAVERNKEEPER[6] = "Il a hérité de la taverne de son père. Son père tenait une taverne non loin d'ici, sur la petite île de Hairoch dans un autre archipel. Ensuite, il s'est installé ici, a construit une nouvelle taverne, et maintenant c'est son fils qui la dirige.";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Il construit de bons navires... Mais en tant qu'homme, il est difficile de dire quelque chose – il vit calmement et discrètement. Probablement un homme bien.";
	STR_SHIPYARDER[1] = "Il construit de bons navires... Mais en tant qu'homme, il est difficile de dire quelque chose – il vit calmement et discrètement. Probablement un homme bien.";
	STR_SHIPYARDER[2] = "Un homme pas mal, mais on dit qu'il est trop sévère. Il réprimande constamment ses ouvriers. C’est pourquoi ils changent souvent. Pourtant, malgré cela, c’est un excellent constructeur naval.";
	STR_SHIPYARDER[3] = "C'est un homme très instruit. On dit qu'il a étudié la construction navale en Angleterre, puis en Hollande. Et il a fini ici – loin de la métropole, dans un archipel perdu. Il paraît qu’il a eu des ennuis avec la Sainte Inquisition, et a dû fuir dans les colonies.";
	STR_SHIPYARDER[4] = "Oui, ce vieil homme n’est plus bon à grand-chose. Il rêve sans cesse du passé, et râle dès qu’on lui commande autre chose qu’une caravelle ou un galion.";
	STR_SHIPYARDER[5] = "Un type formidable. Toujours prêt à aider, à tirer quelqu’un d’un mauvais pas. Il faut dire qu’il construit de très bons navires pour un endroit aussi reculé.";
	STR_SHIPYARDER[6] = "Il était un exilé dans notre colonie jusqu'à ce qu'on découvre son talent pour la construction navale. Après avoir supervisé la construction de deux magnifiques bricks, il a été gracié et est désormais un membre à part entière de notre société.";

	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "Je ne peux rien dire de mal à son sujet. Un citoyen respectable, un paroissien assidu de notre église. Je n'ai jamais entendu quelqu’un le critiquer ou se plaindre de lui.";
	STR_TRADER[1] = "Il est le principal fournisseur de notre gouverneur, ce qui lui assure un bon revenu. Mais il gère ses affaires honnêtement. Enfin, jusqu'à présent, on ne l’a jamais surpris en faute.";
	STR_TRADER[2] = "Ce gros bonhomme est respecté à juste titre dans notre ville. Sa marchandise est toujours de première qualité, et je ne me souviens pas qu’il ait jamais trompé qui que ce soit.";
	STR_TRADER[3] = "Ce type n’est pas très doué. Il commerce, oui, mais ça ne mène à rien. Il manque toujours de certaines marchandises, et lui-même est constamment endetté.";
	STR_TRADER[4] = "Ce n’est pas un homme bien, monsieur. On raconte qu’il était l’assistant de Baudouin Coffier, mais qu’il l’a ruiné avant de racheter sa boutique. Je ne sais pas pour la qualité de ses marchandises, mais en tant que personne, je ne l’aime pas du tout.";
	STR_TRADER[5] = "Oh ! C’est un individu ignoble, je vous déconseille fortement de faire affaire avec lui. Il tient la moitié des habitants de notre ville endettés ! Et les produits qu’il vend sont toujours de mauvaise qualité.";
	STR_TRADER[6] = "Personne ne sait vraiment grand-chose sur lui. Il s’est récemment installé ici et a immédiatement ouvert son commerce. Il semble vendre honnêtement, sans faire de contrebande.";

	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
