// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

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
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// ставим пленного испанца
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//запрет диалога
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
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Oui, ces rumeurs sont parvenues jusqu'à notre église aussi. Je peux vous aider avec votre dilemme. C'est quelque chose qui peut être résolu. J'ai besoin de deux cent cinquante doublons d'or pour arranger votre situation.";
				if (PCharDublonsTotal() >= 250) // Sinistra legendary edition
				{
					link.l1 = "Super ! Voici l'or.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "Alors c'est le moment idéal pour moi de trouver les doublons.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Oui, des rumeurs sur tes 'exploits' sont parvenues jusqu'à notre église aussi. Tu as terni ta réputation, mon fils. Tu devrais être plus prudent. Mais je peux t'aider. J'ai besoin de cinq cents doublons d'or pour arranger ta situation.";
					if (PCharDublonsTotal() >= 500) // Sinistra legendary edition
					{
						link.l1 = "Superbe ! Voici l'or.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "Alors, c'est le moment idéal pour moi de trouver les doublons.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Oui, mon fils. Tu es tout aussi désespéré que ton frère... C'est probablement un trait de famille. Je ne peux pas complètement corriger la situation, mais néanmoins, je crois que je peux atténuer ton sombre sort. Et plus tard, nous pourrons faire d'autres offrandes si tu le souhaites. J'ai besoin de six cents doublons d'or pour l'instant et je commencerai à résoudre ton dilemme immédiatement.";
					if (PCharDublonsTotal() >= 600) // Sinistra legendary edition
					{
						link.l1 = "Superbe ! Voici l'or.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Alors c'est le bon moment pour moi de trouver les doublons.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // Sinistra legendary edition
			Log_Info("You've given "+iTotalTemp+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Maintenant, vous devrez attendre au moins deux semaines. Je pense qu'au cours de ce temps, je pourrai rencontrer et discuter avec les bonnes personnes.";
			link.l1 = "Merci, père ! Je vais attendre...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
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
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Mes félicitations, fils. Ton père peut être fier de toi, et moi aussi. Soyez heureux et prenez soin l'un de l'autre en ces temps difficiles.";
			link.l1 = "Merci, Saint Père. Ce fut un service merveilleux et je suis heureux que ce soit vous qui l'ayez célébré.";
			link.l1.go = "LH_abbat_38";
		break;
		
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
