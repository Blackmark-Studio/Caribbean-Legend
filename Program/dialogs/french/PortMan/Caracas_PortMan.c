// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions ?","Que veux-tu, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"...","Vous avez parlé d'une question pour la troisième fois aujourd'hui...","Écoutez, si vous n'avez rien à me dire sur les affaires du port, alors ne me dérangez pas avec vos questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire."),"Peu importe.","En effet, déjà la troisième fois...","Désolé, mais je ne suis pas intéressé par les affaires du port pour l'instant.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "Le fait est que je vais me rendre à Porto Bello d'ici peu avec une cargaison de marchandises achetées chez vous dans la colonie. Je me suis dit : peut-être avez-vous quelque fret ou affaire que je pourrais accomplir en route... Pour un prix, bien sûr.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Bonjour encore. J'ai livré votre lettre à Porto Bello. Là-bas, on m'a demandé de vous donner une réponse.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Bonjour. Je viens de Porto Bello. Votre collègue de l'autorité portuaire locale m'a demandé de vous remettre cette lettre.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Merci de votre sollicitude, mais je n'ai pas de tels cas. Il y avait en fait une mission, mais vous êtes arrivé avec quelques jours de retard : j'ai envoyé un cotre-courrier rapide à cet effet.";
				link.l1 = "Compris... Eh bien, merci pour cela.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Je vois que vous n'avez même pas un seul navire. Vous devez être un riche marchand. Hmm ... Mais je connais tous les marchands locaux avec des escadrons de vue, mais je ne vous connais pas. Alors ne m'en voulez pas, mais je ne peux pas vous confier quoi que ce soit de sérieux.";
					link.l1 = "Compris... Eh bien, merci pour ça.";
					link.l1.go = "exit";
				}
				else
				{
					if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hmm... J'ai une tâche. Seulement, ton navire ne convient pas. J'ai besoin d'un navire qui soit à la fois rapide et puissant, et le tien ne répond pas entièrement à ces exigences. Du moins pas en même temps. Alors, je te prie de m'excuser.";
						link.l1 = "Compris... Eh bien, merci pour cela.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "J'ai quelque chose à faire... Et tu as un bon navire. Il ne ressemble tout simplement pas à un navire marchand. Et, autant que je peux voir, tu n'as pas de licence à long terme de la Compagnie néerlandaise des Indes occidentales. Ne te vexe pas, mais tu ne me sembles pas être un marchand. Je ne peux pas prendre ce risque.";
							link.l1 = "Compris... Eh bien, merci pour ça.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "J'ai quelque chose à faire... Et tu as un bon navire. Seulement maintenant, je ne comprends pas ce que tu vas échanger... Tu as dit que tu allais à Porto Bello pour vendre des marchandises, mais, autant que je sache, tu ne les as pas achetées chez nous dans la colonie. Ne te vexe pas, mais tu n'as pas l'air d'un marchand. Je ne peux pas prendre ce risque.";
								link.l1 = "Compris... Eh bien, merci pour cela.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "J'ai quelque chose à faire. Bien sûr, je ne vous connais pas... Mais, pour être honnête, je ne me souviens que des marchands avec des escadrons à leurs noms. Le reste - non. Oui, et vous avez une licence à long terme, on voit tout de suite un marchand expérimenté. Votre navire, cependant, est intéressant. Pourquoi échangeriez-vous sur une frégate ?";
								link.l1 = "Hah, ce n'est pas une frégate ordinaire. Elle peut atteindre une très grande vitesse même avec une cale pleine. Il est toujours plus facile de s'échapper des pirates que de les combattre, n'est-ce pas ? Bien que mon navire ait une capacité moindre que les navires marchands ordinaires, le risque est bien moindre.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Hmm, mais tu as raison ! Les Espagnols savent construire des navires, n'est-ce pas ? Oui, oui, j'ai immédiatement vu que ce beau vaisseau avait quitté les chantiers de nos arsenaux. Et oui, on m'a en effet dit aujourd'hui que tu avais acheté un lot de café et de cacao à notre marchand pour le revendre à Porto Bello. Bonne affaire, je te le dis. Les gens qui ne connaissent rien au commerce ne savent pas que ces marchandises sont bon marché ici, grâce aux plantations, et à Porto Bello, elles sont en grande demande, car de là elles partent pour la métropole.";
			link.l1 = "Eh bien, c'est de cela qu'il s'agit, señor. Pour quelques pesos, je ne pousserais pas mon bateau aussi loin.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Eh bien, pour te dire la vérité, j'ai effectivement une affaire pour toi. Et c'est très bien que tu aies un navire si rapide, qui peut aussi riposter en cas d'urgence.";
			link.l1 = "Attendez, señor... Votre cas suggère que je dois me battre...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Non, non ! En fait, ma tâche est aussi simple que possible. J'ai besoin que vous livriez une lettre à l'Autorité Portuaire de Porto Bello. La lettre est scellée et ne peut être ouverte. Personne n'a besoin d'en parler non plus, correspondance... personnelle. Remettez-la en main propre. Le délai est de dix jours. Après cela, elle sera sans importance.";
			link.l1 = "Si simple ? Et combien vais-je recevoir pour cela ?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Cinq mille pesos. Considérez cela pour ne pas avoir à envoyer un lougre courrier à Porto Bello.";
			link.l1 = "Et quelles etaient vos questions a mon sujet et celui de mon navire ?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Laisse tomber. C'est juste que la correspondance est suffisamment importante, et je dois être sûr qu'elle atteindra le destinataire. Et donc rien de spécial. Bureaucratie... Pour une personne ordinaire, ces documents n'ont aucun intérêt.";
			link.l1 = "Eh bien, je suis d'accord. Faisons en sorte que vos papiers soient ici. Dès que j'arriverai à Porto Bello, je les apporterai à votre collègue. Je m'en sortirai en dix jours, ne vous inquiétez pas.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Une seconde. Je suis désolé, j'ai complètement oublié votre nom. Pouvez-vous me le dire, s'il vous plaît ? Je dois le noter dans les documents.";
			link.l1 = "Mon nom est Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Je vous remercie. Alors... Très bien. Souvenez-vous que c'est vous qui devez livrer ce document et directement dans les mains du destinataire. Voici pour vous. La récompense vous sera remise par le chef de l'autorité portuaire à Porto Bello. Bon voyage !";
			link.l1 = "Merci ! Maintenant, excusez-moi.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Parfait ! Vous m'avez beaucoup aidé. Y a-t-il eu des difficultés ?";
			link.l1 = "Non, il n'y a pas eu de difficultés. En vérité, votre collègue vous a maudit : il a dit que vous êtes tous des radins ici, parce que vous n'envoyez pas un navire courrier, mais des marchands de passage, et en plus vous faites payer le destinataire. Il a menacé de rédiger une plainte à La Havane...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Quoi ?! Suis-je le grincheux ?! Que pensait-il de lui-même là-bas ? D'abord, garde tes cinq... non, six mille pesos ! Je pleure honnêtement !";
			link.l1 = "Merci. Il est agréable de voir que votre collègue s'est trompé dans son opinion sur vous.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "Et deuxièmement, ce gredin semble avoir oublié comment il y a deux mois, il m'a laissé toutes les dépenses pour l'entretien d'un navire marchand qui allait de Caracas à Porto Bello, et de là à La Havane ! Et nous avions convenu qu'il paierait pour la deuxième partie du voyage ! Et il n'a jamais remboursé la dette, mais a promis qu'il réglerait tout le mois dernier ! Et je suis toujours un avare... Oui, moi-même, je vais écrire une plainte contre lui à La Havane !";
			link.l1 = "Eh bien, vous avez les passions de l'arsenal de Madrid, bien sûr ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Non, à y penser ... Quel impudent ! Très bien, je vais m'occuper de lui à nouveau ... Et maintenant je vais vous demander de m'excuser : j'ai des affaires urgentes devant moi. Ce fut un plaisir de faire affaire avec vous !";
			link.l1 = "Et bonne chance à vous !";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Superbe ! Tu m'as beaucoup aidé. Bien que, j'ai envoyé un lougre-courrier chez eux, et ils m'ont renvoyé la réponse avec un navire de passage. Ouais ... Et après ça, ils se plaignent encore que nous avons des grippe-sous assis ici.";
			link.l1 = "Eh bien, peut-être qu'ils ont économisé l'argent pour le courrier ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Pas 'peut-être', mais certainement, je vous le dis ! Bon, peu importe. Tenez, prenez votre travail. Et maintenant, j'ai beaucoup de travail, excusez-moi.";
			link.l1 = "Eh bien, peut-être qu'ils ont épargné de l'argent pour le courrier ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
