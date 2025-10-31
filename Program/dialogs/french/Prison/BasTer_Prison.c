// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parle, je t'écoute.";
			link.l1 = "Je me suis trompé. Adieu.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "Il y a un Indien en état d'arrestation. Il a été capturé par Fadey le Moscovite. Puis-je lui parler ?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Dis-moi, vas-tu vraiment pendre cet Indien? N'est-ce pas trop sévère comme punition pour un si petit crime?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "C'est encore moi, commandant. Fadey le Moscovite a rédigé cette pétition pour libérer l'Indien. La voici.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Je viens à vous à la demande du propriétaire du magasin local, il s'appelle "+pchar.questTemp.Shadowtrader.Tradername+"Il m'a demandé de vous remettre cette lettre.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "C'est encore moi. J'ai des preuves substantielles que "+pchar.questTemp.Shadowtrader.Tradername+"a raison.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Je cherche un homme du nom de Longway. J'ai entendu dire que vous le cherchez aussi, Monsieur l'Officier. Avez-vous eu de la chance à le trouver, ou peut-être des pistes ?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, Fadey vous a raconté son histoire ? Je n'ai aucune raison de vous interdire de le voir, monsieur. Vous n'êtes pas le premier à venir voir ce peau-rouge. Eh bien, dans dix jours, chaque citoyen pourra le voir quand nous le pendrons à sécher au soleil...";
			link.l1 = "Alors puis-je entrer dans la prison ?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Comme je te l'ai déjà dit 'Je n'ai aucune raison de te l'interdire'. Va-t'en.";
			link.l1 = "Merci !";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Vous êtes nouveau ici, n'est-ce pas, monsieur ? Directement d'Europe ? Vous ne comprenez pas la situation dans les colonies. Cette exécution sera une leçon pour ces sauvages de peaux-rouges qui oseraient s'en prendre aux biens des colons français. En outre, Fadey lui-même insiste là-dessus et c'est un homme très respecté ici et un proche ami de notre gouverneur.";
			link.l1 = "Y a-t-il un moyen d'adoucir la punition ? Je pense toujours que c'est trop sévère...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Oh, ne te lance pas dans la philosophie ! Va voir Fadey et demande ce Indien si tu te soucies tant de son sort. Si Fadey écrit une pétition pour sa libération, nous la satisferons.";
			link.l1 = "Compris, officier. J'irai voir Fadey.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(lecture) Hum... Ce Fadey est étrange... Il a exigé une exécution démonstrative et maintenant il demande de libérer cet Indien... Peu importe, je suppose que tous les amis du gouverneur sont comme lui. Bien, vous pouvez y aller et prendre ce peau-rouge.";
			link.l1 = "Merci, officier !";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Encore ça "+pchar.questTemp.Shadowtrader.Tradername+" avec ses plaintes ! Très bien, voyons voir ce que c'est cette fois-ci... (lit à travers)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Encore une fois, des suppositions absurdes et pas une seule preuve solide ! Très bien. Dites-lui que cela ne suffit tout simplement pas pour que j'alerte les gardes et leur ordonne de fouiller la ville.";
			link.l1 = "Tu veux que je lui dise ça ?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Exactement - et, de préférence, mot pour mot. Il comprendra ce que je veux dire. Je ne vais pas gaspiller du papier pour répondre à cet agaçant.";
			link.l1 = "Je vois. Adieu, alors.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "Et quelles sont ces 'preuves substantielles' que vous prétendez avoir rassemblées ?";
			link.l1 = "J'ai conclu un accord avec les contrebandiers concernant l'achat de marchandises par leur magasin non officiel. Leur agent viendra ce soir au bureau de l'autorité portuaire pour m'emmener à leur soi-disant 'magasin'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hhm... Eh bien, excellent travail, capitaine ! Ensuite, nous agirons. Nous enverrons notre homme à leur réunion, localiserons leur repaire et arrêterons tous. Merci pour votre initiative !";
			link.l1 = "Toujours heureux d'aider. Je suis sûr que votre opération sera couronnée de succès.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Qui ? Long... Way ? Je ne me souviens pas d'Anglais dans notre ville récemment.";
			link.l1 = "Non, Longway est... Chinois.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Eh bien, eh bien. Et pourquoi cherchez-vous ce Longway à vous, monsieur ?";
			link.l1 = "C'est un ami à moi. J'ai déjà entendu parler de ce qui s'est passé - c'est un triste malentendu, je vous assure.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Je le cherche parce que c'est un criminel notoire dans l'Archipel.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ah, un malentendu. Nous ne cherchions pas à le remettre à sa place sur-le-champ, loin de là. Nous voulions simplement lui parler... pour commencer. Cependant, cet homme enragé de chez vous n'a pas seulement décimé plusieurs gardes de la ville, mais a aussi massacré les unités envoyées pour le pourchasser dans la jungle.";
			link.l1 = "Prévoyez-vous d'envoyer une autre unité ? Je pourrais accompagner vos hommes, lui parler, le calmer et empêcher un autre désastre. Serait-ce suffisant si les meurtres cessaient et que Longway quittait la ville pour de bon ?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "En temps normal, je pourrais être d'accord avec vous. Mais vous voyez, l'un des tués était un officier - un jeune lieutenant prometteur, le favori de Sa Grâce. La ville est en deuil. On ne peut pas fermer les yeux ou compenser cela. Vous comprenez ?";
			link.l1 = "Je comprends parfaitement. Je m'excuse pour les actions de mon ami. Je ne vous importunerai plus.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Vous savez, Dieu seul sait ce qui se passe dans la jungle. N'importe qui aurait pu tuer ces hommes.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "Et qui pensez-vous pourrait avoir abattu toute une escouade de patrouilleurs dirigée par un officier ?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Digne de confiance) Des bandits, qui d'autre ? J'ai honte de l'admettre, mais j'ai à peine échappé à une grosse bande récemment.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Mais comment pourrais-je savoir ? Cela aurait pu être n'importe qui - brigands, pirates, espions...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Hé, ce n'est pas surprenant - vu votre carrure, Capitaine. Oui, nous avons de tels vauriens sur l'île ces temps-ci...";
			link.l1 = "Exactement ! Alors, ils auraient pu massacrer la patrouille et le pauvre sous-lieutenant.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Malheureusement, c'est tout à fait possible.";
			link.l1 = "Précisément. Donc, une fois de plus, je vous demande de me laisser rejoindre la prochaine équipe de recherche - Longway m'écoutera, et ainsi nous pourrons éviter d'autres morts.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "D'accord. Mais il y a encore un 'mais', monsieur.";
			link.l1 = "Et qu'est-ce que c'est ?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "Contrairement à ce qui s'est passé dans la jungle, la culpabilité de votre ami en ville est claire et entièrement prouvée. Cela ne restera pas impuni. Ainsi, ces morts doivent être compensées si vous voulez qu'il quitte la ville vivant.";
			link.l1 = "D'accord. Combien cela coûtera-t-il, Monsieur l'Officier ?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Trois cents doublons. Cet argent ira à la ville, pas aux marchands de la place du marché.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Bien sûr. Trois cents doublons - les voilà.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Je n'ai pas apporté mes doublons en ville cette fois-ci. Mais si vous me laissez les récupérer...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Excellent. Vous avez prouvé votre responsabilité. Nous finalisons le briefing pour la prochaine escouade. Je vous autorise à vous y joindre.";
			link.l1 = "Merci. Au revoir, Monsieur l'Officier.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Je ne suis pas né de la dernière pluie. Je sais que tu comptes t'enfuir - pas pour des doublons, mais pour ton cher Chinois.";
			link.l1 = "Je vous donne ma parole que je ne quitterai pas la ville avec Longway.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Mots, mots... Je suis fatigué de tes bavardages, Capitaine. Tu n'iras nulle part tant que nous n'aurons pas attrapé ce foutu homme à la peau jaune nous-mêmes.";
			link.l1 = "J'obéirai à votre ordre si vous promettez de ne pas tuer Longway sur-le-champ, Monsieur l'Officier.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Mais ai-je personnellement violé les lois de la ville aujourd'hui ?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Alors tu ne sais pas. Je vais m'en tenir à mon intuition actuelle - le Chinois doit être attrapé, quoi qu'il en soit.";
			link.l1 = "Votre intuition actuelle ? Mais vous n'avez aucune preuve que Longway a tué tout le monde dans la jungle.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "Et avez-vous une preuve de son innocence? Non? Alors arrêtez de faire de votre homme à la peau jaune un saint. Me comprenez-vous?";
			link.l1 = "Je comprends parfaitement. Je m'excuse pour les actes de mon ami. Je ne vous importunerai plus.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Je crains de ne pas pouvoir vous laisser partir tout de suite, Capitaine.";
			link.l1 = "Que veux-tu dire ?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "Ce que je veux dire, c'est que puisque ce Longway est ton ami, il n'y a aucune garantie que tu ne courras pas après lui pour essayer de t'échapper avec lui. Donc, je devrai te retenir jusqu'à ce que nous attrapions ce boucher à la peau jaune nous-mêmes.";
			link.l1 = "J'obéirai à votre ordre si vous promettez de ne pas tuer Longway sur-le-champ, Monsieur l'Officier.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Mais ai-je personnellement enfreint les lois de la ville aujourd'hui ?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Je ne peux rien promettre. Qui sait ce que votre ami a en tête, ou s'il ne va pas déclencher un autre massacre en nous voyant. En attendant, profitez de vos luxueuses commodités, Capitaine.";
			link.l1 = "Hilarant...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Comprenez, je n'ai rien contre vous personnellement. Et vous avez raison - vous n'avez commis aucun crime. Mais nous devons nous assurer que votre ami à la peau jaune ne s'échappe pas de la justice.";
			link.l1 = "Alors comprenez que je ne me laisserai pas détenir de manière aussi ridicule.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "Dans ce cas, nous devrons vous faire taire, monsieur.";
			}
			else
			{
				dialog.text = "J'en ai assez de tout cela ! Sergent, conduisez l'escouade jusqu'à cette maudite grotte et trouvez les Chinois ! Je m'occuperai personnellement de celui-ci...";
			}
			link.l1 = "En enfer, tu iras.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Un chasseur de primes, hein ? D'habitude, je n'aime pas traiter avec votre espèce, mais dans ce cas, c'est à mon avantage que nos intérêts convergent. Apparemment, ce jaune est un tueur infâme. Il a assassiné beaucoup de mes hommes, tant en ville que dans la jungle.";
			link.l1 = "Je le poursuis à travers l'Archipel depuis un certain temps maintenant.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Chien de satan ! Voici ce que nous allons faire : je vais rassembler une autre escouade, et tu iras avec eux. Cette fois, il n'a nulle part où fuir, et avec ton aide, nous aurons de meilleures chances de succès. N'attends pas de récompense de ma part, toutefois - tu es un chasseur de primes, donc ton paiement viendra de celui qui t'a engagé. Tu devrais être reconnaissant que je te permette de coopérer avec moi.";
			link.l1 = "C'est bien vrai. À plus tard, officier. Si un de vos hommes survit à une autre rencontre avec notre ami chinois, je vous ferai savoir comment ça s'est passé.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Tu as raison. Vous vous connaissez, je suppose ? Qui êtes-vous l'un pour l'autre ?";
			link.l1 = " C'est un officier de navigation sur mon navire, et...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Je le cherche parce qu'il est un criminel notoire dans l'Archipel.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "Il est meilleur avec les armes qu'avec les cartes. As-tu la moindre idée de ce que ton Chinois de compagnie a fait ?";
			link.l1 = "Pour être honnête, non, car je viens d'arriver et de commencer mes recherches. Je suis sûr que tout cela n'était qu'un malentendu.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Exactement. Qui es-tu pour lui si tu le veux tant? Peu importe - ce qui compte, c'est le but de ta visite en ville.";
			link.l1 = "Rien d'illégal, monsieur. Mais qu'entendiez-vous par « ça n'a plus d'importance » ? Est-ce qu'il...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Oui. Il a été enterré derrière l'une des collines, à une certaine distance du cimetière. Les saints pères n'ont pas permis un enterrement chrétien pour un païen.";
			link.l1 = "Comment cela est-il arrivé, si ce n'est pas un secret ?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Très simplement - il est arrivé en ville, reniflant partout sans fin. Nous avons essayé de lui parler, de découvrir ce qu'il faisait ici, mais il a tué quelques hommes et s'est enfui dans la jungle. J'ai envoyé plusieurs équipes de recherche après lui, l'une après l'autre, mais il les a toutes anéanties ! Nous avons dû le piéger dans une grotte, et les tireurs d'élite ont fait le reste.";
			link.l1 = "Et tu ne sais pas ce qu'il cherchait ? Tu vois, il n'avait jamais fait quelque chose comme ça auparavant - il était navigateur sur mon navire. Mais ensuite, il m'a volé et s'est enfui.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Ça m'est juste sorti de l'esprit, aye. Alors, vous avez souffert de ses actes aussi ? Ça vous servira de leçon, Capitaine. Vous saurez mieux que de vous allier à quelqu'un en qui vous ne pouvez pas avoir confiance. Ne faites jamais confiance à un homme à la peau jaune - retenez bien mes paroles !";
			link.l1 = "Oui, je garderai cela à l'esprit. As-tu trouvé quelque chose sur lui?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Oh, vous voulez récupérer les marchandises volées ? Il avait de l'argent dans ses poches, donc s'il vous a volé, il a déjà tout dépensé. Et il y avait d'autres papiers... de votre journal de bord ? Nous n'avons pas compris de toute façon - une sorte de code, peut-être ? Tout était couvert de sang, donc nous n'avons pas pu distinguer les parties intactes.";
			link.l1 = "Er, oui. Merci. Je me suis toujours inquiété de ce qui arriverait si mes journaux et carnets étaient trouvés par quelqu'un d'autre...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "Et devoir inventer un chiffre complexe à cause de cela ? N'avez-vous pas regretté votre temps et vos efforts ? Voilà. Et pour l'argent - ne soyez pas en colère, mais nous l'avons rendu à la ville. Ce Chinetoque a mis beaucoup de mes hommes sous terre ce jour-là.";
			link.l1 = "Alors je n'ose insister. Adieu.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
