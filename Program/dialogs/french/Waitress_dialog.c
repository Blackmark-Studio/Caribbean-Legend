// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "Que désirez-vous, monsieur? Je suis désolé, je suis juste... 'sanglote'... oh... Je suis désolé.";
					link.l1 = "Pourquoi es-tu si bouleversée, madame? Des larmes sur un si joli visage? Qu'est-ce qui s'est passé?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = "Monsieur! Monsieur, aidez! Assassiner!";
				link.l1 = "Hein? Assassiner qui? Où? Est-ce une plaisanterie, ma chère?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+" ! Quel plaisir de te revoir... Merci d'être passé... mais ce n’est peut-être pas le meilleur moment pour discuter. Reviens quand tu seras seul. Nous pourrons alors aborder... des sujets plus personnels.";
							link.l1 = "Toujours un plaisir de bavarder, mais je dois y aller. Peut-être à une prochaine fois.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Je commençais à croire que tu avais oublié le chemin de notre taverne. Dommage que tu ne sois pas seul. J’espérais que nous pourrions parler en privé.";
							link.l1 = "Je pense que le destin nous offrira encore une occasion de discuter en tête-à-tête.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+" ! Je savais que tu ne me laisserais pas languir trop longtemps. Je ne veux plus perdre une minute. La chambre à l’étage est libre... rien que pour nous. Tu ne vas quand même pas me dire non ?";
							link.l1 = "Tu sais comment m’attirer dans tes filets... Eh bien, je n’ai aucune raison de résister. On y va ?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "J’ai bien peur d’avoir des affaires importantes à régler aujourd’hui. Mais je te promets que je me rattraperai la prochaine fois.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+" ! Je commençais à penser que tu prenais plaisir à me faire attendre. Tu ne comptes tout de même pas rester planté là comme une statue, alors qu’il y a tant de manières plus agréables de passer le temps ?";
							link.l1 = "Impossible de résister à ton charme... Je ne vais pas perdre une seconde – je monte tout de suite.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Tu sais comment séduire, Betsy... Mais hélas, je dois être ailleurs pour l’instant.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Je voudrais te poser quelques questions.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Je vous ai demandé de monter à l'étage. Ne restez pas ici et n'attirez pas l'attention.";
					link.l1 = "D'accord, je pars, je ne veux pas vous compromettre...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Je suis nouveau ici, alors s'il vous plaît, ne me dérangez pas pendant mon travail. Je ne m'y suis toujours pas habitué...";
					link.l1 = "Et où est la serveuse qui travaillait ici avant vous ? "+pchar.questTemp.different.FackWaitress.Name+", comme je me souviens...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Reviens encore, chérie. Nous pourrions nous amuser à nouveau. Si j'avais plus de temps libre...";
					link.l1 = "Bien sûr que je le ferai, tu étais formidable !";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Je ne te connais pas, alors ne me dérange pas...";
					link.l1 = "Où est mon argent?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Désolé, "+GetSexPhrase("beau","joli")+", Je suis trop occupé maintenant. C'est un bon moment pour la taverne mais pas pour les discussions!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "S'il vous plaît, capitaine, ne combattez pas ici ! C'est un dur travail de nettoyer cet endroit.";
					link.l1 = ""+GetSexPhrase("Hm... Je n'allais même pas le faire.","Est-ce que je ressemble à une ivrogne cherchant la bagarre ? Je suis juste une fille, comme toi, ne t'inquiète pas.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("Oh, capitaine! Voudriez-vous partager un lit avec moi aujourd'hui? Je n'aime pas me vanter mais...","Prenez place, capitaine. C'est toujours un plaisir de rencontrer un vrai loup de mer comme vous.")+"";
						link.l1 = "Dommage que je sois pressé maintenant. La prochaine fois!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Avec un grand plaisir, bebe!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Prenez place, capitaine. Goutez à notre rhum, jouez une partie de cartes ou de dés. Sentez-vous comme à la maison! C'est toujours un plaisir de rencontrer un véritable loup de mer comme vous.";
						link.l1 = "Merci, jolie.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Parlez au maître si vous voulez commander quelque chose. Il est derrière le comptoir du bar.";
					link.l1 = "Merci pour le conseil.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Si vous voulez vous reposer et soigner votre santé - louez-vous une chambre alors. Passer toute la nuit dans la salle ne vous aidera pas beaucoup.";
					link.l1 = "Mes remerciements.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Je veux te poser quelques questions.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Ecoute donc. Loue une chambre ici dans la taverne. Va là-bas et attends-moi. Je vais m'y faufiler un peu plus tard...";
			link.l1 = "Ha ! Je vais le faire, chérie ! Je t'attendrai !";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Elle ne travaille plus ici, elle est à la retraite... Je suis désolé, j'ai du travail à faire.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Ecoute bien, idiot lubrique. Je ne sais pas où est ton argent ! Et si tu continues à me presser, j'appellerai les gardes et tu te retrouveras en prison !";
			link.l1 = "D'accord, pas besoin de gardes... Quel idiot...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Exactement, quel sot. La prochaine fois tu seras plus intelligent et plus décent.";
			link.l1 = "Je vais essayer... (chuchotant) Putain de pute...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Pouvez-vous m'entendre?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Vous vous sentez mal ? Vous avez mal à la tête ?";
			link.l1 = "Sacrebleu... où suis-je?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Tu ne te souviens pas? Ils t'ont volé.";
			link.l1 = "Quoi? Oh... Ma tête... Qui oserait?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Comment devrais-je le savoir? Ils ont déboulé, menacé de tuer, fouillé vos poches et sont partis.";
			link.l2 = "Je vois... Merde... J'aimerais de l'eau... Merci.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "Non, ce n'est rien, senor ... merci pour votre gentillesse mais je ... (pleure)";
			link.l1 = "Quelqu'un vous a offensé? Calmez-vous, jolie, racontez-moi tout.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Non, non, monsieur, ce n'est rien. Pardonnez-moi pour mon manque de retenue, c'est juste... C'est mon frère, ils disent qu'il est mort mais je ne le crois pas. Je ne sais pas quoi croire mais je sens de tout mon coeur qu'il est en grand danger. Et je n'ai personne d'autre qu'Angelo après le décès de nos parents... (pleure)";
			link.l1 = "Je comprends, mais je vous demande de vous calmer, s'il vous plaît. Qu'est-ce qui est arrivé à votre frère?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Seigneur... ne me prenez pas mal, mais pourquoi un tel capitaine se soucierait-il d'une fille ordinaire et modeste de la taverne ? Je n'ai même rien à vous promettre pour votre aide...";
			link.l1 = "En fait, vous avez raison. L'altruisme n'est pas pour moi, alors soyez fort, nous perdons tous nos proches. C'est la vie comme on dit en France...";
			link.l1.go = "exit";
			link.l2 = "Une femme peut toujours trouver un moyen de remercier un homme.... Ha-ha. Maintenant, arrête simplement de pleurer et parle-moi de ton problème.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Jeune senorita, ne savez-vous pas que notre Eglise nous enseigne à nous entraider? J'essaierai de vous aider si je le peux, bien sûr.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "C'était un 'indice' ? Excusez-moi, c'était mon erreur de parler avec vous ! Adieu 'caballero'...";
				link.l1 = "Comme tu veux, chérie.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Eh bien alors... Au moins, tu es honnête dans tes désirs. Je promets que si tu trouves Angelo ou me dis ce qui lui est vraiment arrivé, tu obtiendras ce que tu as demandé...";
				link.l1 = "Chère senorita, c'est un plaisir de faire affaire avec vous... Passons directement à l'histoire de votre frère.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Tu plaisantes? Veux-tu vraiment m'aider sans rien demander en retour?";
			link.l1 = "Seul un mauvais homme n'aiderait pas une fille en pleurs. Ne t'inquiète pas, je veux vraiment t'aider. Que s'est-il exactement passé à Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Très bien, monsieur. Mon frère, il... oh, il n'est pas facile pour moi de retenir mes larmes, je suis tellement désolé... Nous étions vraiment pauvres à cause de ma... modestie au travail peut-être... Et Angelo a commencé à travailler avec les contrebandiers locaux. Il pensait que son petit bateau de pêche rapporterait plus d'argent en transportant quelque chose pour éviter les douanes.";
			link.l1 = "Pour le dire en des termes plus simples, ton frère est devenu un criminel, n'est-ce pas?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Non, senor, vous ne comprenez pas... il n'est pas comme ça ! Il l'a fait pour moi ! Pour me sauver de gagner de l'argent ici... vous voyez ce que je veux dire. Nous étions endettés et il l'a fait pour mon honneur et mon âme. Et puis... il a été pris. Ce n'était pas un gros problème, j'ai même emprunté plus d'argent pour payer sa libération... Mais ils ont dit qu'il était mort.";
			link.l1 = "Ils ont dit ? Qui a dit ? Et pourquoi ne les crois-tu pas ? Il est mort en prison ?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Oui. Quand j'ai apporté de l'argent pour payer sa libération, le commandant m'a dit qu'Angelo était mort de la consommation. Pensez-y! Il était arrivé en bonne santé et il est mort deux semaines plus tard juste dans ces chambres. Ils... ils ne m'ont même pas permis de voir le corps. Ils ont dit qu'ils enterraient les prisonniers juste à la baie près du fort pour éviter une épidémie.";
			link.l1 = "Une épidémie? Cela semble très vrai. Alors vous ne voulez tout simplement pas y croire ou vous avez des raisons plus sérieuses?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "Non... Non ! (en pleurant) Je sais que cela peut sembler stupide, mais je suis certaine que je saurais s'il était mort. Voyez-vous, Angelo a toujours été fort - un vrai marin. Mais il y a encore une chose\nMon grand-père est mort de la consomption quand j'étais enfant et lui, un vieil homme, l'a combattue pendant des années ! Je sais comment ça marche, la consomption ne tue pas les gens en quelques jours, croyez-moi !";
			link.l1 = "Hm... Vous m'avez fait douter aussi, quelque chose ne va pas ici. Je ne peux rien vous promettre mais j'essaierai d'en savoir plus.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Même une simple promesse est bien plus que ce à quoi je m'attendais ! Vous êtes si gentil, señor ! Je vais attendre ici !";
			link.l1 = "Oh, la jeunesse! Si inconstant dans les sentiments... voudrais-tu bien me rendre ma main, beauté, j'en ai encore besoin ha-ha... Très bien alors, je vais aller fouiller autour.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "Non, pas de plaisanteries! En haut! Deux voyous sont en train d'assassiner un noble monsieur! Aidez-le, capitaine, vous êtes le seul homme armé ici!";
			link.l1 = "Courrez dehors, appelez les gardes! Je monte à l'étage!";
			link.l1.go = "FMQP_1";
			link.l2 = "Ma chère, tu as dû me prendre pour un garde. Appelle une patrouille en cas de meurtre.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, les gardes! Aidez-moi!";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
