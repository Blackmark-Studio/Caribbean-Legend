int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Je suis heureux de te voir, mon fils. Es-tu ici pour effacer ta dette ?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Oui, père. Je le suis.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Je suis désolé pour le retard, mais je ne suis pas ici pour cela. Mais je le serai bientôt, ne t'inquiète pas.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Avez-vous besoin de quelque chose, mon fils ?";
				link.l1 = "Oui, père. J'aimerais voir mon frère, Michel de Monper. Il a dit...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Avez-vous besoin de quelque chose, mon fils ?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Bonjour, mon enfant. Je suis heureux que tu sois venu. Je voulais te parler.";
				link.l1 = ""+TimeGreeting()+", mon père. Je vous écoute.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "Je voudrais parler de mon père.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Oui, pater. J'ai besoin de votre aide. Mon nom est "+GetFullName(pchar)+"Michel de Monpe m'a conseillé de vous parler.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Oui, père. J'ai besoin de votre aide. Mon nom est "+GetFullName(pchar)+"Mon frère, Michel de Monper, m'a conseillé de vous parler.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Oui, père. J'ai besoin d'un navire pour aider Michel, mais je viens d'arriver aux Caraïbes et ma bourse est vide. Mon frère m'a dit que vous pourriez me prêter de l'argent...";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Bonjour, mon père. Nous avons besoin de votre aide — pour une affaire assez inhabituelle.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Mon père, j’ai réuni la somme. Huit cents pièces d’or.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Bonjour, mon enfant. Je suppose que tu es venu pour connaître le résultat de ton... hum, de votre affaire ?";
				link.l1 = "Toujours aussi perspicace, mon père. Ne me faites pas languir — qu’a découvert votre homme ?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Oui, père. J'ai besoin de votre aide.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Oui, père. Je le suis.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Non, rien, père.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "Qu'est-ce qui t'amène à moi, mon fils ?";
			link.l1 = "Bonjour, père. On m'a conseillé de vous parler. Je m'appelle Charles de Maure. Je cherche Michel de Monper. Autant que je sache, il devrait être quelque part en Martinique. Je suis... son frère.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Le frère de Michel de Monpe? De Maure? Comme c'est étrange...";
			link.l1 = "Je comprends vos doutes, père. Nous avons simplement des noms de famille différents. Mon père est Henri de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, je vois maintenant. Je connaissais personnellement Henri de Monper. Tourne-toi vers la lumière, jeune homme. Voilà ! Tu ressembles exactement à lui. Les mêmes traits, les mêmes caractéristiques nobles ! Je suis heureux de voir un fils d'Henri de Monper dans notre paroisse.\nEt concernant ta question, je te dirai que Michel est un officier de haut rang de l'Ordre de Malte, mais il est... en difficulté. Heureusement, l'un des chevaliers de l'Ordre me rend actuellement visite. Je crois qu'il pourrait accepter de t'accompagner auprès de ton malheureux frère, que le Seigneur ait pitié de son sort...";
			link.l1 = "Qui est cet homme, saint père ?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Mon fils, reviens demain matin. Pour le moment, je n'ai rien de plus à te dire.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Bonjour, mon fils. Comme promis, la personne dont je t'ai parlé hier est déjà ici pour t'attendre. Il est prêt à t'emmener voir ton frère qui, d'après ce que j'ai entendu, est dans une situation déplorable. Que le Seigneur ait pitié de son âme...";
			link.l1 = "Qui est cet homme, saint père ?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Oui, Charles, je suis au courant de cela. Mais je dois te décevoir. Michel n'est pas ici.";
			link.l1 = "Qu'entends-tu par il n'est pas ici ? Il a dit qu'il m'attendrait dans votre église ! Mon père, que s'est-il passé ? Où est mon frère ?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Mon fils, ton frère était ici et il a quitté mon humble tabernacle tard la nuit dernière. Où il est allé, je ne sais pas. Mais il a laissé cette lettre pour toi.";
			link.l1 = "Je n'arrive pas à y croire... après tout ce que j'ai fait pour lui ! Donne-moi cette lettre !";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Ne t'enflamme pas ainsi, Charles. Voici la lettre. Lis-la et ensuite... ensuite j'aimerais te parler. Mais d'abord, lis le message de ton frère.";
			link.l1 = "Je brûle d'impatience !";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Je vois que tu as lu la lettre. Maintenant, j'aimerais te dire quelque chose, Charles...";
				link.l1 = "Mais... comment cela se peut-il ? Quel genre de balivernes est-ce ? Je sais que mon frère est particulier, mais ce n'est pas un fou !";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Mon fils, lis la lettre. Nous parlerons plus tard.";
				link.l1 = "Oui, père...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Les actions de ton frère m'ont également surpris, Charles. J'éprouve encore des moments de perplexité. Un serviteur loyal de l'Ordre et de la Trinité, et il se comporte comme un déserteur.";
			link.l1 = "As-tu la moindre idée des raisons d'un tel comportement étrange ?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Hélas, je ne le sais pas. Mais je suppose qu'il a ses propres motifs, des motifs profonds. Renoncer à tout son passé suggérerait une raison extrêmement significative. Je ne peux même pas imaginer ce que cela pourrait être. Mais je sens que cela implique quelque chose d'extrêmement mauvais... voire terrible.";
			link.l1 = "Que pourrait-ce être, père ?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Mon fils, un prêtre ne voit pas avec ses yeux, mais avec son cœur. Je ne peux pas te l'expliquer avec des mots, mais... ton frère s'est engagé dans quelque chose d'impur, de sale. Je n'aurais jamais pensé que ma bouche pourrait prononcer cela. Cependant...";
			link.l1 = "Eh bien, je ne doute pas que mon frère ait prévu quelque chose de louche. Je peux même deviner exactement ce qu'il projette de faire. Ce 'quelque chose' implique quelque chose de jaune et produit un joli bruit de tintement.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Je ne pense pas que la soif de l'or soit ce qui pousse ton frère. Je dirais qu'il a besoin de quelque chose de plus grand.";
			link.l1 = "J'ai beaucoup appris de Michel et j'ai saisi sa philosophie, donc je pense pouvoir deviner ce qui est important pour lui et ce qui ne l'est pas. Mais je garderai vos précieux conseils à l'esprit, père.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Que Dieu te bénisse, mon fils. Va, va maintenant. Que le Seigneur veille sur toi !";
			link.l1 = "Merci, père. Adieu !";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Le frère de Michel de Monpe? De Maure? Comme c'est étrange...";
			link.l1 = "Je comprends vos doutes, père. Nous avons simplement des noms de famille différents. Mon père est Henri de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, je vois maintenant. Je connaissais personnellement Henri de Monper. Tournez-vous vers la lumière, jeune homme... Voilà ! Vous lui ressemblez. Même apparence, même profil noble ! Je suis heureux de voir un fils d'Henri de Monper dans notre paroisse.\nJ'ai déjà entendu dire que Michel a été visité par un homme, arrivé d'Europe, mais je n'aurais jamais imaginé que c'était son propre frère. J'espère que vous pourrez aider Michel, il traverse une période difficile. Quoi qu'il en soit, comment puis-je être à votre service ?";
			link.l1 = "Michel m'a dit que tu pourrais m'aider si jamais j'avais des ennuis avec les autorités.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "C'est ce que Michel vous a dit ? Je vois. Eh bien, je peux vous aider dans de telles affaires. J'ai une certaine influence au sein de l'Église romaine et des colonies néerlandaises. Par conséquent, je pourrais être en mesure d'intercéder entre vous et les autorités espagnoles ainsi que néerlandaises. Certes, je ne pourrai pas faire grand-chose si votre inconduite est devenue trop importante - dans ce cas, seule une petite atténuation peut être obtenue.\nIl faudra plusieurs intercessions pour une réconciliation complète. De plus, dans tous les cas, vous devrez me fournir des doublons d'or pour les œuvres de charité et les dépenses de voyage. En outre, je ne peux vous aider qu'avec une nation à la fois. Si vous trouvez ces conditions acceptables, n'hésitez pas à vous tourner vers moi, et nous verrons ce qui peut être fait.";
			link.l1 = "Merci ! Je garderai cela à l'esprit.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Que puis-je faire pour vous, mon fils ? Parlez, je vous écoute.";
			link.l1 = "Michel m'a dit que tu pourrais m'aider si jamais j'avais des ennuis avec les autorités.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Comment puis-je t'aider, mon fils ?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Revenons à la question du paiement pour la livraison des ordres.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "Je veux envoyer un ordre...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Je suis tombé dans des ennuis avec les autorités espagnoles.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Je me suis attiré des ennuis avec les autorités néerlandaises.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Désolé, je pense que je vais m'occuper des choses moi-même cette fois.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Alors, les nobles seigneurs sont impatients de vous mettre dans les cachots de La Havane...";
			link.l1 = "Exactement, père...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Alors, les marchands astucieux sont impatients de te jeter dans les cachots de Willemstad...";
			link.l1 = "Exactement ainsi, père...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Oui, ces rumeurs sont parvenues jusqu'à notre église aussi. Je peux vous aider avec votre dilemme. C'est quelque chose qui peut être résolu. J'ai besoin de deux " + sTemp + " d'or pour arranger votre situation.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Super ! Voici l'or.";
					link.l1.go = "agree";
				}
				link.l2 = "Alors c'est le moment idéal pour moi de trouver les doublons.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Oui, des rumeurs sur tes 'exploits' sont parvenues jusqu'à notre église aussi. Tu as terni ta réputation, mon fils. Tu devrais être plus prudent. Mais je peux t'aider. J'ai besoin de " + sTemp + " d'or pour arranger ta situation.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Superbe ! Voici l'or.";
						link.l1.go = "agree";
					}
					link.l2 = "Alors, c'est le moment idéal pour moi de trouver les doublons.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Oui, mon fils. Tu es tout aussi désespéré que ton frère... C'est probablement un trait de famille. Je ne peux pas complètement corriger la situation, mais néanmoins, je crois que je peux atténuer ton sombre sort. Et plus tard, nous pourrons faire d'autres offrandes si tu le souhaites. J'ai besoin de " + sTemp + " d'or pour l'instant et je commencerai à résoudre ton dilemme immédiatement.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Superbe ! Voici l'or.";
						link.l1.go = "agree";
					}
					link.l2 = "Alors c'est le bon moment pour moi de trouver les doublons.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Maintenant, vous devrez attendre au moins deux semaines. Je pense qu'au cours de ce temps, je pourrai rencontrer et discuter avec les bonnes personnes.";
			link.l1 = "Merci, père ! Je vais attendre...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure ? Et vous êtes le frère de Michel de Monper ? Étrange...";
			link.l1 = "Je comprends vos doutes, padre. Mon père est Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, je vois. Je connaissais personnellement Henri de Monper. Tournez-vous vers la lumière, jeune homme. Oui! Les mêmes yeux, les mêmes traits nobles! Je suis heureux de voir un fils d'Henri de Monper dans mon église. J'espère que vous pourrez aider votre frère. Il a eu beaucoup de malchance récemment.";
			link.l1 = "Oui, pater. J'ai besoin d'un navire pour aider Michel, mais je viens à peine d'arriver aux Caraïbes et ma bourse est vide. Mon frère m'a dit que vous pouviez me prêter un peu d'argent...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel te l'a dit ?";
			link.l1 = "Père, je n'ai peut-être pas l'air très digne de confiance, mais c'est la vérité. Plus tôt j'aurai un navire, plus tôt je pourrai sortir mon frère de prison.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Je vois, mon fils. Je peux entendre que tu dis la vérité. Eh bien, pour l'amour de Michel et de ton père, je vais t'aider. J'ai quelques économies, prends-les. Je suppose que 50 000 pesos et 100 doublons suffiront.";
			link.l1 = "Merci, padre. Quels sont les termes ?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Aucune pression. Six mois pour le remboursement suffiront.";
			link.l1 = "Très bien, saint père. Merci encore !";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Va avec mes bénédictions, mon fils.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Splendide, mon fils. J'espère que cet argent t'a été utile.";
			link.l1 = "En effet, c'est arrivé! Merci!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, je n'en crois pas mes yeux ! Qu'est-ce qui t'amène ici ?!";
			link.l1 = "Bénissez-moi, Saint Père, car j'apporte de bonnes nouvelles - je vais me marier, et je souhaiterais vous voir comme le prêtre de mon mariage.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Mon fils, c'est merveilleux ! Alors tu as reçu cette lettre de ton père et tu as décidé, comme d'habitude, d'agir selon ta propre compréhension ? Je suis sincèrement heureux pour toi ! Mais j'ai bien peur de ne pouvoir t'aider à moins que tu ne décides de te marier dans cette église ici.";
			link.l1 = "Je comprends que votre mission est dans une impasse, Saint Père ? Puis-je vous aider en quoi que ce soit ? Puisque le mariage aura lieu dans une chapelle espagnole, bien sûr, c'est une aventure que j'aimerais entreprendre, mais je suis déterminé à tenir la célébration en Martinique. Modérément magnifique, et en présence de témoins respectables et d'invités honorables.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "Je suis désolé, mon fils, mais toute ton autorité ne vaut rien face à l'entêtement des plus hauts hiérarques de l'Église catholique, surtout dans les colonies espagnoles. Nous n'avons pas trouvé d'accord sur la question du partage de l'influence des missions catholiques entre nos pays, et me voilà ici, en tant qu'invité d'honneur et otage d'honneur. Les Espagnols attendent une meilleure offre de notre part. J'ai envoyé un message en Europe, en espérant que la réponse viendra d'ici deux mois et que nous pourrons reprendre les négociations. Si elle n'est pas encore arrivée dans deux mois, elle sera certainement là dans les six prochains mois. \nEt oui, bien que le Pape et Mazarin soient parvenus à un compromis ces dernières semaines, il est trop tôt pour parler d'une véritable relation chaleureuse. Honnêtement, je ne suis pas sûr que nous parviendrons jamais à un quelconque accord. Il me semble que Palotti me garde simplement comme un argument dans ses propres jeux de pouvoir politiques. Cependant, je dois dire que l'inquisiteur a un excellent café !";
			link.l1 = "Je n'ai ni six mois ni deux mois ! Je dois accomplir le souhait de mon père, sinon il me forcera à me marier sans mon consentement. Et sa santé n'est plus ce qu'elle était, pourtant j'aimerais avoir le temps de lui présenter celle que j'ai choisie et la future dame de Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "J'ai bien peur que tu doives trouver un autre prêtre pour ton mariage alors, mon fils. Hélas, je resterai ici longtemps.";
			link.l1 = "Que dirais-tu si je te séparais du café de l'inquisiteur ?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "J'accepterais volontiers votre aide. Je soupçonne que je n'ai pas été choisi pour cette mission par hasard. Dans le pire des cas, ils oublieront simplement le père Benoit. Et, bien que le Seigneur m'ait commandé de supporter, je suis accablé par ma conclusion, malgré toutes ses... bénédictions. Mais, je le répète - il est peu probable que le père Palotti écoute vos demandes.";
			link.l1 = "Alors je vais me faire gagner du temps et je ne vais pas essayer de le convaincre. Nous quitterons simplement l'église dès que le service sera terminé et nous nous rendrons à mon navire. N'hésitez pas, Saint Père - ils ont vu notre rencontre et ils me reconnaîtront, et ce sera beaucoup plus difficile de vous aider si je dois vous sortir du manoir du gouverneur.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "C'est risqué, mon fils, très risqué. Un groupe de gardes m'attend dehors pour m'escorter jusqu'au manoir, et la ville est pleine de soldats.";
			link.l1 = "Nous allons jouer la carte de la surprise, Père Benoît. Il suffit de me faire confiance et tout ira bien. J'ai... une certaine expérience en la matière.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Comme tu veux. Mais s'il te plaît, fais-le sans effusion de sang inutile ! J'ai déjà eu des expériences de ce genre aussi... Guide-nous, mon fils. Je suis juste derrière toi. Mais je ne prendrai pas les armes, alors ne le demande même pas.";
			link.l1 = "«Je n'y ai même pas pensé, Père. Je peux m'en occuper. Suivez-moi, mais soyez prudent, ils pourraient nous tirer dessus.»";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Mon fils, je n'ai pas eu le temps de te remercier pour ma libération. Apparemment, l'évêque espagnol et l'inquisiteur Palotti voulaient perturber les relations à peine établies entre notre cardinal et le Saint-Siège, donc tu as agi entièrement dans l'intérêt de notre pays. Encore une fois. Mais personne ne te dira 'merci', sauf moi.";
			link.l1 = "Chose courante, Saint Père. Heureux d'avoir pu aider. Mais, je dois aussi vous demander quelque chose, vous vous souvenez ?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Bien sûr ! Passons donc aux affaires plaisantes - Charles, comment vont les préparatifs pour votre jour le plus important ?";
			link.l1 = "Ça prend lentement forme. Je connais des campagnes militaires qui ont été préparées plus facilement et plus rapidement, mais ça en vaut la peine !";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Bien sûr, mon fils ! Et, à cette occasion, je veux clarifier quelque chose - comment vois-tu ta cérémonie de mariage ?";
			link.l1 = "Tu veux dire, à quel point pompeux ?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Bien sûr ! Parce que je dois préparer l'église, et peut-être voudrez-vous inviter quelques personnes importantes.";
			link.l1 = "Rien de spécial, Saint Père. Ceux que je considère comme nos amis nous attendront ailleurs. Il n'y aura ici que quelques fonctionnaires, mes gars, et quelques badauds ordinaires.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Eh bien, alors, je pense que nous nous débrouillerons avec une petite donation.";
			link.l1 = "Ça ne semble pas trop effrayant. Et combien vaut un tel don en or ?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "Pour la chorale, le service solennel et autres dépenses - cent cinquante, pas plus. Plus, le don habituel des jeunes mariés, en tout - deux cents doublons.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Voilà, Saint Père.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "À propos de ces campagnes militaires... Je vais devoir faire un tour à la banque et revenir.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "Qu'en est-il de votre don, mon fils ?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Voici pour vous, Saint-Père.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Oui, oui, je l'apporterai bientôt...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Il reste encore une question à résoudre - qui donnera la mariée et témoignera du mariage de son côté ?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, de Blueweld. C'est un Anglais, mais une personne respectée et attachée à Helen comme si elle était sa propre fille, et sa mère adoptive est Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noel Forget, je suis sûr qu'il me fera l'honneur.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, je suis sûr qu'il me fera l'honneur.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Eh bien, et qui témoignera pour le marié ? Souvenez-vous, cela doit être un homme de noble naissance et de réputation digne.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noel Forget, je suis sûr qu'il me fera l'honneur.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, je suis sûr qu'il me fera cet honneur.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - un marchand respectable de la Guadeloupe. Je n'ai qu'à faire provision de son alcool préféré.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey - un marchand respectable de la Guadeloupe. Je n'ai qu'à faire le plein de son alcool préféré.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Génial, je vais envoyer les invitations, mais les invités auront besoin de temps pour arriver ici. Je pense que tout sera prêt dans un mois, et que les personnes indiquées seront arrivées en ville.";
			link.l1 = "Bien! Alors j'ai le temps de faire quelques courses. À bientôt, Saint Père, et souhaitez-moi bonne chance !";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Parfait, je vais envoyer les invitations, mais les invités auront besoin de temps pour arriver. Je pense que tout sera prêt dans un mois, et les personnes indiquées seront arrivées en ville.";
			link.l1 = "Bien! Alors j'ai le temps de faire quelques courses. À bientôt, Saint Père, et souhaite-moi bonne chance!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Parfait, je vais envoyer les invitations, mais les invités auront besoin de temps pour arriver. Je pense que tout sera prêt dans un mois, et les personnes indiquées seront arrivées en ville.";
			link.l1 = "Bien! Alors j'ai le temps de faire quelques courses. À bientôt, Saint Père, et souhaitez-moi bonne chance!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "Alors, le jour est venu, mon fils ! Tout est prêt - dans quelques heures nous pourrons commencer. Tu as l'air pâle !";
			link.l1 = "Je suis un peu nerveux, Saint Père.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "C'est fréquent. C'est le jour le plus important de ta vie, et je suis sincèrement heureux pour toi, comme tous ceux qui sont venus. J'espère que tu te souviens au moins des prières de base - tu n'as jamais vraiment gâté l'église avec ton attention, n'est-ce pas ? Néanmoins, je t'aiderai dans tous les cas. \nEt une chose de plus - autant que je comprends, la mariée ne changera pas ses principes et nous ne la verrons pas en robe ? Eh bien, la haute société est sur le point de voir une autre surprise de ta part - tu en es plein. Quoi qu'il en soit, va mon fils, mets-toi en forme et nous commencerons.";
			link.l1 = "Oui, Saint Père. Faisons-le.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Notre Pere, qui es aux cieux, que ton nom soit sanctifie, ad...";
			link.l1 = "...que ton règne vienne";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "... fiat voluntas tua, sicut in caelo et in terra. Panem nostrum quotidianum da nobis hodie, et dimitte nobis debita nostra si...";
			link.l1 = "...comme nous pardonnons aussi à ceux qui nous ont offensés";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...comme c'était au commencement, et maintenant et toujours, et dans les siècles des siècles. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = " ";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hum...";
			link.l1 = "Bonjour, ami.";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Très chers, nous sommes réunis ici ensemble sous le regard de Dieu, et en présence de cette congrégation, pour unir cet homme et cette femme dans le saint mariage. Bien-aimés "+sld.name+" et Charles, tu as écouté la parole de Dieu, qui t'a rappelé le sens de l'amour humain et du mariage. Maintenant, au nom de la sainte Église, je souhaite mettre au défi tes intentions.\n"+sld.name+"et Charles, as-tu un désir volontaire et sincère de vous unir par le lien du mariage, en présence de notre Seigneur ?";
			link.l1 = "Oui.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Avez-vous l'intention de vous être fidèles en santé comme en maladie, dans le bonheur comme dans le malheur, jusqu'à la fin de votre vie ?";
			link.l1 = "Oui.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Avez-vous l'intention d'aimer et d'accepter les enfants que notre Seigneur vous enverra et de les élever dans la foi chrétienne ?";
			link.l1 = "Oui.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Eh bien, tournez-vous l'un vers l'autre et faites un vœu.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Si quelqu'un ici présent connaît une raison pour laquelle ce couple ne devrait pas être uni dans le saint mariage, qu'il parle maintenant ou se taise à jamais.\nDans ce cas, devant la face du Seigneur, et les personnes rassemblées ici, je vous déclare mari et femme ! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "Jeunes mariés, agenouillez-vous et priez ensemble. Oratio fidelium."+sTemp+"";
			link.l1 = "Bonjour, ami.";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Mes félicitations, fils. Ton père peut être fier de toi, et moi aussi. Soyez heureux et prenez soin l'un de l'autre en ces temps difficiles.";
			link.l1 = "Merci, Saint Père. Ce fut un service merveilleux et je suis heureux que ce soit vous qui l'ayez célébré.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "So you have come to me for counsel, my children? Well then, I am all ears.";
			link.l1 = "Rather for assistance, Father. Assistance from a man who has connections and knows all manner of people...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Forgive me for interrupting you, my son, but I must remind you that I am but a humble abbot, not some secret agent.";
			link.l1 = "Yet a humble abbot might know a secret agent, might he not? Or at least suggest how one might reach him?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "The matter that brought us here truly concerns certain long-forgotten secrets... We are only trying to drag them back into the light.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Now, young man, this I do not like. Get to the point, and then we shall see how – or if – I may help you.";
			link.l1 = "Yes, Father. I shall try to be brief...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", do not speak in riddles – it is, I confess, wearisome.";
			link.l1 = "Yes, Father. I shall try to be brief...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Go on, my son.";
			link.l1 = "My companion, Mary Casper, is seeking her father – or at least some scrap of information about him. We have discovered that he was an officer in the English Navy and served aboard the brig 'Wrangler', which wrecked at Cape Catoche in 1638.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "And you hope that he yet lives? After so many years?";
			link.l1 = "Even if he did not survive the wreck, Mary wishes to know where her father came from, what manner of man he was, the life he led... Official papers are sparse in detail – yet even in them one may find something of value, do you not agree, Father?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "You are right in your reasoning, my son. Yours is a good and godly endeavor. But I still fail to grasp what exactly you expect of me.";
			link.l1 = "You have long dwelt in the Archipelago, Father. Perhaps you know someone with access to colonial archives concerning officers of the English Navy?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "We need a man with access to the colonial archives where records of English naval officers are kept. Surely you know of such a one, Father.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Do you understand what you are asking, my son? The point is not merely that such information may be a military secret...";
			link.l1 = "And what else then, Father? I shall speak plainly...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Do you understand what you are asking, my son? The point is not merely that such information may be a military secret...";
			link.l1 = "And what else then, Father? I shall speak plainly...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "The problem lies with those very colonial archives. Twenty years ago Jamaica was under the Spaniards, and St. John’s and Bridgetown under constant threat of raids. It is unlikely any Royal Navy ships were stationed there...";
			link.l1 = "You mean the Admiralty archives in London, Father?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Perhaps. The papers should have been sent to the Admiralty. To obtain them will not be easy.";
			link.l1 = "But it can be done, can it not, Father?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Nothing is impossible, my son. But it will require effort... and payment.";
			link.l1 = "Of course, Father. Shall I give the money to you, or must I meet with someone else?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "I will meet someone else myself, my son. What I need from you is... eight hundred doubloons.";
			link.l1 = "Very well, Father. How long will it take?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "I reckon two months. And, by the way, you have not told me the name of the one you seek.";
			link.l1 = "That man’s name is Joshua Casper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "I shall remember it. If you are ready to give me the full sum now — I will send word as soon as tomorrow.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Of course, Father. Here, take it. Eight hundred in gold.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "No, Father, I do not have such money on me. But I shall return soon and bring it.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Very well, "+pchar.name+". Return in two months – I am certain by then I shall have one answer or another for you.";
			link.l1 = "Thank you, Father. Until we meet again!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "As you say, my son.";
			link.l1 = "I will return soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "He learned both of Joshua Casper and of his ship – which, however, was not the 'Wrangler'. No brig of that name ever belonged to the Royal Navy.";
			link.l1 = "Hm... I am absolutely certain the vessel Joshua Casper served on bore that name. And what of Joshua himself?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "That man was a fine officer with many merits and awards – all recorded in his personal file. Though he did not belong to the true faith, he was a worthy captain. Mademoiselle may well be proud of such roots.";
			link.l1 = "That is good news, Father. But if you permit, let us return to the ship. If it was not the 'Wrangler', then what was its name?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. He left Plymouth in January of 1638 with orders to deliver wages to the garrisons of Antigua and Providence.";
			link.l1 = "Incredible...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Whether the ship reached its final destination, I do not know. But it did put in at St. John’s. In the port office there remains a report by Captain Casper dated June 2 of that year.";
			link.l1 = "I knew you were not as simple as you try to appear, Father! This document, I presume, contains some important details?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "We are forever in your debt, Father. Since you mentioned this document – it must contain something important, then?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Only a report of a battle with the Spanish galleon 'Toro' near the Azores, in which a third of the crew perished – read the report, it tells all.";
			link.l1 = "One more question: since you had access to the records of Antigua’s port authority, did you by chance come across Joshua Casper’s name anywhere else?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Only a report of a battle with the Spanish galleon 'Toro' near the Azores, in which a third of the crew perished – read the report, it tells all.";
			link.l1 = "One more question: since you had access to the records of Antigua’s port authority, did you by chance come across Joshua Casper’s name anywhere else?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "You ask much of me, my son. If you mean to suggest that he may have survived that shipwreck and later returned to the fleet – I very much doubt it.";
			link.l1 = "The Lord works in mysterious ways, Father.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "Indeed, my son. But you see, his personal file states that Joshua Casper was born in 1586...";
			link.l1 = "Perhaps you are right, Father.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "You know, Father, in my years in the Caribbean I have seen such things that I could believe even the most unlikely of tales.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Surely such an officer was worthy of dying in battle. But if one is to speak philosophically, in a sense that too was a battle...";
			link.l1 = "I am no philosopher, Father. But thank you for everything...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Surely such an officer was worthy of dying in battle. But if one is to speak philosophically, in a sense that too was a battle...";
			link.l1 = "I am no philosopher, Father. But thank you for everything...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "The Lord leads you on this path, my children, and to aid you is my humble duty. But I fear there is nothing more I can do for you in this matter...";
			link.l1 = "I understand, Father. Well then, allow us to take our leave.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "Je suis profondément préoccupé par l'état de ton père. Je ne sais pas s'il te l'a révélé dans sa lettre, mais dans celle qu'il m'a envoyée, il a confessé que ses forces l'abandonnent, et qu'il pense ne plus en avoir pour longtemps.";
			link.l1 = "Il a mentionné que la maladie ne reculait pas... Mais il a visiblement tu ses craintes.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "Je ne peux rien te dire de plus — c'est tout ce qu'il m'a confié, mais une chose est claire : il craint de paraître devant Dieu sans t'avoir revu.";
			link.l1 = "Il en a parlé. Pour être honnête, j'avais moi aussi pensé à lui rendre visite... Mais...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "Mon fils, seul Dieu sait combien de temps il nous est donné. Ne remets pas cette rencontre : parfois, une simple étreinte peut apporter à une âme plus de paix que mille prières.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", j'espère que tu ne reporteras plus ta visite ? Rappelle-toi que le temps joue contre toi...";
			}
			link.l1 = "Vous avez raison, mon père. Je vais immédiatement commencer à préparer mon départ. Vu ma position actuelle, il se peut que cela me prenne du temps pour tout régler...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "Je comprends vos inquiétudes, saint père, et je vous promets d'y réfléchir. Mais pour l'instant, j'ai des affaires urgentes à régler. Nous reparlerons de cela plus tard.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;
		
		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;
		
		case "SharlieEpilog_Benua_5":
			dialog.text = "Si tu as des dettes, mon fils, je te recommande de commencer par les régler. Les usuriers sont des gens vindicatifs : ils peuvent nuire sérieusement à ta réputation, et par elle, au bon nom de ta famille — même dans l’Ancien Monde.\n"+
			"Quant au reste — au nom de mon amitié avec ton père et pour la gloire de Dieu — je t’apporterai toute l’aide possible. Tu peux transmettre tes instructions par écrit, et je m'assurerai qu'elles parviennent à leurs destinataires à temps. Il te faudra simplement payer les frais de messagerie. Je pense que deux cents doublons seront suffisants pour l'envoi de toutes les lettres.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Merci, saint père. Votre aide me sera très précieuse. Voici, prenez-les.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Merci de votre sollicitude, saint père. Hélas, je n’ai pas la somme requise sur moi pour le moment. Nous reviendrons sur ce point plus tard.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;
		
		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;
		
		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Bien sûr, "+pchar.name+". J’imagine que tu as apporté les deux cents doublons ?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Évidemment. Les voici.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Hélas, je n’ai toujours pas cette somme.";
			link.l2.go = "exit";
		break;
		
		case "SharlieEpilog_Benua_6":
			dialog.text = "Parfait, mon fils.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
				case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "Alors, par quoi préfères-tu commencer ?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "À qui veux-tu envoyer un message, et à quel sujet ?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Un jour, j’ai découvert une île absente des cartes. Quelques colons y vivaient déjà, et j’ai pris leur sort sous ma protection. En partant, il leur faudra un nouveau 'gouverneur'.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "Je souhaite envoyer une lettre à Marcus Tirax de La Vega. Ce n’est pas une affaire capitale, mais la lettre doit lui parvenir dans les délais.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "Je possède un brevet en cours de validité au nom de la France — je voudrais informer la chancellerie de Capsterville de ma décision.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Saint père, durant les années passées sur ces terres, j’ai amassé une certaine fortune. Mais avant qu’elle n’appartienne à ma famille, j’aimerais la purifier. Effacer le sang qu’elle pourrait porter. Je veux quitter cette contrée non pas en brigand chargé de butin, mais en homme dont la conscience et la réputation sont pures aux yeux du monde.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "Je souhaiterais informer Jan Svenson de Blueveld de mon départ. Il serait impoli de quitter l’archipel sans l’en avertir.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "Je souhaite faire savoir à la famille Houk de Maroon Town que je pars en voyage.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "Je veux prévenir Gino Guineili de Saint John's de mon départ pour l’Ancien Monde.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "C’est tout, mon père... Il semble que je sois prêt à partir.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Pardonnez-moi, saint père, je dois y aller.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
				case "SharlieEpilog_Benua_Jino":
			dialog.text = "Bien sûr, mon fils.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;
		
		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;
		
		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Prêt. On peut envoyer.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Bien sûr, mon fils.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;
		
		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;
		
		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Prêt. On peut envoyer.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Jan Svenson de Blueveld… Je m’en souviendrai. Donne‑moi la lettre — elle partira aujourd’hui.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "La maison de Jan est facile à trouver. Il suffit de demander à n’importe quel habitant — il est peu probable qu’on trouve quelqu’un à Blueveld qui ne sache pas qui il est et où il habite.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;
		
		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Ne t’inquiète pas, mon fils, nos hommes savent ce qu’ils font. La lettre sera remise à qui de droit et dans les délais.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money":
			dialog.text = "Veux‑tu que l’Église bénisse de l’or obtenu par des moyens criminels ?";
			link.l1 = "Plutôt — obtenu au service de la France et de Sa Majesté.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;
		
		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "Je te comprends, mon fils. Je pourrais dire que l’Église ne purifie pas l’argent et ne nie pas la manière dont il a été gagné. Mais en quoi cela servirait‑il si les affamés restent affamés, les sans‑abri dorment dans la rue et les malades meurent sans aide ? Je suis prêt à donner ma bénédiction. En échange, qu’une petite partie de ces fonds serve non pas à toi, mais à ceux qui ont besoin d’aide.";
			link.l1 = "Bien sûr, saint père, je suis prêt à donner autant que vous le direz.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;
		
		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "Alors, quelle somme veux-tu emporter avec toi ?";
			link.l1 = "Dix millions de pesos.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Vingt-cinq millions de pesos.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Cinquante millions de pesos.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;

		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "Dans ce cas, un don de cent mille pesos sera suffisant. Grâce à cet argent, nous pourrons offrir des repas aux nécessiteux pendant de nombreux mois. Es-tu prêt à verser cette somme dès maintenant, mon fils ?";
			link.l1 = "Bien sûr. Tenez, prenez-les. Je suis heureux d’aider ceux qui en ont vraiment besoin, et je suis sûr que sous votre direction, cet argent servira la cause avec sagesse et honneur.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Je suis désolé, il me faut encore réfléchir.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "Alors, ton don devra s’élever à deux cent cinquante mille pesos. Cette somme nous permettra de construire un orphelinat qui portera ton nom et pourra répondre à ses besoins pendant un certain temps. Es-tu prêt à verser cette somme dès maintenant, mon fils ?";
			link.l1 = "Bien sûr. Tenez, prenez-les. Je suis heureux d’aider ceux qui en ont vraiment besoin, et je suis sûr que sous votre direction, cet argent servira la cause avec sagesse et honneur.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Je suis désolé, il me faut encore réfléchir.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Eh bien, on dirait que tu n’as pas perdu ton temps, "+pchar.name+". Je pense qu’un don de cinq cent mille pesos sera amplement suffisant. Grâce à cette contribution, nous pourrons construire un hôpital et l’équiper pour de nombreuses années. Es-tu prêt à verser cette somme dès maintenant, mon fils ?";
			link.l1 = "Bien sûr. Tenez, prenez-les. Je suis heureux d’aider ceux qui en ont vraiment besoin, et je suis sûr que sous votre direction, cet argent servira la cause avec sagesse et honneur.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Je suis désolé, il me faut encore réfléchir.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Parfait, mon fils.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Parfait, mon fils.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Parfait, mon fils.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "Et quelle sera ta décision, mon fils ?";
			link.l1 = "Même si un long voyage m’attend, je souhaite conserver mon brevet – ainsi que ma loyauté envers la France et le Roi.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "J’ai décidé de renoncer à mon brevet. Un long chemin m’attend et j’ignore quand je reviendrai. Il me semble plus sage de ne pas porter le fardeau d’obligations et de règles que je ne pourrai peut-être pas respecter.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "Je suis heureux que tu sois parvenu à cette décision, mon fils. Aujourd’hui plus que jamais, notre royaume a besoin de ses chevaliers forts et courageux. Mais dis-moi, "+pchar.name+", n’as-tu jamais songé à te poser, à trouver un foyer, à cesser de risquer ta vie à chaque instant ? Car l’homme n’est pas destiné à se mettre à l’épreuve éternellement dans les flammes.";
			link.l1 = "Je ne suis pas sûr de pouvoir rester sans rien faire, mon père. Mais, comme il est écrit dans les Écritures : 'même les guerriers du Seigneur reçoivent le repos lorsque leur labeur est achevé'. Aussi loin que je sois de la fin de mon œuvre, j’espère choisir moi-même le jour où je rangerai ma lame pour toujours.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Parfait, mon fils. Je pense que Sa Majesté ne restera pas indifférente à ta loyauté et à ton dévouement.";
			link.l1 = "Mes pensées sont ailleurs pour l’instant... J’espère que mon père n’insistera pas pour que je reste vivre dans notre domaine. Je ne pense pas être prêt pour cela. Mais, heureusement, j’aurai le temps d’y réfléchir.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Bon, revenons aux choses terrestres.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "C’est une décision raisonnable. Toutefois, je dois dire que ton départ affaiblira grandement la puissance de la France dans ces eaux.";
			link.l1 = "Je suis certain que sous les ordres de Sa Majesté, il y a assez de capitaines dignes pour que la grandeur de la France ne vacille pas.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "Voilà, c’est fini. Comme un poids en moins. À vrai dire, j’en ai presque oublié qui j’étais en arrivant ici, dans les Caraïbes... Tant de choses se sont passées.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Tu l’as sans doute déjà entendu, mon fils : les voies du Seigneur sont impénétrables. Tout ce qui t’a été destiné d’en haut, tu l’as traversé avec dignité. Mais je crois que tes épreuves ne sont pas terminées, et peut-être que ta gloire ne fait que commencer à s’élever vers son apogée.";
			link.l1 = "La gloire est un fardeau, père. Tous ceux qui la recherchent ne sont pas capables d’en supporter le poids... ni de s’arrêter à temps.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Bon, revenons aux choses terrestres.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron":
			dialog.text = "Mon fils, as-tu affaire avec le chef des pirates ?";
			link.l1 = "Vous connaissez le Gardien du Code ?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "Le Gardien du Code ? Non, je ne le connais pas. Je connais Marcus Tirax – le bourreau, derrière qui se cache tant de sang que même des siècles de prières ne suffiraient pas à obtenir le pardon du Seigneur. Et pourtant... tu fais vraiment affaire avec lui ?";
			link.l1 = "J’ai dû gagner ses faveurs... pour faire sortir Michel de prison. Quoi qu’il en soit, j’ai reconnu mon erreur et je n’ai plus l’intention d’entretenir des liens avec lui. Cette lettre rompra le dernier fil qui nous relie.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "Cela n’a plus d’importance. Je quitte l’archipel, et nos chemins se sépareront d’eux-mêmes, mon père.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;

		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "Et quel est donc ce lien, mon fils ? J’espère qu’il n’est pas taché du sang des innocents.";
			link.l1 = "J’étais officiellement à la tête de l’établissement pirate de Le François. En réalité, un autre homme tirait les ficelles. Aujourd’hui, je renonce au titre de baron pirate – définitivement et irrévocablement.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "Je suis heureux que tu sois revenu sur le droit chemin, mon fils, et je prierai pour le salut de ton âme. Chacun peut trébucher, mais le Seigneur ne pardonne que ceux dont le repentir est sincère.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;

		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;

		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Excellent, "+pchar.name+". Donne-moi la lettre – je veillerai à ce qu’elle parvienne à son destinataire. Et n’oublie pas de prier, mon fils. Seuls le repentir et la prière peuvent laver même les péchés les plus lourds de ton âme.";
			link.l1 = "Merci, mon père. Peut-être que tout n’est pas encore perdu pour moi.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "Aussi grand soit le péché, mon fils, les portes du pardon restent toujours ouvertes. Le repentir, la prière et les bonnes actions purifient l’âme comme la pluie lave la poussière de la pierre.";
			link.l1 = "Chaque chose en son temps, mon père. Pour l’instant, je dois m’occuper des affaires terrestres.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;
		
		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;
		
		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Tenez.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "C’est bien, mon fils, que tu aies choisi de prendre soin de ces gens et que tu ne les aies pas oubliés. À qui souhaites-tu confier cette île ?";
			link.l1 = "Je pense qu’il faut y hisser le drapeau français. Tôt ou tard, l’île sera découverte, et d’autres nations pourraient chercher à s’en emparer. Je ne peux pas laisser faire cela.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "Cette île et ses habitants méritent de vivre libres, sans être soumis à une autorité royale. J’ai l’intention d’envoyer une lettre à mon ami Jan Svenson, de Blueweld. Je suis certain qu’il acceptera de prendre cette terre sous sa protection. Mais je vous en prie, mon père, gardez cette conversation secrète – pour la sécurité et le bien-être de ces gens.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;

		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "Tu fais preuve de sagesse, "+pchar.name+". Sous la protection du Roi, cette île connaîtra l’ordre et la sécurité.";
			link.l1 = "J’enverrai une lettre appropriée à la chancellerie de Capsterville et aux habitants de l’île. Les coordonnées seront indiquées sur l’enveloppe.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;

		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Tenez. J’espère que vos hommes trouveront l’île avant que la flotte de Sa Majesté n’y parvienne.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Ne t’inquiète pas, mon fils. Je confierai la livraison de ces lettres aux meilleurs de nos courriers.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "Ce n’est pas à moi de juger si ton choix est juste, mon fils. Tôt ou tard, quelqu’un découvrira cette île, et l’une des puissances voudra se l’approprier. Ce n’est qu’une question de temps. Mais si telle est ta décision, alors c’est sans doute la volonté de Dieu. Ne t’en fais pas : je ne mettrai pas ces gens en danger et je prierai pour eux.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Jan Svenson de Blueweld, n’est-ce pas ?";
			link.l1 = "Exactement, mon père. Et la seconde lettre doit être livrée directement sur l’île. Les coordonnées sont indiquées sur l’enveloppe.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Parfait, mon fils. Si je ne me trompe pas, tu es arrivé ici à bord de la pinasse '"+GetShipName("Ulysse")+"' ?";
			link.l1 = "C’est exact. Mais pourquoi cette question ?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Parce que ce navire a été récemment mis aux enchères. Et toi, Charles, tu as la chance de rentrer chez toi à bord du même bâtiment – mais cette fois en tant que capitaine.";
			link.l1 = "Hmm... Je dois avouer que l’idée est séduisante. Je devrais peut-être passer au bureau du port. Merci, mon père.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
