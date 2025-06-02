// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions, "+GetSexPhrase("mon fils","ma fille")+"?","Demandez, je vous écoute..."),"Je t'écoute, parle maintenant, "+GetSexPhrase("mon fils","ma fille")+"...","Pour la troisième fois, "+GetSexPhrase("mon fils","mafille")+", demandez ce dont vous avez besoin.","Un ecclésiastique a beaucoup de travail et vous me distraisez, "+GetSexPhrase("mon fils","ma fille")+"... ","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas pour le moment, padre..."),"Je n'ai rien à dire, mes excuses.","Je demanderai, mais plus tard. Pardonnez-moi, mon père.","Pardonnez-moi, saint père...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Mon père, je veux parler de la fille de Thomas Morrison.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Mon père, Thomas m'a demandé de vous dire qu'il se repentira, se consacrera à de bonnes actions et offrira une nouvelle cloche à la paroisse, quoi qu'il lui en coûte.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Parle, mon enfant, je t'écoute.";
			link.l1 = "Je sais que vous êtes contre l'idée que la gitane aide la fillette. Mais peut-on vraiment forcer un père à rejeter la moindre chance de sauver sa fille ? Même si ses méthodes semblent douteuses, elle possède des connaissances qui peuvent être utiles.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_2":
			dialog.text = "Mon fils, seul le Seigneur peut guérir l'enfant. La foi en Sa volonté nous guide à travers les épreuves. Si Thomas prie avec ferveur, suit la parole de Dieu et fait preuve de générosité envers l'église, le Seigneur exaucera ses prières et lui accordera Sa grâce.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Digne de confiance) Mais même vous devez admettre que le Seigneur agit à travers les hommes. Et si la gitane n'était qu'un instrument entre Ses mains ? Et si Son dessein était si profond que nous, simples mortels, ne pouvons le comprendre ? Les voies du Seigneur sont impénétrables, n'est-ce pas ?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Digne de confiance", "Trustworthy");
			}
			else
			{
				link.l1 = "Vous forcez un père à regarder sa fille s'éteindre lentement, plutôt que de lui permettre de tenter de la sauver. Est-ce cela la miséricorde ?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Compétence non débloquée", "Trustworthy");
			}
		break;
		
		case "dwh_pastor_VD_1":
			dialog.text = "Vos paroles sont sages, capitaine. Pourtant, je ne peux permettre que l'hérésie pénètre au cœur de notre paroisse et ébranle la foi de l'un de ses plus fidèles fils.";
			link.l1 = "Rien ne pourra ébranler davantage sa foi que la mort de sa propre fille. Si vous lui permettez d'utiliser tous les moyens, même ceux qualifiés de péché, sa foi ne faiblira pas, elle deviendra plus forte.";
			link.l1.go = "dwh_pastor_VD_2";
		break;
		
		case "dwh_pastor_VD_2":
			dialog.text = "Mais... Quel exemple cela donnera-t-il aux autres membres de la paroisse ?";
			link.l1 = "Celui que l'église ne punit pas aveuglément, mais guide vers une vraie repentance. L'Écriture n'enseigne-t-elle pas que la véritable contrition et les bonnes actions peuvent racheter un péché ? Le premier pas pourrait être un don généreux à l'église.";
			link.l1.go = "dwh_pastor_VD_3";
		break;
		
		case "dwh_pastor_VD_3":
			dialog.text = "Peut-être avez-vous raison, capitaine. Je suis prêt à donner une chance à Thomas. Mais sachez que si sa foi vacille, la responsabilité retombera aussi sur vous ! Quant aux dons... l'église n'a pas besoin de richesse, nous avons tout le nécessaire. Sauf... une cloche, endommagée lors d'une attaque espagnole...";
			link.l1 = "Je transmettrai vos paroles à Thomas. Merci pour cette conversation, mon père. Que Dieu vous garde.";
			link.l1.go = "dwh_pastor_VD_4";
		break;
		
		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;
		
		case "dwh_pastor_bez_VD_1":
			dialog.text = "Ce n'est pas de l'insensibilité, capitaine, c'est la foi. Nous remettons le sort de la fillette non au hasard, mais entre les mains de Dieu. Si Thomas prie, croit et attend humblement, j'ai foi que le Seigneur entendra nos prières et lui accordera la guérison.";
			link.l1 = "Vous savez que même la noblesse de cette île, y compris le gouverneur, a eu recours aux services de la gitane. Et ils n'ont pas été excommuniés. Pourquoi êtes-vous si catégorique dans le cas de Thomas ?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;
		
		case "dwh_pastor_bez_VD_2":
			dialog.text = "Je le sais bien, mon fils. Mais eux sont des âmes égarées, n'ayant pas trouvé la lumière du Seigneur. Thomas, en revanche, est un pilier de notre communauté. Laisser le malin saper sa foi serait un coup porté à toute l'Église, ce que je ne peux tolérer.";
			link.l1 = "Alors vous refusez de donner ne serait-ce qu'une petite chance ? Est-ce vraiment le chemin juste ?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;
		
		case "dwh_pastor_bez_VD_3":
			dialog.text = "Ce que vous appelez un salut peut être une voie directe vers la perdition. Je le sais par expérience. Jadis, contre ma volonté, une telle guérisseuse a soigné ma nièce. Une petite fille morte dans d'atroces souffrances, et seul Dieu sait si ces rituels païens n'ont pas damné son âme à jamais. Inutile d'essayer de me convaincre.";
			link.l1 = "Très bien. Si c'est votre décision finale, je ne discuterai pas. Que Dieu vous garde.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;
		
		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddQuestRecord("DWH", "4");
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "dwh_pastor_VD_5":
			dialog.text = "Parfait, mon fils. Une nouvelle cloche sera le symbole de sa dévotion envers Dieu et l'Église. Qu'il fasse ce qu'il doit faire, mais qu'il se souvienne : l'œil du Très-Haut veille sur chacun de ses actes, et rien n'échappe à Sa volonté.";
			link.l1 = "Ainsi soit-il, mon père. Au revoir.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
