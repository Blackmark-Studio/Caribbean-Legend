// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Je devrais partir...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Bon sang, qui diable es-tu ?";
				link.l1 = "Bonjour, don Lope. Bien que nous ne soyons pas encore présentés, le moment est aussi bon que n'importe quel autre. Surtout maintenant que je suis si désireux de vous aider à sortir de cette situation difficile...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Que veux-tu ?";
				link.l1 = "Je devrais y aller...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Aider ? Moi ? Quel retournement de situation ! Pourriez-vous m'éclairer, señor, d'où vient une telle générosité ?";
			link.l1 = "Certainement. Je cherche votre ancien capitaine, Esberdo Cabanas, et je n'ai pas beaucoup de temps... de préférence, j'aimerais le rencontrer dans cet endroit qu'il garde secret. Encore mieux si j'y arrive avant lui.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha ! J'ai dit à cet idiot pathétique de garder sa bouche fermée ! L'ambre bleu, n'est-ce pas ?";
			link.l1 = "Vous pensez dans la bonne direction, mon bon monsieur.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Alors hâtons-nous. J'aimerais te raconter chaque détail si tu trouves un moyen de me sortir d'ici. Tu sais comment je me suis retrouvé dans ce trou?";
			link.l1 = "Dans l'ensemble, oui je le fais.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "J'étais complètement ivre quand cela est arrivé. Que le diable emporte ce foutu barman ! Je ne me souviens de rien. On m'a tout raconté seulement quand je me suis réveillé dans la cale du 'Cantavro'. Tout serait derrière nous si nous partions en mer, le commandant et l'alcalde étaient prêts à détourner le regard. Mais ce maudit don Esberdo m'a simplement mis en prison. Tu penses qu'il a fait ça 'pour bien faire' ? Si seulement, ce vaurien voulait juste garder ma part des ambres.\nC'est moi qui ai mentionné qu'il pourrait y avoir plus d'ambre sous l'eau que ce que nous avons trouvé sur la plage. C'est moi qui ai trouvé un moyen de l'obtenir. Je devais recevoir une belle part, mais... oh, ce fils de pute ! Ugh, mais assez de ça. Ni l'alcalde, ni le commandant, ni le don de Tolède ne sont contents que je sois gardé ici à pourrir. Si ce n'était pas pour ce paysan et sa femme vache, qui ont semé le chaos... de toute façon, ils ne s'opposeront pas à ce que tu m'aides.\nParle au gouverneur, fais semblant d'être mon vieil ami d'Europe - je le confirmerai moi-même. Comment t'appelles-tu, d'ailleurs ?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+"Formidable. Allez voir don Diego de Tolède et demandez-lui conseil. Souvenez-vous, vous n'avez que trois jours, poursuivre le 'Cantavro' serait inutile après cela. Libérez-moi et je vous donnerai tout ce dont vous avez besoin pour vous occuper de ce salaud, Cabanas.";
			link.l1 = "Je vais aller voir le gouverneur immédiatement, don Lope. Je ferai de mon mieux pour résoudre cette situation pour nous deux.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Alors, le charlatan et sa poule tapageuse ont eu leur revanche, et j'en ai enfin fini avec ce trou. Vous avez ma gratitude, señor, vous avez fait votre part. Maintenant, permettez-moi de faire la mienne.";
			link.l1 = "Je suis tout ouïe !";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Bien. Lors de notre précédente patrouille, nous avons été frappés par une tempête qui nous a fait abandonner notre cap. Nous avons atterri sur la plage du Main Occidental, non loin de la Côte des Moustiques, pour y prendre de l'eau douce. Nous avons trouvé un bon gisement d'ambre bleu là-bas. J'ai fait quelques prospections et j'ai trouvé un tas sous l'eau. Nous avions besoin de meilleur équipement pour le récolter, c'est pourquoi nous avons décidé de revenir plus tard. \nEsberdo avait acheté cinq longues barques à La Havane pour que les Indiens plongent et ramassent l'ambre. Vous connaissez la suite de l'histoire - les salauds se sont débarrassés de moi et ont pris la mer. Trouvez-le à la Côte des Moustiques au nord de Blueweld, et faites vite - selon mes calculs, vous n'avez qu'environ sept jours pour y arriver. J'espère que vous attraperez cet enfoiré en plein milieu de la récolte, que vous lui prendrez tout son ambre et que vous lui planterez le ventre de nombreuses fois. Faites attention cependant, mon ancien capitaine est un combattant et un marin expérimenté. Bon vent, señor.";
			link.l1 = "Toi aussi, Lope. Adieu !";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Voulez-vous poser une question, monsieur ?";
			link.l1 = "Concernant don Montoro. Nous sommes de vieux amis et j'ai été vraiment contrarié lorsque j'ai appris ses malheurs. Don Diego de Tolède m'a envoyé vers vous, disant que vous aviez déjà essayé de libérer notre ami commun...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... señor, c'est un peu... inattendu, mais je suis heureux de rencontrer un ami de Lope ! Il n'a pas eu de chance depuis un bon moment déjà et maintenant ça...";
			link.l1 = "Que pouvons-nous faire pour lui? Pas question qu'un noble hidalgo pourrisse parmi la lie de la société!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Un homme d'affaires ! Il est à la fois facile et difficile d'aider le pauvre Lope. J'ai parlé avec le profiteur avec qui le pauvre Lope a eu la malchance de se disputer. Il a accepté de nous rencontrer à mi-chemin pour cinq cents doublons. Une sacrée somme pour ses 'souffrances' et celles de sa femme. Hélas, je n'ai réussi à rassembler que la moitié de la somme requise - deux cent cinquante doublons.";
			link.l1 = "Alors, si je vous apporte encore deux cent cinquante doublons, don Lope sera libéré ?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Oui. Le salaud avide m'a promis de répandre la nouvelle que Lope l'a dédommagé pour tous les dégâts. Il demandera également au gouverneur de lui accorder son pardon.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "J'ai la somme requise avec moi en ce moment. Tiens, que ce bourgeois avide s'en étrangle.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Je ferai de mon mieux pour obtenir de l'argent dès que possible.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Je n'en crois pas mes oreilles ! Senor, le Seigneur a dû vous envoyer !";
			link.l1 = "Quand vont-ils libérer notre homme ?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Ravi de l'entendre, señor. Vous êtes un véritable ami de Lope et un vrai noble.";
			link.l1 = "Adieu !";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "As-tu apporté l'argent ?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "J'ai la somme requise avec moi en ce moment. Tiens, que ce bourgeois avide s'en étouffe.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Je suis toujours dessus.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Je vais apporter l'argent à ce salaud rusé ce soir. Je crois qu'ils auront un ordre pour la libération de notre ami d'ici midi. Et j'espère que nous nous réunirons plus tard pour célébrer ?";
			link.l1 = "Bien sûr, don Rosario. Je devrais y aller maintenant. À bientôt !";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Bientôt notre ami sera libre !";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Hé, qu'est-ce que tu fais sur mon navire, diable ? Je ne crois pas t'avoir invité, hein ?";
			link.l1 = "Calme-toi, Geffrey. Je viens de la part de Tyrex concernant l'affaire de la soie du navire.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, eh bien, parlons alors. Qu'est-ce qu'il prévoit ? J'ai déjà parlé avec des contrebandiers, si vous me demandez, ils offrent un bon prix pour les marchandises...";
			link.l1 = "Et combien, si je puis me permettre ?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 pesos pour un rouleau. Je pense que c'est un bon prix.";
			link.l1 = "Ouais, et Tyrex veut vingt pièces en or pour un rouleau. Pas une pièce de moins. Et je parle de doublons. Il m'a donné pour mission de trouver l'acheteur idéal à ce prix-là.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, gars, t'as de la chance ! Marcus a un sacré appétit ! Eh bien, va donc trouver un tel acheteur alors, ce serait glorieux de te voir essayer.";
			link.l1 = "Ouais, c'est vraiment très putain de drôle et hilarant. J'ai l'air heureux ? Non. Alors je te suggère d'arrêter de rire et de m'aider.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Très bien, très bien, mon pote... Jésus, tu n'es pas très amateur de blagues, hein? Mais je comprends, tu n'es pas à blâmer pour les fantasmes de Tyrex, nous aurons tous notre part de cela, fais-moi confiance. Et comment puis-je t'aider? Tu ne peux pas le vendre dans les magasins, les douanes ne sont pas une option non plus, il ne reste que les contrebandiers. Qui d'autre en a besoin? As-tu des idées?";
			link.l1 = "J'y pense depuis Hispaniola... Peu importe. Je n'ai que deux mois pour trouver un acheteur régulier. Il faut faire quelque chose à ce sujet. Tes ordres sont de débarquer dans la baie la plus proche et de faire des réparations.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Deux mois ?! Que diable ? Ah, merde. Le 'Serpent' a besoin de réparations et de nettoyage ou elle ne pourra même pas rattraper une barque. Hé, putains françaises ! L'équipage de Bald Geffrey reste à Capsterville pendant deux mois ! Ha-ha-ha !... Eh bien, bonne chance à toi, mon pote, dans tes recherches inutiles. Si tu trouves un idiot prêt à payer le prix de Marcus pour cette foutue soie - tu sais où me trouver.";
			link.l1 = "Attends ! Donne-moi un rouleau de cette soie. Je dois montrer la marchandise à des acheteurs potentiels.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Bien sûr, pas de problème. Tu peux l'emmener avec toi sur une chaloupe... Hé les gars ! Jetez une balle de soie sur le bateau du capitaine !";
			link.l1 = "Bien. Eh bien, je te verrai quand je trouverai l'acheteur !";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Autre chose, l'ami?";
			link.l1 = "Rien pour le moment...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Comment vas-tu, l'ami ?";
			link.l1 = "Ça va bien. J'ai trouvé un acheteur pour nous. Vingt-cinq doublons pour un rouleau. Je crois que Tyrex va aimer ça.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Pas possible ! Tu es le fils débrouillard d'un diable ! Comment as-tu réussi cela, hein ?";
			link.l1 = "C'est une longue histoire, Geffrey. Maintenant écoute. Tu devrais arriver au Cap Negril de la Jamaïque entre le 10 et le 15. Ils t'attendront là-bas la nuit. Le mot de passe est 'Un marchand de Lyon'. Compris? Répète.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "Un marchand de Lyon. J'ai compris. Je devrais dire à mon commissaire de l'écrire, c'est le seul homme ici qui sait écrire. Ha-ha!";
			link.l1 = "As-tu cent rouleaux dans la cale?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "J'en ai encore plus.";
			link.l1 = "Splendide. Il est temps pour vous de hisser les voiles alors. Ne me décevez pas !";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Détends-toi, camarade, tout sera fait comme il se doit.";
			link.l1 = "Bon vent, Geffrey. Peut-être que nous nous reverrons.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho ! Rusé Charlie Prince, en chair et en os ! Ça fait plaisir de te revoir, l'ami !";
			link.l1 = "Bougre de Geffrey! Charlie Prince tu dis? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Jamais entendu ton deuxième nom avant ? C'est comme ça qu'ils t'appellent à La Vega maintenant.";
			link.l1 = "Je vois d'où vient Charlie, mais pourquoi Prince ?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Eh bien, tu es le seul fils de noble chienne à La Vega ! Ha-ha-ha ! Comment ça va ? As-tu été chez Pasquale ? As-tu acheté des provisions du vieux salaud ?";
			link.l1 = "Plus jamais!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha ! Pourquoi, tu ne l'aimais pas ? T'a-t-il vendu du boeuf salé au prix du rhum ?";
			link.l1 = "Pire ! J'ai obtenu de lui un tuyau sur une caravane hollandaise chargée d'ébène. Ce n'était pas facile de la trouver, d'aborder le marchand et puis de protéger ce foutu bois de quelques douzaines de rats ! Et devine quoi, le salaud m'a payé 150 pesos pour une pièce. Pour une pièce de foutu ébène, Geffrey !";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Ça arrive tout le temps, mon pote, je te l'assure. Lavoisier a déjà roulé une douzaine de braves gars comme toi. Il t'a même payé quelque chose, ce qui est rare pour lui. Nous n'acceptons pas ses 'pistes', même si nous mourons de faim.";
			link.l1 = "Merci mon ami, au moins maintenant je sais que je n'étais pas le premier et le seul idiot ! Mais cette fois, le salaud s'est piégé lui-même. Je m'assurerai qu'il regrette le jour où il m'a vu.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Hé-hé-hé ! Attends Prince, calme-toi un peu. Le trafiquant est intouchable ici. Ose le piller - Marcus s'occupera de ton cul. Dis-moi, c'est Tyrex qui t'a envoyé chez Lavoisier ?";
			link.l1 = "Hm. Ouais... Pourquoi ?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Ecoute... (abaissant la voix) On dit que le binoclard partage avec Marcus. Tu me comprends maintenant ? C'est pourquoi aucun pirate n'osera jamais attaquer les navires de Lavoisier, sinon ils sont foutus.";
			link.l1 = "Bien noté. Merci pour l'avertissement, Geffrey. Adieu et bon vent !";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Toi aussi, mon pote.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho Prince ! Je me demandais qui avait fait les feux d'artifice ! J'ai amené une escouade de mousquetaires au cas où ce serait les Espagnols.";
			link.l1 = "Geffrey ? Vous êtes ici aussi ? Mais comment ? Avez-vous également acheté la carte au trésor ?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Mon pote, je ne gaspille pas mon argent pour des conneries pareilles. Ils m'ont livré le journal d'un voyageur qui écrivait sur un passage sûr vers ces cachots.";
			link.l1 = "Qui te l'a apporté ?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Un ivrogne, c'est tout. Il avait juste besoin de cent pesos pour un verre.";
			link.l1 = "Est-ce que cela s'est passé à Tortuga ?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Nan. C'était la Barbade ? Prince, pourquoi t'inquiètes-tu tant ? Plus nous serons nombreux, plus vite nous pourrons transporter les trésors !";
			link.l1 = "Je n'aime pas ça. Je ne crois pas aux coïncidences de ce genre. Serait-ce le père de Camilla qui a écrit ce journal ?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Qui est Camilla ?";
			link.l1 = "La garce qui m'a vendu une carte de cet endroit pour deux cents pesos !";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Héhé... Prince, tu réfléchis trop. Allons chasser le trésor. Allez, viens !";
			link.l1 = "Pas besoin. Je les ai déjà trouvés... Ils sont en bas dans le cachot, derrière des barreaux de fer. Il faudra les briser. Écoute Geffrey, il y a encore une chose ! Pelly le Sabre était ici aussi !";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Sabre? Eh bien, c'est notre jour de chance ! Mais où est-il maintenant ?";
			link.l1 = "En bas... mort. Je l'ai rencontré près du trésor. Il est devenu fou, a commencé à hurler de cupidité. Puis lui et ses compagnons m'ont attaqué.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly a toujours eu la poisse avec l'argent. Il a dû devenir fou en voyant la cargaison d'or.";
			link.l1 = "Peut-être bien... mais Geffrey, tu ne comprends pas ! Nous trois sommes arrivés ici ! Et nous avons tous le même indice ! Tu penses que c'était par hasard ? Quelqu'un veut clairement que nous soyons tous au même endroit, et cet endroit ressemble bien à une tombe.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "As-tu vu l'or cependant ?";
			link.l1 = "J'ai vu de mes propres yeux. Plusieurs coffres gigantesques remplis de pièces et de lingots.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Alors pourquoi t'inquiéter, Prince ? Montre-nous le chemin, allons jeter un œil à tes lingots. Ensuite, nous partagerons l'or.";
			link.l1 = "Ah tu pourrais avoir raison, peu importe... Allons-y.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Quel spectacle spectaculaire ! C'est un gros tas d'or ! Je comprends maintenant pourquoi Cutlass est devenu fou. Nous sommes très chanceux, Prince ! Que penses-tu, combien d'or trouverons-nous ici ?";
			link.l1 = "Beaucoup. Nous le saurons avec certitude lorsque nous nous occuperons de ces barreaux.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Oui, la grille est très solide, nous ne la briserons pas à mains nues ni avec des épées. Tu as raison, camarade - nous devons trouver des outils ou beaucoup de poudre à canon. Hé regarde ! Qu'est-ce que c'est !?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Quel foutu imbécile !";
			link.l1 = "Sale serpent !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Que le requin me happe si cela s'est passé sur le 'Poisson Volant' cette année... les gars, nous avons un invité ici ! Qu'est-ce qui ne va pas tant dans ta vie, l'ami, que tu as décidé de rendre visite à ma vieille baignoire ?";
			link.l1 = "Salutations ! Vous êtes celui qu'ils appellent Billy le Costaud, n'est-ce pas ?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Ne pouvez-vous pas deviner par ma voix, capitaine ? Il fut un temps où elle faisait chier les marchands britanniques et espagnols. C'était le bon vieux temps, ça !... Maintenant, le vieux Billy attend la fin de sa vie près des côtes de son île préférée sur son précieux canot...";
			link.l1 = "J'ai une affaire pour toi, Billy. On m'a dit que tu sais tout ce qui se passe ici autour de la Jamaïque. Est-ce vrai ?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Si on vous l'a dit, alors cela doit être vrai, n'est-ce pas ? Ne tirez pas un crabe par ses couilles, parlez. Quelle affaire avez-vous pour moi ?";
			link.l1 = "Très bien. Il y a un constructeur naval à Port Royal. Il offre à ses clients des services spéciaux, et il a besoin de soie navale pour sa production et lesdits services. Comme le commerce de cette marchandise est illégal ici, il s'est trouvé un vendeur illégal. Je veux savoir qui et comment lui fournit la soie navale.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, regarde ça ! Tu travailles pour le colonel D'Oyley, fiston ?";
			link.l1 = "Nous y revoilà ! Non, je travaille avec Marcus Tyrex. Il veut une part du marché de la soie pour navires, et ce constructeur naval a une peur bleue de traiter avec des gens 'inconnus'...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, tu travailles pour le Gardien du Code ! Voilà de grandes nouvelles... si tu ne mens pas bien sûr. Je me fiche éperdument des constructeurs de navires, arrête-en un - un autre viendra. Mais je me soucie de ma vieille fille. Le 'Poisson Volant' est en mauvais état. Tu me comprends ?\nApporte-moi une autre chaloupe, une neuve, et un rouleau de soie de navire, du même type dont tu parles - Billy fera une voile décente avec ça pour qu'il puisse embêter les patrouilles, ha-ha-ha ! En retour, Billy te dira tout sur le constructeur de navires et sa source de soie. Fais-moi confiance, fiston, je sais tout ce que tu veux savoir, je dois juste m'assurer que tu es un pirate honnête et pas un lèche-cul de manteau rouge !";
			link.l1 = "Une nouvelle chaloupe ? Que diriez-vous si je vous donnais assez d'argent pour l'acheter vous-même ? J'ajouterai même un supplément.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "Eh-eh, capitaine, le vieux Billy n'est pas le bienvenu en ville. Ils se souviennent trop bien de moi à Port Royal et l'idée d'être pendu parmi mes vieux amis sur ce rocher ne me plaît guère. Alors, fiston, j'attends que tu me livres une nouvelle chaloupe toute neuve. Je t'attendrai pendant trois jours au Cap Negril. Et n'oublie pas la soie !";
			link.l1 = "Très bien, Billy. Tu auras ton canot et un rouleau de soie de navire. Je reviendrai bientôt.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = "Très bien, Billy vous attendra sur la rive, capitaine. À bientôt !";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "Quoi ? M'as-tu déjà apporté un grand canot ?";
			link.l1 = "Tu es un farceur, hein, Billy ?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Alors, capitaine, qu'en est-il de ma nouvelle chaloupe flambant neuve ?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "C'est fait, Husky. Elle est livrée avec un rouleau de soie de navire dans sa cale. Tu es libre de couler ta vieille baignoire.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "Je suis toujours dessus. Attendez.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Merde alors ! C'est la meilleure nouvelle des cinq dernières années de la vie du vieux Billy ! Heh, une bonne raison de déboucher cette bouteille...";
			link.l1 = "Je vais passer. Alors, à propos du fournisseur de soie ?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Quel dommage, nous pourrions trinquer à mon tout nouveau 'Poisson Volant' ! Peu importe... Écoute-moi bien, fiston\nUne brigantine sous pavillon anglais arrive à Portland Cove au milieu de chaque mois, quelque part entre le 10 et le 15. Pas de rhum pour moi jusqu'à ma mort si elle est vraiment anglaise ! Son nom est 'Utrecht' et elle arrive du sud-ouest où se trouve Curaçao. C'est clairement un navire hollandais, capitaine, ça se voit\nToujours le même groupe de personnes les accueille sur le rivage, dirigé par le maître de cet astucieux constructeur de navires. Il est le receveur de la soie de navire que les Hollandais déchargent là. Je suis sûr que c'est la soie de navire, car seuls les Hollandais l'emballent ainsi.";
			link.l1 = "Chaque mois, as-tu dit ?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "En effet mon garçon, pas un mois de manqué depuis l'année dernière. Si tu veux discuter avec cette morose compagnie barbue, je te conseille de les attendre à Portland Cove du 10 au 15 de chaque mois, la nuit. Je le jure sur la nouvelle voile en soie fraîche de ma longue barque !";
			link.l1 = "Heh ! On dirait que mon argent a été dépensé pour une bonne raison. Bon vent, Billy, veille à protéger ton vieux derrière des patrouilles, sinon tu vas vraiment me mettre en rogne.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, le vieux Billy est sur le point de s'amuser vraiment autour des côtes de la Jamaïque ! Bon vent, capitaine ! Bonne chasse !";
			link.l1 = "Toi aussi, Billy !";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hey, matelot, tu viens d'arriver en Jamaïque, hein?";
			link.l1 = "Hm. Correct. Quel est le problème ?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Avez-vous vu quelque chose se passer en mer, là-bas ?";
			link.l1 = "Oui, j'ai. Un brigantin s'est engagé dans un combat avec une corvette de patrouille anglaise. Les Brits leur ont donné du fil à retordre, les Hollandais se sont débarrassés de leur cargaison en tentant de fuir.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Pourquoi es-tu si sûr qu'elle était hollandaise ? Aucun Hollandais sain d'esprit ne songerait même à s'approcher aussi près de Port Royal...";
			link.l1 = "Elle avait des couleurs anglaises, pourtant le nom... 'Utrecht'. Pas très britannique, hein ? Je vous dis qu'ils étaient néerlandais, peut-être même des contrebandiers. La patrouille les attendait sûrement.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Sacré nom d'une pipe !";
			link.l1 = "On dirait que tu n'es pas vraiment ravi de cela...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Attendiez-vous ce brigantin ici ?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Pourquoi le serais-je ?";
			link.l1 = "Allez. Je sais qui vous êtes. Vous êtes un contremaître du chantier naval de Port Royal et vous attendez que la cargaison très spéciale soit livrée par la brigantine.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Tu l'as écrit sur ton visage, juste là !";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh ! Les gars, c'est une patrouille déguisée ! Achevez-les et fichez le camp d'ici !";
			link.l1 = "Merde ! Attends, tu es en train de te tromper...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Être impoli, 'loup de mer'? Surveille ta langue ou...";
			link.l1 = "« Allez. Tu as l'air évidemment contrarié. Attendais-tu vraiment que ces Hollandais arrivent ? »";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Ou quoi ? Vas-tu m'enseigner une leçon de vie ?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "Et si c'était le cas ? Pourquoi cela te préoccupe-t-il ?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Pas vraiment. C'est toi qui attends ici, pas moi. Tu as l'éternité devant toi.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Oh, j'ai toutes les raisons de m'en soucier. Je sais ce qu'il y avait dans la cale du brigantin. De la soie de navire. Vous êtes ici à cause de cela, n'est-ce pas ?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Éternité ?";
			link.l1 = "Il faut une éternité pour revenir des profondeurs de la mer. Ta brigantine a été coulée par une corvette de patrouille, l'ami. Comme ça. Bien que, la guerre apporte à la fois des prix et des pertes. Je ferai un bon profit sur ce Hollandais coulé.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "Et comment exactement, je me demande ?";
			link.l1 = "Je vendrai ce qu'ils ont jeté par-dessus bord en essayant de fuir. Presque tout est perdu, mais la précieuse soie du navire flottait comme... un bouchon. J'en ai récupéré la plupart, donc je me rends en ville demain pour trouver un acheteur. On ne sait jamais où l'on gagnera et où l'on perdra.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Attends !";
			link.l1 = "Caramba ! Et maintenant ?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Combien de soie as-tu réussi à rassembler ?";
			link.l1 = "Et pourquoi cela te préoccupe-t-il ? C'est ma soie ! Ou es-tu le chien du gouverneur ? Tu es de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Garde ton épée dans son fourreau, matelot. Je ne suis ni un chien ni une balance. Nous travaillons au chantier naval local... Cette soie était pour nous et d'après ce que je comprends, tu l'as maintenant. Je vais tout t'acheter, nous avons besoin de cette soie, camarade.";
			link.l1 = "Vraiment ? Intéressant... Combien ?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Deux mille cinq cents pour un rouleau. C'est un bon prix, vous ne trouverez pas mieux.";
			link.l1 = "On dirait que j'ai eu de la chance ! J'ai "+FindRussianQtyString(i)+"Montre-moi l'argent et je donnerai l'ordre de le livrer à terre immédiatement.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Marché conclu !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim était censé livrer seulement quatre-vingts rouleaux - pas moyen que tu puisses en récupérer autant... ce qui signifie que tu essaies soit de jouer un sale jeu ici, soit... tu es un mouchard ! Les gars, tuez-le et fichez le camp d'ici !";
			link.l1 = "Putain !";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Une affaire splendide, mon pote ! Pourquoi si morose ? Inquiet pour les Hollandais au fond de la mer ? Les choses arrivent, ne t'en fais pas !";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Oui, c'est ça... Ils étaient notre fournisseur habituel. Où sommes-nous censés obtenir la soie maintenant ? Nous en manquons toujours et tout le commerce est sous le contrôle direct du colonel D'Oyley. Bah, bon sang...";
			link.l1 = "Hm... Écoute, ami, je suppose que je peux t'aider avec ça.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Ah vraiment? Et comment comptes-tu nous aider? Vas-tu nous livrer cent rouleaux chaque mois?";
			link.l1 = "Moi? Hmm, probablement pas, mais Marcus Tyrex le ferait. Avez-vous entendu parler de lui?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "Crévindiou ! Alors, tu es un pirate ?";
			link.l1 = "Non, je fais juste affaire avec eux lors d'occasions spéciales. Je sais pertinemment que Marcus reçoit constamment des lots de soie de navire et il les vend à quiconque peut se le permettre. Et je ne parle pas de 2500 pesos pour un rouleau ici, je dirais que si vous pouvez lui payer 25 doublons en or pour chaque rouleau, il vous en inondera, vous pouvez en être sûr.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Ce sont des nouvelles intéressantes... Marcus Tyrex tu dis ? En doublons seulement ?..";
			link.l1 = "Allez, mon pote, est-ce vraiment important pour toi de savoir d'où tu obtiens ta soie ? Et l'argent, c'est de l'argent, tu peux toujours échanger des pesos contre des doublons dans une banque. Alors, dois-je glisser un mot ou deux à ton sujet aux oreilles du gardien du code ? Je vais de toute façon à La Vega.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Très bien. Passons un marché. Voici nos conditions : un lot de cent rouleaux chaque mois entre le 10 et le 15. Nous vous attendrons ici... attendez, changeons le point de rendez-vous, cet endroit est compromis maintenant. Nous vous attendrons au Cap Negril, près de la ville Maroon, ce devrait être plus sûr là-bas. Le mot de passe - 'Un marchand de Lyon'.";
			link.l1 = "Marché conclu, ami. Diable de voyage que c'était ! Tyrex me paiera un ou deux doublons pour un tel acheteur ! Ha-ha ! Très bien, je dois y aller. Attendez le navire de Tyrex le mois prochain. Bonne chance à vous et à votre famille !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Tu n'auras plus besoin de leçons de vie après qu'on t'aura appris la politesse.";
			link.l1 = "Tu fais le dur, charpentier ? Très bien, attends donc pour ta brigantine, bien que cela prenne un moment.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Hé, professeur, j'ai aussi quelques leçons pour toi !";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Charpentier ? Mille tonnerres, comment le sais-tu ? K-ha ! Merde, les gars, c'est une patrouille déguisée ! Tuez-le et foutez le camp d'ici !";
			link.l1 = "Merde !";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Laisse-nous tranquilles, écaille de poisson, on n'a pas l'temps. Dégage !";
			link.l1 = "Tu es occupé à attendre un certain navire hollandais ? Bonne chance avec ça. Tu as l'éternité devant toi.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "De quoi diable parles-tu ?";
			link.l1 = "Je vois. Mais, au cas où tu l'attendrais, oublie ça. Elle ne viendra pas, grâce à une corvette de patrouille. J'ai vu à travers une longue-vue la fin d'un combat. C'est arrivé si vite et pas loin d'ici";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Encore une fois, nous n'attendons rien ni personne et...";
			link.l1 = "Ecoute, je m'en fous complètement. Je ne fais pas partie de la patrouille de la ville et je me fiche de ce que tu fais, je ne suis pas un ange moi-même. Si tu fais de la contrebande - c'est ton affaire. Tout ce que je voulais, c'était te prévenir. Bonne chance, l'ami.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Attends... Es-tu sûr que 'l'Utrecht' a coulé?";
			link.l1 = "Absolument. Elle a essayé de fuir, a jeté tout ce qu'elle avait dans ses cales, ils n'ont même pas épargné la soie précieuse du navire, mais de telles mesures drastiques ne pouvaient rien contre l'avantage de vitesse d'une corvette.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Quel dommage... et que sommes-nous censés faire sans la soie? Nom d'un chien!";
			link.l1 = "Avez-vous besoin de soie pour navire ?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Pourquoi demandes-tu, le vends-tu ?";
			link.l1 = "Je ne le suis pas, mais je connais un homme qui l'est. Il cherche un acheteur généreux et régulier. Penses-tu pouvoir convenir ?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "Et qui est cet homme ?";
			link.l1 = "Marcus Tyrex, le baron de La Vega, mieux connu sous le nom de Gardien du Code. Il reçoit constamment des lots de soie de navire, donc il en a toujours à vendre. Je suppose qu'il envisagera de vous en vendre aussi si votre prix est suffisamment élevé.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Donc, tu es un pirate ?";
			link.l1 = "Pourquoi t'en soucies-tu ? Je peux arranger un accord entre toi et Tyrex si t'as les tripes pour ça. Si non - adieu alors.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Très bien, très bien, ne te fâche pas. Bien sûr, je le fais. Je veux conclure un marché avec Tyrex. Mais qu'est-ce que tu y gagnes, toi ?";
			link.l1 = "Si vous offrez un bon prix pour la cargaison, je recevrai probablement de Marcus une somme décente pour mon aide. Alors, qu'en sera-t-il ?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Vingt-cinq doublons pour un rouleau. C'est le meilleur prix que vous pouvez obtenir, croyez-moi.";
			link.l1 = "Vingt-cinq pièces d'or ? Hm. Pas mal. Je crois que Tyrex me devra beaucoup pour un tel acheteur. Très bien, marché conclu, je lui ferai savoir. Cependant, si tu m'as menti sur le prix, alors c'est ta peau qui est en jeu.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Ne t'inquiète pas, nous sommes des gens honnêtes. Voici nos conditions : un lot de cent pains chaque mois entre le 10 et le 15. Nous vous attendrons ici... attendez, changeons le point de rendez-vous, cet endroit est compromis maintenant. Nous vous attendrons au Cap Negril, près de la ville des Marrons, ça devrait être plus sûr là-bas. Le mot de passe - 'Un marchand de Lyon'.";
			link.l1 = "Compris. Attends le premier lot le mois prochain.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Faites savoir à Tyrex qu'il peut apporter plus de cargaison cette fois, nous sommes à court de soie pour ce mois-ci.";
			link.l1 = "Je le ferai. Bon vent, ami.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoy ! Qu'est-ce qui t'amène à bord de mon navire, ami ?";
			link.l1 = "Eh, Coutelas. Marcus Tyrex m'a envoyé. Une marche vers Maracaibo nous attend.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, enfin. Alors, vous devez être mon nouveau capitaine pour ce voyage. Bien. Quel est le nom de mon nouvel amiral ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Ordres, Amiral "+GetFullName(pchar)+"?";
			link.l1 = "Nous naviguerons vers le lac Maracaibo séparément. Vous devriez y arriver la nuit et débarquer secrètement à la baie de Guajira. Attendez-moi là-bas et, en attendant, installez un petit camp. Pour ma part, je débarquerai dans le port espagnol.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Oui-oui, Amiral !";
			link.l1 = "Combien de temps cela te prendra-t-il pour y arriver ?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Cela devrait prendre environ une semaine. Un jour de moins, un jour de plus, tout dépend du vent.";
			link.l1 = "Bien. Ne perdons pas de temps alors. Je te verrai à la baie de Guajira, ami.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Oui-oui, amiral !";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Ordres, amiral ?";
			link.l1 = "Rien pour le moment. Je suis occupé avec notre opération.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Prepares un grand coffre sur le rivage. Nous y allons rassembler des armes pour nos frères emprisonnés.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Alors, qu'est-ce qu'on fait avec le Beau? Mes mains me démangent de verser du sang de Don!";
				link.l1 = "C'est plus compliqué que nous le pensions. Il a dit que les gardes de la plantation sont trop vigilants. La seule façon d'introduire des armes en douce est de les cacher dans les marchandises. Nous devrons urgemment obtenir une cargaison de café, de coprah ou de vanille - le planteur local ne traite que ces produits et rien d'autre.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Quittez le camp et rassemblez une escouade de tempête. Il est temps de marcher, nous attaquons sous le couvert de l'obscurité.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Ecoutez, Amiral, j'ai réfléchi...";
			link.l1 = "Qu'est-ce que c'est, Terrax te paie pour réfléchir au lieu d'agiter ton sabre, hein, Sabre ?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho ! Une rébellion à la plantation, n'est-ce pas, amiral ? Des flammes ! Nous allons en tirer de l'or !..";
			link.l1 = "J'ai besoin d'un coffre sur le rivage, Cutlass.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Aussitôt, Amiral !";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Aussitôt, Amiral!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Les hommes sont prêts et préparés, Amiral !";
			link.l1 = "En avant !";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Amiral, on dirait que l'ami de Tyrex que nous devions sauver est... quelque peu mort.";
			link.l1 = "Oui, mais rien ne pouvait être fait là-bas. Tu as vu les gardes, nous avons eu de la chance de rester en vie.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Amiral, Marcus sera furieux contre vous. Ne l'approchez pas en ce moment. Je m'en vais. Vous devriez faire de même.";
			link.l1 = "Ouais...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Mauvaises nouvelles Amiral. Il y a une escadre espagnole qui vient vers nous de l'Est. Nous n'avons pas le temps de fuir.";
			link.l1 = "Combien y en a-t-il ?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Trois navires. Beaucoup de canons. Nous sommes foutus."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Nous verrons.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = " "; 
		   link.l1 = "Jean, tu vas au navire de Cutlass.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Cutlass, tu devrais hisser le drapeau espagnol et déguerpir d'ici. Je vais les distraire pour toi. On se voit tous à La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Mais...";
			link.l1 = "Pas de mais ! Sabre, c'est ta peau si Picard n'arrive pas chez Tyrex. Tous à bord !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Des ordres, Amiral ?";
			link.l1 = "Préparez-vous à combattre. Attaquez-les à mon commandement !";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Oui-oui Amiral... à vos ordres!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho ! Bonjour Prince. Qu'est-ce qui t'amène à Tortuga ?";
			link.l1 = "Encore une tâche de Marcus. Ecoute, Sabre, pourquoi le salaud qui vit dans cette maison ne me laisse-t-il pas entrer ?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Dentdor? Il ne travaille qu'avec des camarades de confiance. Les autres auraient besoin de recommandations pour travailler avec lui. Tu veux vendre quelques babioles brillantes? Je pourrais me porter garant pour toi si tu veux...";
			link.l1 = "Alors c'est un usurier ? Quel est son intérêt ?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Frère, il te manque quelque chose. Gaspard n'est pas un usurier, tu devrais aller à "+GetFullName(characterFromId("Tortuga_usurer"))+"si vous en avez besoin. Dentsd'or achète des pierres précieuses et des bijoux de toutes sortes. Au fait, il paie bien et ne pose jamais de questions stupides. Chaque capitaine pirate est son client.";
			link.l1 = "Je vois... On m'a dit que certains d'entre eux lui confient même leur argent...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha ! C'était un menteur qui t'a dit ça, va lui cracher dans les yeux sans vergogne. Gaspard ne travaille qu'avec les bijoux, il l'a toujours fait. Pourquoi aurait-il besoin de problèmes avec l'argent d'autrui ?";
			link.l1 = "Je vois. Merci, Cutlass, à la mer!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, en effet. Alors, il achète des babioles ? Intéressant... Tu dis que tu peux me recommander ?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "À bientôt, Prince.";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Bien sûr ! Tu es des nôtres maintenant, héhé ! Attends ici un instant.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Tout est réglé ! Maintenant, Goldentooth sait que Charlie Prince peut venir lui vendre des babioles. Mais garde à l'esprit que son prix, bien qu'il soit bon, est toujours inférieur à ce que paient ces usuriers avares. Mais il achète tout à la tonne ! Et sans questions inutiles, comme je l'ai déjà dit.";
			link.l1 = "C'est mon beau garçon ! Bien joué Paul ! Maintenant, j'ai un endroit pour décharger tout le butin !";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "Non, Jean Picard est le 'Bel', moi je suis le 'Sabre', haha ! Adieu, Prince !";
			link.l1 = "Merci, Cutlass, bonne chance en mer !";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "J'ai trois oiseaux pour toi, Prince. Trouvés cachés dans des armoires et sous un lit. Jolies choses, non ? Ha-ha-ha !";
			link.l1 = "Je dis qu'ils le sont en effet. Et ils sont bien soignés aussi. Don Stubborn doit s'en soucier profondément.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Tous à l'abordage ! Que diable fais-tu ici, Prince ?";
			link.l1 = "Sabre?.. Je suivais les voix et le bruit, mais jamais je n'aurais pensé que ce serait toi. Comment diable as-tu atterri ici?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "Non, pourquoi es-tu ici ! Tu es toujours dans les parages ! Tyrex doit t'avoir envoyé pour ce trésor, n'est-ce pas ? Caramba, je suis en retard, encore une fois...";
			link.l1 = "Tyrex? Non... J'ai acheté une carte d'une fille de joie. Elle t'en a probablement vendu une copie aussi, hein? À Tortuga? Quelle garce rusée. Mais elle n'a pas menti - regarde cette pile d'or! Je reviendrai avec plus de monde pour transporter tout ça...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Par les entrailles de Neptune, c'est un tas d'or ! Mais ce n'est ni à toi ni à Tyrex ! C'est moi qui l'ai trouvé en premier ! C'est à moi ! Peu importe comment j'en ai entendu parler ! Cela ne te regarde pas !";
			link.l1 = "Calme-toi, Sabre, pourquoi es-tu si furieux ? Regarde ce tas - il doit y avoir un million là. Peut-être même plus ! Assez pour nous deux !";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Tu obtiens toujours la meilleure part du gâteau, Prince ! Mais pas cette fois ! Le trésor est à moi ! Je l'ai trouvé le premier !";
			link.l1 = "Merde, Paul, qu'est-ce qui ne va pas chez toi ? Ne pouvons-nous pas conclure un marché ici ? Même la moitié de cet or est une fortune. Tu n'as jamais eu une telle somme entre les mains auparavant. De plus, je pourrais un jour trouver une piste lucrative et t'en parler.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Tu veux m'abattre, Prince? Pas question! Je ne vais pas te donner une seule pièce, pas un seul écu! Tu es en retard!\nAh-ah, je vois ce que tu mijotes! Pas question que tu aies cet or!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Hilarant. Vraiment. Vous êtes un comédien, Amiral. Mais c'est vrai - Marcus n'aime pas ceux qui essaient de le rouler, comme vous. Mais il apprécie les hommes astucieux.";
			link.l1 = "D'accord, d'accord. Alors, qu'as-tu en tête ?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Quelque chose que toi et Handsome n'avez clairement pas pris en compte. Vous préparez une révolte sur la plantation. Bonne idée - si le but était de piller ou de semer le chaos. Mais...";
			link.l1 = "Mais quoi ? Vous êtes contre la révolte ? Ça vous effraie ?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Moi ? Ha ! Jamais. Mais réfléchis à ce qui se passe si le Beau rencontre sa fin durant le massacre. Que dirons-nous à Marcus ? Je vais te dire quoi - cela n'aura aucune importance ce que nous dirons. Il aura nos peaux de toute façon.";
			link.l1 = "Hmm. Alors, quel est ton plan brillant ? Nous devons le sortir d'une manière ou d'une autre.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Nous le faisons. C'est pourquoi... pourquoi ne pas l'acheter ? Off... Officiellement, c'est-à-dire. Une poignée d'or peut acheter n'importe qui parmi ces salauds - même leurs propres mères. Que dire du pauvre Jean ?";
			link.l1 = "Ha ! Sabre, es-tu sérieusement en train de me suggérer d'entrer dans une plantation et de demander à acheter Picard ? Devrais-je aussi leur dire pour qui je travaille, juste pour le plaisir ? Tu as perdu la tête ?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Aucun besoin de dire cela. En fait, tout le contraire - fais semblant d'être un marchand. Bien sûr, tu n'as pas l'étoffe pour ce rôle, mais tu ne ressembles pas non plus à un pirate. Sans vouloir te vexer, Amiral, mais c'est la vérité. Il te suffit de t'avancer vers cette plantation, d'agir avec assurance, et de demander Jean. Le propriétaire pourrait soupçonner qui tu es, mais il ne le montrera pas. Comme je l'ai dit - une poignée d'or scelle les bouches.";
			link.l1 = "Et combien nous coûterait cette... main d'or ? Toute la montagne ?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Peut-être bien. Mais mieux vaut se séparer de l'or que de ta tête. Je ne suis pas resté inactif pendant que tu étais à terre - je me suis changé en quelque chose de moins pirate et j'ai demandé des renseignements sur la plantation et son humble propriétaire.";
			link.l1 = "Et qu'as-tu trouvé, Sabre?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Les prix du marché, pour ainsi dire. Ce n'est pas la première fois qu'un prisonnier de valeur tombe entre ses mains. D'habitude, ils finissent à la potence ou pire - dans les cachots de l'Inquisition.";
			link.l1 = "Et combien les vend-il?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Pour quelqu'un d'important ? Cinq cents pièces. En doublons, bien sûr.";
			link.l1 = "CINQ CENT?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Plantations, qu'attendiez-vous?";
			link.l1 = "Pour ce prix, je pourrais équiper une petite armée ! Pourquoi diable est-ce que j'amasse un arsenal sur mon navire pour une révolte alors ? Cela suffira pour une petite guerre.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "Les armes seront utiles pour ton équipage plus tard, quoi qu'il en soit. Alors, que dis-tu ?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = " (Digne de confiance) Je dirai simplement que ce sera drôle si la récompense de Terrax est moins que ce que nous dépensons ici. Mais tu as raison - nos vies valent plus. J'ai les doublons.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Je n'ai pas ce genre de montagne d'or en ce moment.";
				link.l2.go = "Pelly_44_1";
				notification("Trustworthy", "Trustworthy");
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "Tu sais quoi, Cutlass ? Oublie ça. Sommes-nous des pirates ou non ? Et Jean ? Ou son joli minois est-il son seul atout ? Prépare un coffre - nous nous en tiendrons au plan initial.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Je serais surpris si vous le faisiez - c'est une somme énorme. Bien, lorsque vous serez prêt, ou si vous trouvez quelque chose de mieux, venez me trouver.";
			link.l1 = "Je vais m'en occuper. Attends ici.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Eh bien, Amiral, as-tu amassé assez d'or pour sauver Picard ?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Oui, je l'ai enfin fait. Espérons que cela fonctionne.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Je travaille encore dessus, Sabre.";
			link.l2.go = "exit";
			link.l3 = "Je ne vais pas donner mon argent durement gagné à ces planteurs avides ! Préparez le coffre - nous agirons comme des Gentilshommes de Fortune. C'est ma décision.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Ouah. Tu es nouveau dans notre équipage et déjà à balancer ce genre d'argent !";
			link.l1 = "L'argent n'est pas tout. Mais se prélasser dans la gloire de Terrax ? Inestimable.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "On ne peut pas contester cela. Mais comme vous l'avez dit, il ne s'agit pas seulement d'argent - il y a autre chose d'important, Amiral.";
			link.l1 = "Je suis curieux maintenant. Quoi ?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Je t'ai dit que j'ai tout étudié à propos de la plantation. Y compris quels biens sont en demande ici et circulent sur le marché. Si tu veux te faire passer pour un commerçant légitime, tu ferais mieux de te ravitailler en ceux-là au lieu de simplement balancer une pile d'or sur le bureau du planteur.";
			link.l1 = "Ça a du sens. De quels types de marchandises parlons-nous ?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Eh bien, à part les marchandises vivantes, heh-heh, le propriétaire de la plantation locale achète, échange et revend du café, de la coprah et de la vanille. Alors...";
			link.l1 = "Je dois vite faire le plein quelque part. Ou attaquer une caravane et espérer qu'elle transporte ce dont j'ai besoin.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Pas n'importe quelle caravane. J'ai du mal à m'en séparer, mais j'ai une piste gardée pour moi. Une caravane transportant exactement ce dont tu as besoin va bientôt arriver. Mais il y a un hic...";
			link.l1 = "Oh, que se passe-t-il maintenant ?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "C'est sous le drapeau français.";
			link.l1 = "Quoi?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Je comprends ta frustration, ha-ha. La décision te revient... Amiral. Tu veux les détails?";
			link.l1 = "Merde... D'accord, crache le morceau. Nous n'avons pas beaucoup de temps - si toi ou moi ne les grignotons pas, quelqu'un d'autre le fera.";
			link.l1.go = "Pelly_52";
			link.l2 = "Je ne touche pas aux Français à moins de n'avoir pas le choix. Fin de la discussion.";
			link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "Alors tu ferais mieux de commencer à rassembler toutes ces marchandises par toi-même et vite avant que Beau Gosse ne soit vendu à quelqu'un. Je ne peux pas traîner ici éternellement non plus.";
			link.l1 = "Je m'en doutais.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_52":
            dialog.text = "Ca c'est mieux! Je savais que tu avais ça en toi... Amiral. Alors, voici le marché : mon contact fiable a rapporté récemment que dans environ deux semaines, une caravane française transportant du café et des épices apparaîtra dans les eaux de la Guadeloupe. Elle est grande et bien armée, alors prépare-toi soigneusement.";
			link.l1 = "Quel autre choix ai-je.";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			//if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup")) AddQuestUserData("Roger_3", "sText", "Who would've thought that among the captains of Terrax, there'd be someone with at least the spark of a negotiator or a true entrepreneurial streak? That person turned out to be my temporary companion, Paul "Cutlass." Understanding the consequences of Marcus's wrath if we fail his assignment, Cutlass suggested... officially buying Picard from the plantation owner. While I scouted the situation and spoke with Jean, Cutlass didn't waste time either. He discovered that the plantation owner frequently sells valuable captives, with the average price for such transactions being around 500 doubloons - a small fortune. But Paul is right - it's better to do this than risk Picard being killed by a stray bullet or blade. Now all that's left is to load up on the plantation's usual trade goods - be it coffee, copra, or vanilla - in large quantities.");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Tu as l'air abattu, Amiral. Où est Beau? Est-ce que tout est parti à vau-l'eau?";
			link.l1 = "En effet. J'ai gagné de l'argent correct, mais cette mule obstinée a refusé de me vendre Picard - même pour un tas de doublons !";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Quel imbécile ! Que faire maintenant ?";
			link.l1 = "J'ai déjà arrangé avec le planteur pour décharger la marchandise. Nous devrons revenir au plan initial - c'est maintenant ou jamais !";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "Mais nous n'avons même rien préparé pour Beau et les autres !";
			link.l1 = "Pas le temps ! Montez à bord des navires - nous glisserons des armes et des médicaments de nos cales dans les sacs de marchandises. Et n'oubliez pas de hisser le drapeau espagnol !";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Ça semble être un plan.";
			link.l1 = "De toute façon, nous n'avons pas le temps pour autre chose. Bouge ! Le déchargement se fait bientôt.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Regardez qui voilà ! Beau gosse ! Et à en juger par ton visage intact et ta démarche assurée, je suppose que tout s'est déroulé sans accroc ?";
			link.l1 = "D'une facilité déconcertante - non seulement j'ai évité une bagarre et racheté Jean, mais j'ai aussi gagné un peu d'argent. Ton plan a fonctionné à merveille, Paul. Tout est calme à l'horizon ?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Silencieux comme une tombe. Tu retournes voir Marcus ?";
			link.l1 = "D'accord.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("shore37", "boat", false);
			bQuestDisableMapEnter = false;
			AddQuestRecord("Roger_3", "29");
			pchar.questTemp.Mtraxx = "plant_success";
			QuestSetCurrentNode("Terrax", "mtraxx_27");
			//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
			SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
			
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			sld = ItemsFromID("fire");
			sld.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
				}
			}
			sld = characterFromId("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
			sld = characterFromId("mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;
		
		case "Pelly_62":
            dialog.text = "Hmm, comme vous voulez, Amiral. Mais s'il arrive quelque chose à Beau, je m'assurerai que Terrax sache que vous avez ignoré mon conseil. Tout est prêt pour l'évasion ?";
			link.l1 = "Laisse-moi verifier et compter ce que j'ai dans le coffre.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Soyez-en sûr. Je peux aider pour une modeste somme et couvrir mes efforts, hé hé.";
			link.l1 = "Comment cela ?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "J'ai un contact, un trafiquant d'armes à Maracaibo. Je me déguiserai, m'infiltrerai, le paierai, et organiserai la contrebande des armes ici. Mais ça te coûtera - des doublons d'or, pour être précis.";
			link.l1 = "Et pourquoi ne m'as-tu pas présenté ce type plus tôt? Combien cela va-t-il me coûter?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Devrais-je aussi te présenter à tous mes informateurs ? Très bien. Avec les dépenses, les risques, et ma part... cela coûtera à peu près autant que la rançon pour Beau.";
			link.l1 = "Sabre, crains Dieu...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Je ne crains ni Dieu ni vous, Amiral. Mais la colère de Marcus si nous échouons à sauver Jean ? C'est une autre histoire. Alors, qu'en dites-vous ? Besoin d'aide avec le coffre ?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "D'accord, vas-y - assez de temps a déjà été perdu. Voici, cela devrait être le bon montant.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "C'est beaucoup d'argent, Paul. Je dois y réfléchir.";
			link.l2.go = "Pelly_67";
			link.l3 = "C'est beaucoup trop cher pour un petit lot d'armes que je peux acheter en gros à bien meilleur prix ! Non merci, je m'en occuperai moi-même.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Eh bien, pense à cela. Mais souviens-toi-pendant que tu réfléchis, le nombre de bleus sur le visage et le corps de Beau augmente d'heure en heure, heh-heh-heh.";
			link.l1 = "Je vous apporterai les doublons...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Ce n'est pas une question de taille de la cargaison-c'est une question de timing et de risques. Mais fais à ta guise.";
			link.l1 = "Fais-moi confiance, je sais. Prépare juste le coffre - je m'en occupe à partir d'ici.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Prêt, Amiral? Besoin d'aide avec les armes, ou êtes-vous toujours à court d'or?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Enfin assez ! Prends-le et règle ça déjà - ça commence à m'agacer.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Surveille ton ton, Sabre. Je suis prêt, mais j'ai besoin de plus de temps pour rassembler l'argent.";
			link.l2.go = "Pelly_67";
			link.l3 = "C'est bien trop cher pour un petit lot d'armes que je peux acheter en gros beaucoup moins cher ! Non merci, je vais m'en occuper moi-même.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Oh, quelle pile de doublons c'est! Mais ne t'inquiète pas - chaque pièce ira vers le plan. Sinon, Marcus me déterrerait de la tombe plus tard, heh-heh. Maintenant, va voir Handsome, Amiral, et dis-lui que tout est prêt.";
			link.l1 = "Je suis celui qui donne les ordres ici. Maintenant, bougez-vous.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Ouais, c'est un problème. Quel est ton plan, Amiral ?\nJ'ai tout examiné à propos de la plantation. Y compris les marchandises qui sont demandées ici et qui circulent sur le marché. Si tu veux te faire passer pour un commerçant légitime, tu ferais mieux de te procurer ces marchandises au lieu de simplement jeter une pile d'or sur le bureau du planteur.";
			link.l1 = "Ça fait sens. De quels types de marchandises parlons-nous ?";
			link.l1.go = "Pelly_48";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Que veux-tu de moi ?";
			link.l1 = "Mon ami, je cherche Jean Picard. Y a-t-il une chance que tu portes le même nom ?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Il y a une chance. Cependant, je ne me souviens pas de ton visage.";
			link.l1 = "Ne sois pas trop brutal, Jean. C'est Marcus Tyrex qui m'envoie. Mes ordres sont de te sortir d'ici.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Chut. Je suis désolé, ami, je ne savais pas ça. Mais nous ne devrions pas parler ici, ces foutus gardes sont partout et ils écoutent toujours... Je vois que tu es un invité bienvenu parmi les Espagnols, trouve-moi dans une des huttes la nuit et nous parlerons. Je t'attendrai, frère.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Eh bien, c'est sûr ici... Quel est ton nom, frère ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+"Maintenant dis-moi, comment as-tu fini dans cette merde. Tyrex veut tout savoir.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Un étranger m'a abordé dans une taverne de Willemstad... Il m'a demandé d'être son compagnon pour piller une caravane hollandaise. J'avais une brigantine, il avait une polacre, très unique aussi. Alors nous avons poursuivi une caravane non loin de Caracas et l'avons pillée... C'était la nuit, nous partagions le butin quand un énorme galion espagnol est apparu dans l'obscurité\nMon compagnon a fui, et moi aussi. Mais il n'y avait aucun moyen pour ma brigantine endommagée d'échapper à un galion et deux autres navires. Ils nous ont abordés et ont vendu tous les survivants à cet endroit comme du bétail.";
			link.l1 = "Je vois. Tu penses que c'était un accident ? Je parle du galion.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Diable si je savais. Ils ont peut-être entendu une fusillade, ce n'était pas loin du Main.";
			link.l1 = "Hmm. C'est possible. Aviez-vous rencontré votre ancien compagnon auparavant ? Qui est-il ?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Jamais rencontré auparavant. Il a dit que son nom était Ignacio Marco, un corsaire d'Angleterre. Il a fait l'impression d'un homme sérieux, c'est pourquoi j'ai accepté de participer à cette entreprise. C'est un marin aguerri et un capitaine, c'est certain, il a un équipage audacieux derrière lui et son polacre est une beauté, on ne voit pas un navire comme celui-là tous les jours.";
			link.l1 = "Ignacio Marco ? Un corsaire anglais ? Est-il espagnol ?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "Il est Portugais, pas Espagnol. Qu'y a-t-il de mal avec une lettre de marque britannique ? Nous avons beaucoup d'Espagnols parmi nous, tu le sais.";
			link.l1 = "Je vois. Bien, parlons de votre évasion d'ici. Des idées ?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Quels sont vos effectifs ?";
			link.l1 = "Mon navire, une barquentine et les hommes de Pelly le Sabre. Mon vaisseau est stationné au port de Maracaibo. Le Sabre a accosté à la baie de Guajira et y a installé un camp.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "Quoi, vous vous attendiez à ce que Tyrex envoie un vaisseau de ligne ici ?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Je ne m'attendais à rien. En fait, je suis surpris que Marcus ne m'ait pas oublié.";
			link.l1 = "Il ne l'a pas fait, évidemment. Alors, des idées ?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "Aucune chance de s'échapper d'ici - cette plantation est trop bien gardée et il y a des jungles sauvages autour. Inutile de l'attaquer non plus, vous n'avez pas assez d'hommes, de plus il y a un fort à proximité.";
			link.l1 = "Peut-être que toi et tes gars pourriez nous aider de l'intérieur ? Frappez-les fort par derrière.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Avec quoi ? Des mains nues et des machettes rouillées ?";
			link.l1 = "Et si vous aviez des armes ?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Eh bien, dans ce cas, nous leur aurions donné un enfer. Cependant, il y a un problème, ils vérifient tout ce que tu apportes à l'intérieur, il n'y a aucun moyen de faire passer des armes en contrebande. Je te suggère donc d'oublier cela.";
			link.l1 = "Et pourtant, c'est notre meilleure option pour le moment. Je vais réfléchir à comment vous livrer, à vous et vos hommes, des armes... Dites-moi, combien d'entre vous sont capables de se battre ?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Trente têtes, je dirais.";
			link.l1 = "Trente sabres alors... Des pistolets feraient également une différence, je crois.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Capitaine, es-tu sérieux à ce sujet?";
			link.l1 = "Je le suis. Je suis arrivé ici exprès, plaisanter n'en fait pas partie. Que pourrais-tu utiliser d'autre ?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Très bien... Essayons au moins. Nous avons besoin de simple acier froid - mes gars ne sont pas formés à manier des rapières sophistiquées ou autres. On peut en dire autant des pistolets, les moins chers feront l'affaire. Si tu nous trouves un mousquet ou deux, cela nous serait d'une grande aide, j'ai quelques gars qui se débrouillent bien avec les mousquets. Balles, poudre à canon. Les potions de guérison sont les bienvenues.";
			link.l1 = "Compris. Les lames et les haches peuvent être prises de l'arsenal du navire. Le reste est plus difficile à obtenir. Je te ferai savoir quand j'aurai tout.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Dépêche-toi, frère. Nous n'avons pas une demi-année ici, ce fichu travail de bétail nous tue un par un. Si tu as besoin de moi - viens me voir la nuit.";
			link.l1 = "Compris, l'ami. Tiens bon, je vais essayer de ne pas te faire attendre. Et sois prudent, ne leur donne pas encore de raison de t'écarter.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Des nouvelles, camarade ? As-tu rassemblé des armes ?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Oui. Un coffre avec des munitions se trouve à la baie de Guajira. Il ne reste plus qu'à trouver un moyen de le faire entrer discrètement dans la plantation.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Je m'en occupe. Attendez.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Très bien, capitaine. J'ai déjà réfléchi à la manière de m'y prendre.";
			link.l1 = "Content de l'entendre. Qu'avez-vous en tête ?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "Ils produisent du sucre et cultivent des fèves de cacao sur cette plantation. Parfois, son directeur vend lui-même les marchandises, c'est plus rentable ainsi. Fais-lui une offre. Paie-le non pas avec de l'argent mais avec des marchandises. Quelque chose que tu peux mettre dans des caisses comme du coprah, de la vanille ou du café. Fais un effort pour marchander mais n'en fais pas trop\nCache des armes dans une ou deux caisses et mets des marques dessus. Organise un échange le soir pour qu'ils soient obligés de laisser les caisses dehors pour la nuit\nLa nuit, nous trouverons tes caisses marquées, nous nous armerons et nous donnerons l'enfer aux Espagnols. Avec ton aide bien sûr.";
			link.l1 = "Bien pensé, frère ! Très bien, j'aime ce plan. Restons-en là.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Une dernière chose - proposez un seul type de marchandises à échanger. Plus de types de marchandises - plus de caisses vérifiées par les gardes.";
			link.l1 = "Je suis d'accord. Je ne prendrai qu'un seul type alors. Café, vanille et coprah, tu as dit ?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Oui. Cela semblera une bonne affaire pour le chef de la plantation.";
			link.l1 = "Compris. Je te ferai savoir quand l'affaire sera conclue.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Va mon ami, le temps est précieux et nous n'en avons pas...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "... ";
			link.l1 = "(à voix basse) L'affaire est conclue. Les caisses seront livrées à la plantation demain soir. Les caisses dont vous avez besoin sont marquées d'une lettre 'W'. Les autres portent le reste de l'alphabet. Préparez vos hommes. Nous attaquerons avant l'aube, vers trois heures.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "Nous commencerons par votre signal...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Enfin ! Je vais revoir la mer ! J'ai déjà oublié son apparence et son odeur. Bien joué, capitaine ! Je vous dois une fière chandelle.";
			link.l1 = "Ne t'en fais pas, nous réglerons ça plus tard... Maintenant, embarquons et tirons-nous d'ici !";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Salutations "+pchar.name+"Ravi de te revoir, et aussi content de t'avoir comme compagnon dans cette aventure. Ce boulot va être rude mais je suis sûr qu'on s'en sortira.";
			link.l1 = "Content de te revoir Picard. Je suis tout ouïe, parle-moi de ton aventure.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Je l'ai déjà dit à Marcus, maintenant je te le dis. Quand j'étais esclave à la plantation de Maracaibo, j'ai appris quelque chose des Espagnols. Ils sont assez bavards quand ils sont ivres... Écoute, au sud-est de la baie de Maracaibo, il y a un petit village. Il est caché entre deux montagnes, profondément dans la jungle. Nom d'enfer qu'il a : Santiago-de-Los-Caballeros-de-Merida. Appelons-le Merida\nCela ne semble pas très intéressant pour le moment, hein? Les montagnes entourant le village se sont avérées riches en pierres précieuses. Émeraudes, opales et légendaires opales de feu\nAutant que je le comprends, les colons de Merida n'ont pas informé le gouverneur général de ces pierres précieuses. Cependant, il l'apprendra bientôt, c'est pourquoi nous devrions visiter Merida avant l'arrivée des officiers coloniaux espagnols.";
			link.l1 = "Veux-tu piller la colonie ?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Exactement. Il est perdu parmi les jungles et les montagnes avec une petite garnison - une proie facile pour une unité corsaire. De plus, ils sont loin de la mer, ils ne s'attendent pas à ce que quelqu'un les attaque, sauf des sauvages avec des lances et des arcs.";
			link.l1 = "Combien es-tu sûr que la colonie possède des pierres précieuses ?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Si nos aventures s'avèrent être une fausse piste, je servirai moi-même sur votre navire comme officier ou comme matelot, je nettoierai les ponts et combattrai dans d'innombrables abordages jusqu'à ce que ma dette envers vous et Marcus soit effacée.";
			link.l1 = "Je vois... Très bien, savez-vous comment se rendre à Mérida ?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Bien sûr, je ne connais pas le chemin exact à travers les jungles, mais nous engagerons un guide parmi les indigènes. Nous devrions débarquer au sud du lac Maracaibo, trouver un village indien et ceux qui savent comment y parvenir.";
			link.l1 = "... ";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Capitaine, je suis profondément désolé pour mon langage, mais pourquoi diable ne sommes-nous pas encore à Mérida ? Hein ? Vous avez craché sur notre cause commune ! Leprechaun et moi partons sans vous. J'expliquerai tout à Tyrex et vous devriez partir. Tenez, prenez 50 000 pesos pour votre aide à Maracaibo, je les ai empruntés à des amis. Adieu, sacrée honte, je pensais mieux de vous.";
			link.l1 = "Hmm... Je suis désolé.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Nous y voilà. Les jungles sont devant nous. Tout d'abord, nous devrions trouver un village indien et demander un guide.";
			link.l1 = "Faisons-le. Luke, as-tu quelque chose à dire... ou peut-être un conseil ?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "La garnison de Merida est finie. Je ne m'attends pas à une résistance sérieuse à l'intérieur du village. Allons-y !";
			link.l1 = "À l'abordage !!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "C'est fait ! Plus de héros. Maintenant, nous devrions parler au gouverneur de cette 'cité'. J'espère qu'il est du genre à se laisser convaincre.";
			link.l1 = "Je suis d'accord, 'persuadons'-le!.. Jean! Suis-moi!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Bien joué, "+pchar.name+" ! Il est temps de partager le butin. J'ai déjà fait les comptes. Il y avait presque 2000 gemmes dans le coffre : 1560 émeraudes, 1032 opales et 363 opales de feu. Ta part est le tiers : 350 émeraudes, 244 opales et 63 opales de feu. Tiens, prends-les.";
            }
            else
           	{
           	dialog.text = "Bien joué, "+pchar.name+" ! Il est temps de partager le butin. J'ai déjà les chiffres. Il y avait presque 2000 gemmes dans le coffre : 1050 émeraudes, 732 opales et 189 opales de feu. Ta part est le tiers : 350 émeraudes, 244 opales et 63 opales de feu. Tiens, prends-les.";
           	}
			link.l1 = "Chouette !";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Maintenant parlons de ma dette envers vous pour mon sauvetage. Je comprends que vous avez eu des dépenses sérieuses. Quelle compensation considérez-vous comme équitable ? Je paie avec ma part de gemmes.";
			link.l1 = "Un tiers de ta part suffira. Toi aussi, tu as besoin d'argent - pour acheter et équiper un navire, pour payer ton équipage...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Merci, ami ! Je pensais que tu demanderais pas moins de la moitié. J'ai vraiment besoin d'argent maintenant. Tiens, prends les gemmes.";
			link.l1 = "Quel raid Jean ! Allons à Hispaniola, chez Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Oh, quelle rencontre ! Plaisir de vous voir, "+pchar.name+". Comment vas-tu ?";
			link.l1 = "Plutôt bien. J'ai récemment trouvé les trésors du Loup Rouge. Maintenant, je me dirige vers la Martinique pour rencontrer un ami commun à nous. Tu veux voir Tyrex?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Ouais. Je veux lui parler à propos de Pasquale Lavoisier. Marcus m'a envoyé chez ce demi-bandit, demi-marchand. J'ai fait ce qu'il a demandé et il a payé avec des merdes en prétendant que c'était un sacré bon paiement. Je l'aurais tué sur place, mais Marcus a demandé de le traiter avec respect... alors c'est à lui de gérer ce problème.";
			link.l1 = "Je suis désolé mais Marcus ne fera rien. Quatre-yeux est en affaires avec lui.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Putain de merde ?";
			link.l1 = "Oui, mais je ne t'ai rien dit à ce sujet, d'accord ? Lavoisier m'a aussi embobiné il n'y a pas si longtemps. Tyrex m'a demandé de l'aider, tout comme il t'a demandé. On m'a prévenu à Isla Tesoro que se frotter aux quatre-yeux, c'est comme se frotter à Marcus. Alors je te conseille d'oublier ça. Tu n'es ni le premier ni le dernier dans ce cas.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Je vois. Toi aussi, tu t'es fait avoir par ces deux-là alors ?";
			link.l1 = "Eh bien, oui. Je pensais lui causer des ennuis aussi avant d'en apprendre davantage sur lui. Ça ne vaut pas le coup.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Essayerais-tu de rembourser le salaud si tu savais que personne ne le découvrirait jamais ?";
			link.l1 = "Ha ! Bien sûr que je le ferais ! Bien que je ne sache pas comment. Attaque les flutes de Lavoisier et un beau jour, tes marins se saouleront et déballeront tout. Ne sais-tu pas comment ça fonctionne ?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Vous vous dirigez vers la Martinique maintenant ? Quand arriverez-vous à nouveau à La Vega ?";
			link.l1 = "Marcus m'a donné trois semaines.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Essaye de le faire en deux. Je vais y réfléchir... Trouve-moi dans la baie de Gonaives dans 14 jours. Dirige-toi directement là-bas, et n'entre pas à La Vega.";
			link.l1 = "Je vois que vous préparez quelque chose, ha-ha. Très bien. Je vais essayer.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Tu ferais mieux de faire cela. A bientôt !";
			link.l1 = "... ";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Où est ton navire ? Es-tu arrivé ici depuis La Vega ? Merde ! Je t'avais demandé de venir ici incognito et en secret. Mon plan est gâché maintenant. Nom d'un chien !..";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Te voilà, "+pchar.name+"  C'est bien que vous soyez là. Renvoyez vos compagnons au navire. C'est une conversation privée.";
				link.l1 = "Très bien.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Te voilà, "+pchar.name+" . C'est bien que tu sois là. J'ai une affaire pour toi. Prêt à l'entendre ?";
				link.l1 = "Bien sûr !";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Je t'ai déjà dit - renvoie tes officiers !";
				link.l1 = "Oui-oui, j'ai compris.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Parfait. Maintenant, nous pouvons parler librement. J'ai une affaire pour toi. Prêt à l'entendre ?";
				link.l1 = "Bien sûr !";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Connais-tu bien La Vega ?";
			link.l1 = "Eh bien... Je pense que oui. Pourquoi demandes-tu ?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Tu as déjà remarqué l'entrepôt à droite du magasin local ? La seule grande maison parmi les cabanes.";
			link.l1 = "Celui qui est toujours fermé ? Oui, je l'ai vu. Qu'en est-il ?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Bien vu - elle est toujours fermée. Pendant que tu étais en mission à la Martinique, notre ami commun Lavoisier a séjourné ici trois jours en tant qu'invité de Marcus Tyrex. Ils passaient leur temps dans cette maison à boire du rhum et à s'amuser.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Puis les hommes de Lavoisier ont traîné quelques caisses et colis dans la maison. Ensuite, il est parti. Quant à Marcus, il reste à cet endroit chaque jour pendant plusieurs heures.";
			link.l1 = "Des suggestions?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Quelles suggestions ? Je suis sûr que cette maison doit être une base de Lavoisier à La Vega. Je n'ai pas vu grand-chose à travers la fenêtre mais il y a des marchandises entreposées là. Je pense que le binoclard a les moyens de rembourser ce qu'il nous doit.";
			link.l1 = "Eh bien, eh bien... Tu veux forcer l'entrée ? Et la porte fermée ? Elle est lourde et robuste, impossible de la forcer discrètement.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", me prends-tu pour un idiot ? J'ai déjà réglé ça. J'ai fabriqué la clé en utilisant un moule en cire de la serrure. Ça m'a coûté un joli sou, mais c'est mon problème.";
			link.l1 = "Eh bien! Pourquoi m'attendre alors ?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Ce sera plus sûr ainsi, d'ailleurs tu es le seul en qui je puisse avoir confiance. Une tête c'est bien, deux têtes c'est mieux, et quatre yeux valent mieux que deux.";
			link.l1 = "Eh bien, oui, croiser Lavoisier nécessitera autant d'yeux qu'il en a, ha-ha-ha ! Mais qu'en est-il de Tyrex ? Et s'il entre dans la maison pendant que nous vérifions les affaires de Pasquale ?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Il ne le fera pas. Il est toujours de retour chez lui avant minuit. Prêt à partir pour La Vega la nuit prochaine ? Ils ne réaliseront jamais qui les a bousillés : tu es toujours à la Martinique et j'ai quitté La Vega il y a une semaine.";
			link.l1 = "J'adorerais baiser cet enculé à quatre yeux. Mais dis-moi Jean, comment sommes-nous censés transporter les tonneaux et les coffres depuis la maison ?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Je suis sûr que nous y trouverons des objets plus précieux que des coffres et des barils de marchandises, qui seront beaucoup plus légers. Alors, tu es partant ?";
			link.l1 = "Enfer oui, je le suis !";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Super, je suis content de ne pas m'être trompé sur toi. Reposons-nous maintenant, nous mettons le cap sur La Vega à minuit.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Il est temps de partir. Nous devrions dépouiller ce salaud et foutre le camp d'ici avant l'aube.";
			link.l1 = "En avant !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Chut... Maintenant, avancez, en silence, vers la maison de Pasquale. Suivez-moi.";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Regarde ça - tellement de bric-à-brac qui traîne. Commençons. Vérifie un coffre près de la porte, puis monte à l'étage et occupe-toi d'une chambre. Je vais rester ici : je connais les astuces pour cacher des trésors parmi les ordures. Garde les yeux et les oreilles ouverts et reste loin des fenêtres.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", qu'as-tu? Quelque chose d'intéressant?";
			link.l1 = "Viens voir. C'est quelque chose.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Bon sang ! Maintenant je comprends pourquoi Tyrex vient ici chaque jour. Ce n'est pas seulement l'entrepôt du binoclard, mais aussi un bordel.";
			link.l1 = "On dirait qu'elle est une esclave ici.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Bien sûr. Regarde-la - c'est une prostituée de port évidente... Mauvaise chance pour nous. Nous devons la tuer.";
			link.l1 = "Vraiment ?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Elle a vu nos visages et entendu ton nom. Elle dira tout à Tyrex.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "C'est ton choix. Sa vie peut te coûter la tienne.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "N'y pense même pas à faire confiance à cette putain. Demain, Tyrex saura tout. Tu veux recevoir une marque noire ?";
			link.l1 = "Non, je ne le fais pas. Et je ne veux pas tuer la garce - j'ai besoin d'elle. Elle vient avec moi.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Ne sois pas idiot ! Elle s'enfuira dès qu'elle en aura l'occasion. Regarde son front, vois-tu la marque ? C'est une voleuse.";
			link.l1 = "Hm. Tu as probablement raison, Jean. Très bien, achève-la et partons d'ici.";
			link.l1.go = "rocur_82";
			link.l2 = "Je n'ai pas l'intention de la garder sur mon navire. J'ai un endroit pour elle d'où elle ne s'échappera jamais, et il n'y a pas d'oreilles pour entendre ses cris non plus. Elle continuera son boulot là-bas... Une catin personnelle, sans frais, hé-hé !";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "C'est fini, il n'y a aucune chance qu'elle dise quoi que ce soit à Marcus maintenant...";
			link.l1 = "Pauvre fille... ah bien comme on dit, la chance est une garce...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Tu es un homme bon, "+pchar.name+". Pourquoi veux-tu t'embêter avec elle ? Ah, peu importe, c'est ton choix. Assure-toi qu'elle reste silencieuse pendant que nous partons.";
			link.l1 = "Si elle ne le sera pas - elle est morte.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "Qu'as-tu trouvé ?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "Plus de chance de mon côté. Tiens, prends ta part. Je ne pourrais jamais tout emporter avec moi à terre. Le binoclard nous a payé intégralement.";
			link.l1 = "Splendide! Bien joué, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Maintenant, va!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Parfait. C'est fait. Discret et silencieux. Allons, retournons aux navires.";
			link.l1 = "Hah, bonne idée.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Eh bien, "+pchar.name+". Il est temps que nous nous séparions. Je ne suis pas sûr que nous nous reverrons un jour, mais sachez que ce fut un plaisir de vous connaître, ami.";
			link.l1 = "Ah allons, nous nous verrons souvent à La Vega.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "Non. J'en ai fini avec Tyrex. Ce bazar avec Lavoisier a été la goutte d'eau.";
			link.l1 = "Hmm... Je vois, oublie ça. Nous avons récupéré ce qui nous revenait de droit. Tyrex donne des pistes profitables, n'est-ce pas? La dernière fois, j'ai gagné plus d'un demi-million grâce au trésor de Red Wolf.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Dis-moi alors, as-tu mis beaucoup d'efforts pour le trouver ?";
			link.l1 = "Eh bien... Ce n'était pas facile. J'ai beaucoup réfléchi, voyagé et combattu. Ça en valait la peine, je pense.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Combien as-tu payé à Tyrex ?";
			link.l1 = "Un tiers.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Quel était son rôle dans cette affaire ? Qu'a fait Marcus exactement ?";
			link.l1 = "Hm... Il m'a donné le journal de bord du Loup Rouge...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "Et c'est tout? D'accord?";
			link.l1 = "Eh bien... Je n'aurais jamais appris l'existence du capitaine Wulfric autrement...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", ne vois-tu pas que Tyrex fait faire le sale boulot par les autres ? Tu penses qu'il te donnerait la mission de trouver ce trésor s'il pouvait le faire lui-même ? Que non ! Je parie qu'il a essayé de le faire d'abord lui-même et quand il a tout foiré, il t'a appelé pour faire le boulot. Et pendant que tu réfléchissais, passant des semaines en mer, te battant et risquant ta propre vie, ce salaud avec son ami dégoûtant à quatre yeux baisaient la pute à La Vega. Et pour cela, il a aussi reçu un quart de million de pesos. Comme ça\nTu penses qu'il a envoyé son chien Leprechaun pour nous aider dans notre raid pour Merida ? Non, il voulait s'assurer que ses intérêts soient en sécurité. Tout ce que Marcus peut faire par lui-même, il le fait, soit seul, soit avec l'aide des Sabres, des Chauves, des Lutins et d'autres idiots qui travaillent pour lui pour des clopinettes. Les gens comme toi et moi, nous recevons des pistes que Marcus est trop stupide pour exécuter par lui-même\nSouviens-toi de toutes les tâches que tu as faites pour lui ? Compte combien il a gagné sur ton dos. J'en ai assez de ça. Maintenant j'ai l'argent, une superbe corvette, et un équipage loyal... à partir de maintenant je suis un mercenaire. Je me dirige vers la Jamaïque, peut-être que je recevrai une lettre de marque là-bas.";
			link.l1 = "Je ne pense pas que tu aies tout à fait raison à propos de Tyrex... Mais je te souhaite bonne chance Jean ! J'espère que tu trouveras le succès en Jamaïque.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "Je le ferai. Bonne chance à toi aussi et réfléchis à ce que je t'ai dit. Être le larbin de Marcus n'est pas le meilleur rôle pour toi, je sais que tu es capable de bien plus. Eh bien... adieu frère ! Bon vent !";
			link.l1 = "Bonne chasse, Jean !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", dis-moi, comment avons-nous passé autant de temps dans les jungles? Maintenant mon plan est fichu. Eh... Adieu, l'ami...";
			link.l1 = "Hé hé...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Il est temps de partir, les gars. Diable, Prince, tu m'as surpris. Tu as brûlé toute une ville, mais tu as refusé de te salir les mains quand c'était important.";
				link.l1 = "Je n'ai pas ordonné de brûler la ville !";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Il est temps de partir, les gars. Lucas, tu as raté ça. Le Prince s'en est sorti brillamment – et a fait un bon bénéfice !";
				link.l1 = "Et la ville, Beau?! J'ai donné ma parole!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "Au moins, tu n'as pas essayé de le sauver. Sinon, nos hommes t'auraient étripé en premier. Ça a été une journée difficile pour eux. Ils méritaient de se défouler un peu. Tu t'y habitueras. Tu as tout ce qu'il faut pour ça.";
			link.l1 = "Merci pour le conseil, mais je ne me souviens pas l'avoir demandé. Allons-y.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Je pensais que tu plaisantais. Eh bien... tu as été trop pressé. La ville est finie. C'est toujours ainsi quand la Confrérie de la Côte se met au travail. Tu t'y habitueras.";
			link.l1 = "Je ne suis pas sûr de le faire. Très bien, allons-y.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Camarade... qu'est-ce que c'était à l'instant ?";
			link.l1 = "Quoi, tu n'as pas compris ? Je t'ai acheté. Tu as dit une fois que j'avais accès aux Espagnols, alors j'en ai profité.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "J'ai compris - je ne suis pas un idiot. Mais ne travaillions-nous pas sur un autre plan ?";
			link.l1 = "Eh bien, Cutlass et moi avons pensé que ça ne serait pas bien si tu finissais mort lors d'un soulèvement ou d'une poursuite, alors nous avons décidé de t'acheter directement.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, ne m'insulte pas. Je suis l'un des capitaines de Terrax, après tout. Je sais manier une lame.";
			link.l1 = "Je n'en doute pas, mais es-tu vraiment contrarié d'être libre ?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "Non, non - je suis reconnaissant. C'est juste... n'était-ce pas un peu excessif de dépenser tout cet or ? J'en ai la nausée rien que d'y penser. Le planteur, par contre, avait l'air aussi brillant qu'un plateau d'argent poli.";
			link.l1 = "Oui, 'Le Marché du Siècle,' en effet. Ça pique un peu, c'est sûr. Mais le temps est plus précieux que l'or, Jean. Chercher des pistolets et des médicaments pour vous tous...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "Je suis reconnaissant, mais compagnon, tu es un imbécile - sans vouloir t'offenser. Je t'ai dit que mes gars ne sont pas doués avec les épées. Mais n'importe qui peut appuyer sur une gâchette. Tu aurais pu apporter n'importe quels pistolets et médicaments de la cale, comme pour les coutelas et les haches - ils ne sont pas difficiles.";
			link.l1 = "Hmm, honnêtement, je n'y avais pas pensé... Quoi qu'il en soit, allons-y - le Sabre doit probablement commencer à s'impatienter.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Salutations, capitaine "+GetFullName(pchar)+"Luke le Farfadet est à votre service ! On m'a dit que nous allons dans les jungles du Sud de la Terre Ferme.";
			link.l1 = "Précisément. Embarquez sur les chaloupes, nous partons sur-le-champ.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Laisse un vieux boucanier te donner un conseil, capitaine. Puisque nous nous dirigeons vers la selva - nous rencontrerons sûrement les Indiens. Emporte avec toi des présents pour eux. Les guerriers indiens adorent les beaux pistolets, surtout ceux de duel. Ils aiment aussi les boussoles et les longues-vues. Ils les considèrent comme des objets magiques\nLeurs femmes préfèrent les bijoux bon marché et les colifichets comme les miroirs et les coquilles. Si nous avons une escarmouche avec eux, utilise des tromblons et des arquebuses : la mitraille en général est très efficace contre ceux qui ne portent pas d'armure. Quant à l'établissement lui-même, je recommande les armes qui peuvent utiliser des cartouches en papier.";
			link.l1 = "Très bien, Luke. Tes paroles sont notées. Bienvenue à bord.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "Vois le chef dès notre arrivée au village. Et apporte des cadeaux, sinon c'est inutile. Assure-toi de demander si quelqu'un parmi son peuple connaît des passages secrets dans la jungle devant, et demande ceux qui n'ont pas peur de voyager. Je viens avec toi, adresse-toi à moi en cas de difficultés.";
			link.l1 = "Allons-y ! Jean, Luke - suivez-moi !";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Des questions, capitaine ?";
			link.l1 = "Aucun pour l'instant, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Oui ! J'ai parlé avec leur chef, je lui ai offert un cadeau et plus tard, il a convoqué ses peaux-rouges pour une réunion. Il y en a parmi eux qui savent comment se rendre à Merida mais personne n'est prêt à y aller - ils craignent une autre tribu appelée Capongs. Ceux-là terrifient les locaux à mort. Le salaud de peau-rouge prétend que nous n'avons aucune chance de trouver le chemin par nous-mêmes et qu'il n'y a pas de guide à engager. Alors, qu'est-ce qu'on est censé faire maintenant, hein ?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "J'ai des antidotes avec moi.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, je vois... Capitaine, vous devez savoir que la lachete est souvent vaincue par l'avidite. Promettez une recompense si genereuse qu'un homme acceptera le travail... Vous savez quoi? Essayez une option plus rusée - leurs femmes. Offrez-leur des cadeaux et demandez à propos de leurs hommes et il y a de grandes chances que vous trouviez le guide dont nous avons besoin. Promettez-lui des tas de perles et de miroirs pour l'aide de son mari. Soyez genereux et promettez beaucoup, persuadez-les.";
			link.l1 = "Hé ! Eh bien, le moins que je puisse faire, c'est essayer, bien que je ne sois pas sûr que cela fonctionnera...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Eh bien, il y a une autre option... Mais ce n'est pas exactement la meilleure, si tu vois ce que je veux dire.";
			link.l1 = "Une autre option ? Vas-y, raconte ! Je ne suis pas trop chaud pour aller voir les femmes indiennes et les supplier de convaincre leurs maris de nous rejoindre.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Cette option est aussi vieille que le monde. Montre-leur qu'ils devraient te craindre plus qu'ils ne craignent les Kapongs. Tu sais... Tu pourrais dire au chef ce que tes pirates pourraient faire à toutes les femmes du village, surtout à sa femme et ses filles. Tu pourrais même ajouter quelques menaces de torture. \nQuoi qu'il en soit, je suis sûr que tu trouveras quelque chose pour faire en sorte que ces Indiens te craignent. Personnellement, je ne suis pas fan de cette voie, et il y a des raisons à cela.";
			link.l1 = "Des raisons ? Comme quoi ? Dans mon livre, cela me semble être une solution assez efficace et directe.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Pour commencer, nous ne serons pas exactement les bienvenus en ville après cela. Nous pourrions finir par tomber dans un piège ou une autre situation désagréable. Et deuxièmement, eh bien... cela ne me semble tout simplement pas correct. C'est une chose d'éliminer des adversaires armés, mais c'en est une autre de menacer des femmes. Je suggérerais de trouver un moyen de gérer les Indiens de manière plus... diplomatique.";
			link.l1 = "Compris, je vais y réfléchir. Peut-être que je tenterai de séduire une demoiselle avec des perles... Ou alors, je trouverai des façons imaginatives de torturer les filles du chef, haha !";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Encore une chose capitaine, d'après le chef, nous pourrions rencontrer une tribu hostile d'Indiens dans la jungle, il est très probable qu'il s'agisse simplement d'un petit groupe de cannibales, mais mieux vaut prévenir que guérir. Si c'est une tribu guerrière, ils empoisonneront leurs armes, alors assurez-vous de fournir à vos hommes des antidotes\nMoi et mes hommes avons toujours beaucoup de potions avec nous. Quant à vos pirates... Apportez-moi simplement les antidotes et je veillerai à ce qu'ils soient distribués parmi vos hommes. J'ai besoin d'au moins une douzaine de potions pour cela. Assurez-vous d'en apporter aussi pour vous et vos officiers.";
			link.l1 = "Bien. J'apporterai les antidotes.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Très bien. Donne-les-moi. Je ferai le reste.";
			link.l1 = "Là...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Quarante-deux potions suffiront. Le reste, tu devrais le garder pour toi.";
			link.l1 = "D'accord...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Capitaine, vos Indiens - Hayami et Tagofa ont attendu trop longtemps que vous leur livriez les cadeaux que vous leur aviez promis et sont partis vers un autre village pour danser et boire du kasheeri. J'ai le sentiment que votre manière de faire des affaires ne nous apportera rien de bon. Je suis désolé, mais vous êtes hors de cela. Picard dirigera l'expédition.";
			link.l1 = "Allez tous vous faire foutre alors!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Capitaine, que diable ? Nous avons perdu trop de temps pour rien ! J'ai l'impression que votre manière de faire des affaires ne nous mènera à rien de bon. Je suis désolé, mais vous êtes exclu de cela. Picard dirigera l'expédition.";
			link.l1 = "Allez tous vous faire foutre alors !";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Capitaine, qu'est-ce que c'est que ce bordel ? Vous aviez dix jours pour trouver du cuir et des planches. Il y a la ville de Maracaibo pas loin d'ici ! J'ai l'impression que votre manière de faire des affaires ne nous mènera à rien de bon. Je suis désolé, mais vous êtes hors de ça. Picard dirigera l'expédition.";
			link.l1 = "Allez tous vous faire foutre alors !";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Capitaine, je suis désolé mais je devais être à La Vega il y a longtemps, tout comme vous en fait. Vous avez dû oublier mon existence et celle de Marcus. Quoi qu'il en soit, je pars. Vous devriez continuer à faire ce que vous faites et j'expliquerai tout à Marcus. Adieu, c'est dommage, je pensais mieux de vous.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Alors, si je comprends bien, vous vous êtes disputés. Vous n'avez pas réussi à partager le butin, n'est-ce pas Charlie Prince ?";
			link.l1 = "Leprechaun ? Vous êtes ici... Pas de grande surprise pourtant. Oui, ces enfoirés cupides avaient craché sur le Code et essayé de me tuer.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Ouais, ils t'ont bien amoché, Prince. Tu ressembles à de la merde mouillée\nQu'as-tu dit à propos du Code ? Laisse-moi t'éclairer : j'ai travaillé avec Marcus, qui est censé être le Gardien de ce Code, j'ai vu des hommes cracher dessus tant de fois que je n'oserais pas les compter. Certains de ces hommes ont payé un prix terrible. Certains d'entre eux non\nTu peux faire tout ce que tu veux, si la récompense le couvre. Surtout si personne ne regarde.";
			link.l1 = "Alors... vous êtes ici pour le trésor aussi ?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Quelle question stupide. Que ferais-je d'autre ici, si loin de ma patrie en Hispaniola ? Bien que, après tout, je sois plus malin que vous tous : connaissant votre nature pourrie de pirates. Je n'ai fait qu'attendre, vous laissant, sales rats, vous déchirer les uns les autres, ne laissant qu'un seul ennemi en vie, mais blessé et fatigué.";
			link.l1 = "Ennemi ? C'est ainsi que tu suis le Code de ton patron ?! Il tue des gens pour ça !";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Je ne suis pas soumis au Code Prince, je ne suis pas un pirate. Je ne possède même pas de navire - j'ai dû louer une barcasse pour venir ici. Je ne suis rien de plus qu'un boucanier en un mot. Je suis un chasseur, je chasse les buffles et fais du boucan. Ces maudits Espagnols qui prétendent que nous, les boucaniers français, gâchons leur existence, m'ont poussé à chercher soutien et protection auprès de Marcus. Je l'aide dans ses affaires pour cela parfois\nBien que je ne sois pas un pirate, mes hommes et moi nous battons bien, vous nous avez vus en action.";
			link.l1 = "Nous pillions et combattions ensemble, Leprechaun. Nous couvrions mutuellement nos arrières, risquant nos vies pour sauver l'autre. Cela ne représente-t-il rien pour toi ?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Je vais être franc avec toi, Prince : je ne t'ai jamais aimé. Tu es un parvenu. Un jeune insolent, amateur de boissons et de filles perdues, qui a accompli quelques tâches rentables pour Tyrex et s'est cru grand pirate\nDe plus, tu es boucher de nature. Tu penses que Carthagène t'a donné plus de poids au sein de la Confrérie ? Ho-ho, oh diable non, seulement parmi les monstres comme toi.";
			link.l1 = "Oh c'est hilarant ! Ha-ha-ha dit par un véritable ange lui-même ! Vieux salaud !";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Je pense que nous avons tout mis au clair maintenant. Il est temps de mettre fin à cette comédie. Les diables t'attendent en enfer depuis bien trop longtemps.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Aimes-tu cela, hein ?";
				link.l1 = "Recule !";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Eh bien, qu'en penses-tu ?";
				link.l1 = "Ce n'est pas drôle, Lutin. Qu'est-ce que c'est que ce bordel ?! Je n'ai pas commandé un massacre ! Ne crois-tu pas que c'est trop ?! Terrax ne sera pas content !";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Pourquoi cet air coupable, alors ? Cela ne te plaît pas ? Laisse-moi te dire - les choses ne feront qu'empirer. Tu crois que le massacre d'aujourd'hui s'est produit juste parce que c'est ce genre de journée ? Hah, bien sûr. C'est la routine. Picard n'a même pas sourcillé. Pour eux, c'est juste une autre journée à faire ce qu'ils aiment.";
			link.l1 = "Et toi ? Tu ne fais que passer ?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Je ne suis pas un pirate. Et j'aurais préféré ne pas faire partie des événements d'aujourd'hui. Et... si la vue des corps de femmes sur le sol noirci de Merida te bouleverse tant, pourquoi as-tu agi ainsi avec les Indiens, Prince ?";
			link.l1 = "Que devais-je faire? Tout laisser tomber et ramper jusqu'à Marcus avec des excuses?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Je pensais que tu l'avais pleinement adopté, que tu commençais à penser et à agir comme les capitaines de Tirax. Mais non, ha ! Tu es trop tendre pour ce genre de travail. Tu ferais mieux de donner ta part à Marcus et de partir la queue entre les jambes. Ce n’est pas ta vocation.";
			link.l1 = "Ce n'est pas à toi de décider pour moi, Lutin. Et tu n'as certainement pas le droit de m'insulter. Je ne renoncerai pas à ma part pour qui que ce soit. Je la partagerai équitablement avec Terrax.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "D'accord. Mais il vaut mieux partir avant que tu ne t'évanouisses.";
			link.l1 = "Ce n'est pas drôle, bon sang.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "Alors, tu ne le connais pas bien. Pourtant, puisque les événements d'aujourd'hui ne te réjouissent pas, écoute ce que j'ai à te proposer.";
			link.l1 = "Que pourrais-tu offrir après cela?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "Tu ferais bien de faire un effort pour écouter, garçon.";
			link.l1 = "Hmm, je n'aime pas ton ton, Lucas, mais soit, vas-y.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Je peux me le permettre - j'ai vécu plus longtemps que toi, Prince. Donc j'ai un œil vif, pas seulement pour tirer. Tu veux savoir ce que j'ai remarqué ?";
			link.l1 = "Dis-le simplement !";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Tu es hors de ton élément. Oui, tu es bon. Tu fais des progrès. Mais seulement parce que tu es un capitaine fort, pas parce que c'est vraiment ta vocation. Je ne sais pas comment tu t'es tourné vers Terrax, ou pourquoi, mais crois-moi, ce n'est pas ton truc.";
			link.l1 = "J'ai... un but. Je ne peux pas te dire ce que c'est.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "Et t'en es-tu rapproché ?";
			link.l1 = "Pas encore.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Eh bien, si même aujourd'hui ne t'a pas rapproché, il n'y a plus rien à gagner ici. T'es un bon gars, Prince. Tu as traité les Indiens comme des humains. C'est ironique que tu te retrouves ici avec nous. Mon conseil : donne ta part à Terrax pour éviter des problèmes, et tiens-toi à l'écart de tout ça - sauve ton âme tant que tu le peux.";
			link.l1 = "Je vais y réfléchir.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa te salue, fils de la mer. Veux-tu que je te montre le chemin vers la colonie espagnole aux montagnes ?";
			link.l1 = "Correct. Je vois que vous maniez bien notre langue contrairement au reste de votre peuple.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa avait souvent des affaires avec les yalanaui... La plupart de notre chemin se fera par rivière. Vous aurez besoin de longues embarcations. Les avez-vous ?";
			link.l1 = "Vraiment ? Nous pourrions les emprunter un petit moment...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Notre village est petit, nous avons très peu de chaloupes et toutes ne servent qu'à la pêche. Maintenant, nous avons besoin de bonnes chaloupes, celles qui résisteront à un long voyage, comme celles de vos navires.";
			link.l1 = "Hmm... Nous aurons alors besoin de six chaloupes. Le navire n'en a pas autant.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Construisez-les alors. Vous, les Blancs, pouvez réparer vos vaisseaux géants à terre, sûrement vous pouvez faire quelques chaloupes.";
			link.l1 = "Heh, il semble que tu as raison, Tagofa. Emmène-nous à la rivière, j'espère qu'elle n'est pas loin d'ici ?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Ce n'est pas le cas. Suis-moi.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Voici la rivière dont je vous ai parlé. Nous commencerons notre voyage d'ici. Vous construisez les bateaux et ensuite nous commencerons.";
			link.l1 = "Compris, Tagofa. Je te dirai quand ce sera fait.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Les bateaux sont-ils prêts, chef blanc ?";
			link.l1 = "Oui. Mes hommes sont sur le point de les attaquer.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Très bien. Montez sur le premier avec moi. Tagofa montrera le chemin.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "La partie de la rivière est faite. Nous ne sommes pas loin de l'établissement espagnol d'ici. Voici le sentier, restons dessus et nous ne nous perdrons pas. Nous avons réussi à contourner une forêt remplie de chasseurs Capong, mais c'est aussi leur territoire ici. Nous devons être prudents.";
			link.l1 = "Ne t'inquiète pas. Nous les éliminerons dès qu'ils nous montreront leurs vilains visages peints.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "Hé ! Tagofa ! Regarde ! Qu'est-ce que c'est... au milieu du chemin ? Un truc indien.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "C'est un signe des Capongs. Un avertissement. Il te dit d'arrêter et de ne pas aller plus loin. Les Capongs nous ont déjà repérés.";
			link.l1 = "Et si nous allons plus loin ? Nous attaqueront-ils ?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Oui, chef blanc. Vous devez leur sembler menaçant, puisqu'ils ne nous ont pas encore attaqués. Et pourtant, ils ont mis un signe pour vous.";
			link.l1 = "Que le signe aille se faire foutre. Nous avançons... Que tout le monde écoute ! Aux armes ! Préparez-vous ! Soyez en alerte ! Si ces sauvages nous montrent leurs sales trognes, nous les tuerons tous !";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Le chef blanc et ses hommes ont écrasé les capongas, Tagofa est impressionné. La ville espagnole est proche. Il y a une vallée où vous verrez une cascade. Tagofa n'ira pas chez les Espagnols. Je vous attendrai près de la cascade.";
			link.l1 = "Très bien. En avant !";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Nous sommes revenus, chef blanc. Tagofa a fait ce qu'il avait promis.";
			link.l1 = "Gratitude, Tagofa. Tu as bien fait.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa doit partir. Hayami m'attend avec impatience. Adieu fils de la mer.";
			link.l1 = "Bonne chance fils de la selva. Transmets mes salutations à ta femme. Et merci de nous avoir aidés.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Hé ! Qui es-tu et que veux-tu ?";
			link.l1 = "Nous devons nous rendre à Merida et avoir une conversation avec votre gouverneur ou avec quiconque vous avez à sa place...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "On ne laisse pas les étrangers entrer à Merida. Va-t'en !";
			link.l1 = "Compagnon, nous avons ramé dur pendant deux jours et ensuite combattu des hordes d'Indiens pour ne pas partir comme ça. Je répète, je veux parler au chef de votre village ! Nous avons une... proposition commerciale pour lui, oui ! Et si nous sommes tous d'accord, votre village restera intact.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Fais-tu des menaces, voleur ?";
			link.l1 = "Comment as-tu deviné cela? Ah oui, en effet, je fais des menaces. Soit nous obtenons ce pourquoi nous sommes ici pacifiquement, soit par la force, et tu as l'honneur de décider du sort de ton village.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Tu ne mettras jamais les pieds à Merida, sale pirate ! Alerte ! Ennemi aux portes !";
			link.l1 = "Un gentilhomme si déraisonnable...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Fichus larrons ! Que voulez-vous de nous ?! C'est une petite, modeste colonie. Nous n'avons ni or ni argent ! Comment avez-vous même entendu parler de nous ?";
			link.l1 = "Oh, ne faites pas l'innocent et l'ignorant, Votre Excellence. Le monde entier est déjà rempli de rumeurs à propos de vos opales.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "Et vous avez causé ce massacre impie à cause de... rumeurs ?! Vous n'avez épargné personne ! Des bêtes... Sachez-le : les gisements sont loin d'ici. Il n'y a rien à gagner ici pour vous. Partez.";
			link.l1 = "Tu as commencé ce massacre impie. Les civils ont combattu aux côtés de tes soldats. Je ne croirai jamais qu'un héroïsme aussi insensé soit possible juste pour protéger quelques murs nus.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Sais-tu combien d'efforts ont été nécessaires pour construire ces murs ? Nous n'avons pas engagé de bâtisseurs extérieurs - nous les avons construits nous-mêmes, brique par brique. Chaque résident. Même moi, de mes propres mains.";
			link.l1 = "Quelle histoire émouvante... Et qu'en est-il des meubles ? Vous les avez fabriqués vous-mêmes aussi ? Quelle belle chaise sculptée. Et table. Et armoires. Est-ce du chêne teinté ? Ou de l'ébène ? Un peu trop luxueux pour un 'modeste établissement,' n'est-ce pas ?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "L'avidité a obscurci ton esprit, ladrón.";
			link.l1 = "Pas besoin de compliquer les choses, Señor Gouverneur. Ou vous le regretterez.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Vas-tu me torturer, maudit pirate ? Tant pis pour toi - je crois en Dieu Tout-Puissant. Et je m'élèverai en martyr si tu en fais trop.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Mon ami, il ne va pas parler de cette manière. Laisse-moi m'en occuper.";
			link.l1 = "Oh?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Je me souviens de tout ce que ces Espagnols arrogants m'ont fait sur cette maudite plantation. Je serais heureux de te montrer, Prince. Et je te raconterai quelques histoires pendant que j'y suis. Tu ne t'ennuieras pas.";
			link.l1 = "Et si tu te laisses emporter?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "Il ne parlera pas gentiment. Je connais son genre.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Digne de confiance) (Honneur) (Leadership) Ça suffit de sang pour aujourd'hui, Jean. Je vais m'en occuper moi-même.";
				link.l1.go = "merida_head_dobro_1";
				notification("Trustworthy", "Trustworthy");
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(50))+")", "None");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Fais-le. Je ne m'en mêle pas. Et je ne regarde pas non plus.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Si je ne te devais rien, j'aurais quelques mots bien sentis pour toi... Bon sang. Va, maintenant il est temps de passer aux choses sérieuses.";
			link.l1 = "Ne te surmène pas.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Comme tu veux, mon ami. Ce sera amusant à regarder.";
			link.l1 = "Ne ricane pas trop tôt.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Tu dis que tu vas t'occuper de ça toi-même, sans effusion de sang, espèce de maudit voleur ? Il n'y a rien que tu puisses dire pour faire apparaître des pierres de nulle part !";
			link.l1 = "qu'ils apparaissent, Gouverneur. Sinon, nous raserons la ville et tuerons tout le monde sauf vous. Je n'aime pas cette solution, mais je suis prêt à compromettre mon honneur pour ma cause. Votre devoir, en revanche, est de protéger les civils, les soldats survivants, et les ouvriers de Merida. Ou préférez-vous 'ascensionner en martyr' au prix de leur souffrance ? Cela ne me semble pas très divin.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Que le diable t'emporte...\nLà-bas... dans le coffre. Épargne juste les gens du village !";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Se faufiler) Est-ce que tout est dans le coffre?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Je tiens parole. Adieu, Gouverneur.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Maudit soit-tu en enfer !\nLe coffre a aussi un faux fond. Prends tout !!";
			link.l1 = "... ";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Doux, Prince. Désolé de vous avoir sous-estimé.";
			link.l1 = "Satisfait?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Doux, Prince.";
			link.l1 = "Satisfait ?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Tu avais promis de quitter la ville une fois que tu aurais les gemmes... Tu les as maintenant et tes voleurs ont mis le feu à nos maisons ! Tu es un menteur et un infâme pirate ! J'espère que les flammes de l'enfer seront aussi brûlantes pour toi !!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", bon monsieur. Quel est votre but ici ?";
			link.l1 = "Je viens de Tyrex. On m'a dit d'escorter votre navire jusqu'à Bridgetown. Êtes-vous prêt ?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Eh bien, enfin ! Oui, mon équipage est prêt à appareiller immédiatement !";
			link.l1 = "Splendide. Préparez les voiles, capitaine. Mettons-nous en route !";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Merci de m'avoir aidé, capitaine ! Avec vous à mes côtés, j'étais aussi en sécurité que si j'étais derrière les murs du fort.";
			link.l1 = "Hah, n'en parle pas, l'ami ! Tout est sur Marcus. Bonne chance à toi, camarade !";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Salutations au vaillant capitaine ! Permettez-moi de me présenter - corsaire d'Angleterre, Ignacio Marco du Torero.";
			link.l1 = TimeGreeting()+", ami. Capitaine "+GetFullName(pchar)+"à votre service. Comment puis-je vous aider ?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Oh, je vous connais ! Monsieur "+GetFullName(pchar)+" ! Des rumeurs sur vos ressources et mécènes m'étaient parvenues dans tout l'archipel. Je crois que mon offre sera fort intéressante pour vous.";
			link.l1 = "Quelle offre ?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Allons à une taverne pour boire un coup. Je te raconterai tout. Ce n'est pas une conversation de rue.";
			link.l1 = "Très bien... Allons-y !";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Une tournée, capitaine ?";
			link.l1 = "Bien sûr !";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Hé, ils ne mélangent pas vraiment le rhum avec de l'eau ici...";
			link.l1 = "Et ne pas traiter les clients avec du poisson pourri, oui-oui. Alors, quel est le marché ?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "J'aime votre franchise, monsieur. Dites-moi, êtes-vous au courant de la guerre commerciale entre les Anglais et les Néerlandais ?";
			link.l1 = "Je le suis. J'ai eu le plaisir d'y participer.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Pas besoin de l'expliquer alors. En tant que corsaire anglais, je combats cette guerre de leur côté. Vous êtes un mercenaire pour l'essentiel. Ce qui vous rend indifférent à quel côté combattre...";
			link.l1 = "Presque. Je ne traverse pas la France, je suis désolé.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Par tous les moyens, capitaine ! Alors, allons droit au but : il y a une petite île habitée entre Curaçao et Trinidad, elle n'est pas sur les cartes... Depuis peu, je dirais très récemment, les Hollandais ont commencé à l'utiliser comme escale temporaire pour se réapprovisionner et réparer. Il semble qu'ils croient être les seuls à connaître cette île. Faux. He-he\nIl y a quelques jours, une caravane d'argent a été frappée par une... tempête, et maintenant les Hollandais réparent leurs vaisseaux sur cette île. Le navire amiral a perdu son mât, donc cela prendra un certain temps pour le réparer. Les Hollandais sont occupés à réparer, et les équipages sont principalement dispersés sur l'île...";
			link.l1 = "Et puis soudain, nous arrivons pour sauver la mise ?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Exactement, capitaine. Je ne peux pas faire ça seul mais avec vous - c'est une toute autre histoire. Tenterez-vous le coup ? J'ai un navire formidable, l'équipage est excellent et j'ai une bonne dose d'expérience. Vos compétences... sont également louables.";
			link.l1 = "Combien de temps avons-nous ?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Beaucoup, si nous ne le gaspillons pas et partons immédiatement.";
			link.l1 = "Alors ravitaillons-nous en munitions et armes, capitaine Ignacio Marco, et levons l'ancre. Quelles sont les coordonnées exactes de l'île ?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 Nord, 64'11 Ouest. Compris?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha ! Deja vu... Compris.";
			else link.l1 = "Compris.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Je me dirige vers le 'Torero'. Je vous attendrai, capitaine !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Quel sacré combat, n'est-ce pas, capitaine ? Maintenant, la partie agréable : partageons notre butin. La moitié pour moi et mes hommes.";
			link.l1 = "Très bien, faisons-le...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Capitaine, qu'est-ce que c'est ? Où est notre argent ? As-tu coulé notre prise ?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Quelque part, l'argent a été gaspillé bien que nous ayons obtenu du bois de séquoia. Partageons-le.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm.. C'est médiocre. Je pensais qu'il y en aurait beaucoup plus.";
				link.l1 = "On a ce qu'on a.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Pas mal, pas mal. Quoique, je pensais qu'il y en aurait plus.";
				link.l1 = "On a ce qu'on a.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Bien joué, Monsieur. Voilà un joli butin...";
			link.l1 = "Je ne peux pas te contredire là-dessus, capitaine.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "On dirait que tu as un sérieux problème dans la caboche. Nous partons ! Les gars !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "Au moins, nous retirons quelque chose de cette affaire... Garçons ! Allons-y !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "C'est quelque chose. Séparons nos chemins.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "C'est quelque chose. Séparons-nous. C'est un succès après tout, hé hé !";
			link.l1 = "...  ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Nous avons eu une réunion très profitable. Peut-être que ce n'est pas la dernière fois que nous faisons affaire ensemble, capitaine !";
			link.l1 = "Appelle-moi si tu trouves d'autres gros marchands, hé-hé !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Je suppose que ce n'est pas un accident, capitaine ?";
			link.l1 = "Tu ne serais pas malin si tu ne le voyais pas. Tu me dois pour l'arnaque. Tu sais de quoi je parle. De plus, tu me dois pour avoir piégé mon ami Jean Picard. Il a été vendu à la plantation après ton complot... Tu as perdu Ignacio. Je vais te pendre, mais tu peux alléger ta punition...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Je me demande même - que puis-je faire pour que tu me prennes en pitié ?";
			link.l1 = "J'ai besoin d'informations. Je vais te mettre dans ma cale où nous parlerons de ton programme à La Havane...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Je ne l'avais pas vu venir ! N'y pense même pas. Barbazon saura ma trahison en un rien de temps. Tu ferais mieux de ne pas savoir ce qu'il fait aux gens qui l'ont trahi. Je l'ai vu.";
			link.l1 = "Alors, être pendu est une meilleure option ?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Je préfère mourir au combat !";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Capitaine ! Capitaine ! Vite ! L'escadre militaire espagnole est à nos trousses !";
			link.l1 = RandSwear()+"Je m'y attendais... La même histoire est arrivée à Picard. As-tu vu combien d'entre eux étaient là dehors ?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Oui, capitaine. Trois navires. Leur vaisseau amiral est un galion, le plus grand que j'aie jamais vu et il avance vite, les deux autres sont une corvette et un chebec.";
			link.l1 = "Tous à bord. Nous pourrions encore être en position de fuir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya ! Maudit yalanaui vient dans notre forêt ! Tuez-le ! Haya !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Hé ! Que diable fais-tu ici ? A-ah, voler les biens des autres ? Eh bien, tu es foutu !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Hé ! Tout le monde, arrêtez-vous là ! Ou je vous emporte tous avec une volée de mitraille !"+RandSwear()+"";
			link.l1 = "Nous ne bougeons pas d'ici pour le moment. Mais écoute, l'ami - il n'y a aucune chance que tu nous tues tous d'un seul coup. Certains d'entre nous te mettront en pièces pendant que tu recharges. On ferait mieux de discuter tout de suite.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Est-ce vous qui commandez ici ? Répondez-moi !";
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+"Et tu dois être le second de Red Wolf quand il est absent d'ici, ai-je raison ?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Que fais-tu ici, capitaine "+GetFullName(pchar)+" ? Nous n'invitons pas d'étrangers en ces lieux !";
			link.l1 = "Quel est ton nom ? Je veux savoir à qui je parle.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Je m'appelle Rodgar Janssen.";
			link.l1 = "Je vois bien que vous êtes dans le brouillard, les gars. Vous n'avez plus de capitaine. Et votre corvette est partie aussi. La 'Freyja' a été bombardée jusqu'à l'enfer par les Espagnols non loin d'Hispaniola. Son équipage a été massacré jusqu'au dernier...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Aahhh-ghhhhh!!! ... Mais comment puis-je savoir que vous dites la vérité?";
			link.l1 = "J'ai le journal de bord de votre ancien capitaine ! Nous avons récupéré quelques objets de l'épave de Freyja. Grâce au journal, j'ai trouvé cette île et ces... trésors à vous.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh ! Tu me dois toujours une réponse : pourquoi es-tu ici sur cette terre inconnue ?";
			link.l1 = "Je ne vais pas te mentir, mon pote. On dit que le Loup Rouge possédait une sacrée fortune. Je suis ici pour la trouver, car aucun tel trésor n'a été découvert sur son navire. Je crois qu'ils devraient appartenir aux braves gens, ils ne servent plus à rien à Wulfric de toute façon.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha ! Matelot, je vais te décevoir : ni moi ni aucun autre membre de l'équipage n'avons jamais vu les trésors de Wolf. C'était trop risqué de lui demander.";
			link.l1 = "Alors je devrais probablement les chercher dans ton village. Vas-tu poser ton arme ou devrais-je commencer à prendre d'assaut le village ? Tu n'as aucune chance Rodgar. J'apporterai des armes et plus d'hommes si besoin.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Avant de mourir, nous vous emmènerons en enfer avec nous, un bon paquet de salauds! Peut-être toi aussi!";
			link.l1 = "Es-tu sûr ? Tu n'as ni capitaine, ni navire et personne ne viendra te sauver. Même si je pars, vous mourrez tous de faim bientôt !";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... as-tu des suggestions ?";
			link.l1 = "Oui, je le fais. Reculez d'un pas du canon et gardez vos hommes sous contrôle. Je jure de ne vous faire aucun mal, ni à vous ni à vos hommes. Si vous voulez, vous pouvez rejoindre mon équipage ou nous vous emmènerons vers une civilisation.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Jure-le devant tes hommes, fort et clair !";
			link.l1 = "Je le jure ! Tu as ma parole : toi et tes hommes ne serez pas blessés.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "J'espère que vous tiendrez parole, capitaine.";
			link.l1 = "Je le fais toujours. Combien d'entre vous reste-t-il?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Tu nous vois tous. Trois. Les autres sont morts dans la jungle en t'attaquant. Je leur ai dit de ne pas le faire mais ils n'ont pas écouté...";
			link.l1 = "Je vois...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "La nourriture venait à manquer. Nous avons commencé à chasser les perroquets. Le 'Freyja' était absent depuis trop longtemps. Nous avions nos soupçons et ils se sont révélés vrais.";
			link.l1 = "Dieu merci que j'ai décidé de partir à la chasse au trésor. Où penses-tu qu'il les a cachés ?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Je te l'ai déjà dit : personne ne les a jamais vus. Wulfric était prudent avec sa part, il ne la laissait jamais se perdre. Il était juste avec nous, mais tous ceux qui ont essayé de trouver sa cachette ont disparu. Tu es libre de fouiller le village si tu le souhaites.";
			link.l1 = "C'est mon plan. Où se trouve la maison de Loup Rouge ?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "Le seul bâtiment à deux étages que nous ayons ici.";
			link.l1 = "Bien. Au fait, quel est ton métier ?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "Je suis charpentier et ces deux-là sont mes assistants. Nous avions l'habitude de réparer et de truquer le 'Freyja' auparavant. Nous pourrions être utiles dans votre équipage.";
			link.l1 = "Je vois. Très bien, tu es des nôtres, nous parlerons des détails plus tard. Prends ce pistolet à l'entrée. Et Rodgar, ne quitte pas le village pendant que je cherche la cachette.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Ordres, capitaine ?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Oui. Les trésors de votre capitaine ont été trouvés. Il les avait bien cachés, mais je l'ai déjoué !";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, que penses-tu, y a-t-il autre chose que nous puissions faire avec cette base ?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, j'ai apporté les outils. Ils auraient déjà dû être livrés à vous.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Bienvenue ! Voici Rodrigo Jimenez, le chef d'une petite mais très travailleuse communauté de Cadix. Senor Jimenez a gentiment accepté de s'installer temporairement sur nos terres et de nous aider avec la construction.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, comment ça va ? As-tu de bons conseils pour moi ?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, j'ai besoin d'un service.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >=600)
			{
				link.l1 = "Je t'ai apporté les doublons, mais ne les gaspille pas tous en alcool tout de suite.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, vérifie l'entrepôt. J'ai apporté les médicaments et les provisions.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Bonjour, Rodgar, comment vont les choses dans la nouvelle colonie ?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, mon navire a besoin de réparations. Toi et tes gars êtes prêts?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, je voudrais laisser un de mes navires ici.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, je voudrais reprendre un de mes navires.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Écoute, y a-t-il un bâtiment vide que je pourrais utiliser comme entrepôt ?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, je veux voir un entrepôt.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, je veux laisser une partie de l'équipage sur l'île.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, je veux emmener mes marins avec moi de retour en mer.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Rien encore...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Félicitations capitaine. Que faisons-nous ensuite? Partons-nous?";
			link.l1 = "Es-tu ici depuis longtemps?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Depuis beaucoup trop longtemps. Cela fait un an que Wulfric m'a mis aux commandes ici.";
			link.l1 = "J'ai décidé que cette base secrète est trop bonne pour être gaspillée. Le village est à moi maintenant. Je peux te laisser, toi et tes hommes ici si tu veux. Rhum, provisions, médicaments - tout est à vous.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Ce serait formidable, capitaine. Je me suis habitué à la vie sur cette plage, cette île.";
			link.l1 = "Splendide. Au fait, comment s'appelle l'île ?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Peut-être qu'un jour nous construirons plus de maisons et de structures ici... Mais plus tard. Pour l'instant, vous garderez le même rôle ici mais sous un nouveau capitaine.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Marché conclu. Prends soin de toi, capitaine, et n'oublie pas de nous fournir en provisions.";
			link.l1 = "Bien sûr, Rodgar. Bonne chance, je devrais naviguer vers La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "Il est difficile de dire, Capitaine. Feu Wulfric n'a jamais laissé plus de deux douzaines de personnes ici. En ce moment, nous ne sommes que trois,"+sTemp+"Il n'y a pas grand-chose que nous puissions faire.";
			link.l1 = "Voulez-vous dire que si plus de gens vivaient ici, vous pourriez transformer cet endroit en une colonie à part entière ?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "L'île est petite, donc vous ne pouvez pas y construire une colonie, mais un établissement est tout à fait possible ! Vous pouvez pêcher, chasser les oiseaux et les chèvres, cueillir des fruits. Nous pouvons nous sustenter, mais nous n'en tirerons pas richesse.\nMais il y a une chose que je ne comprends pas bien, Capitaine. Pourquoi avez-vous besoin de cela ?";
			link.l1 = "C'est ma maison et ma terre, mon peuple. Que suis-je si je ne m'en occupe pas?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Je veux investir de l'argent dans une affaire qui en vaut la peine.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Cette petite île se trouve en plein cœur de cette région. Il serait sage de la transformer en une base militaire secrète et à part entière.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Je m'inquiète pour toi, Rodgar, vous êtes tous devenus complètement fous à ce stade.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Tu es un drôle de loustic. Eh bien, peu importe. Au moins, il y aura de quoi s'occuper...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Tu es un drôle d'oiseau. Enfin, peu importe. Au moins, il y aura quelque chose à faire...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Tu es un drôle d'oiseau. Bon, peu importe. Au moins, il y aura quelque chose à faire...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Tu es un drôle de loustic. Bon, peu importe. Au moins, il y aura de quoi faire...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Tout d'abord, tu devras trouver des individus très spéciaux. Ceux qui pourraient être persuadés de déménager dans cette contrée sauvage pour y vivre et y travailler pendant des années, dans une isolation complète du monde extérieur. C'est le genre de personnes spéciales que tu devras rechercher. Espérons-le, pas qu'une seule. Après tout, tu ne peux pas encore ordonner à ton équipage de vivre ici. Les colons ne voudraient pas quitter leurs foyers établis et leurs emplois stables. Et nous n'avons pas besoin de vagabonds et d'autres inadaptés ici.\nDe plus, la question du secret entourant cette île sera toujours présente. Si tu le dis à quelqu'un, il y aura immédiatement la menace de chasseurs cherchant à enquêter.";
			link.l1 = "Je comprends, des suggestions ?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "Non, Capitaine. Je suis ici depuis bien trop longtemps et j'ai complètement perdu le contact avec la vie civilisée.";
			link.l1 = "Super, c'est utile !";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Je travaille avec le bois, pas avec les gens. Et j'en suis très heureux, ha-ha ! Au fait, en plus des gens, vous devrez aussi apporter ici un ensemble d'outils de forge et de construction de haute qualité. Ils ne sont fabriqués qu'en vieille Europe, alors cela vous coûtera une jolie somme. Demandez aux propriétaires des chantiers navals, les plus grands.";
			link.l1 = "Tout est clair. Résumons : si je veux transformer cette base en quelque chose de plus grand, je dois ramener ici plus de colons et d'outils ?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "C'est exact !";
			link.l1 = "Je verrai ce que je peux faire.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Oui, Capitaine ! Ensemble de première classe, nous sommes prêts à fonder une colonie ! Cela a-t-il coûté cher ?";
			link.l1 = "Ça m'a coûté une fortune, j'espère bien que ça en valait la peine !";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Il y a quelques années, j'aurais dit que c'était très cher. Mais maintenant... Je ne sais même pas.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Tu ne pouvais pas te contenter de ce que tu avais déjà, n'est-ce pas ? Quoi qu'il en soit, prépare-toi à voir tes dépenses augmenter. As-tu réglé le problème avec les colons ?";
			link.l1 = "Non, Rodgar. Je n'ai pas encore découvert où les trouver. Après tout, je n'ai pas les droits souverains pour établir des colonies dans ces eaux.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Tu ne pouvais pas te contenter de ce que tu avais déjà, n'est-ce pas ? Quoi qu'il en soit, prépare-toi à ce que tes dépenses ne fassent qu'augmenter. As-tu réglé le problème avec les colons ?";
			link.l1 = "Non, Rodgar. Je n'ai pas encore découvert où les trouver. Après tout, je n'ai pas les droits souverains pour établir des colonies dans ces eaux.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "Dans ces eaux, Capitaine, le chaos règne chaque jour. Écoutez ce que disent les gens, vous pourriez bien voir une opportunité cachée. Je m'occuperai des outils pour l'instant.";
			link.l1 = "D'accord, je serai à l'affût de ce genre d'informations.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Espagnols ? Vous plaisantez, Capitaine. Je pensais que vous ramèneriez des fainéants de Le Francois, pas ceux-là...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Es-tu d'Europe ? Hehe, ce n'est pas difficile à deviner. Ne t'inquiète pas, tu t'y habitueras.";
			link.l1 = "Jimenez, tu resteras chez moi un moment. Il y a un sous-sol là-bas, beaucoup d'espace. Rodgar, j'ai apporté les outils, et les colons aussi. Quelle est la suite ?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "À demain, Capitaine. Nous parlerons dans un jour, une fois que ces... colons se seront installés avec leurs trésors...";
			link.l1 = "D'accord, nous continuerons demain.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Capitaine, parle au Espagnol. Il est déjà pleinement engagé dans son travail.";
			link.l1 = "Compris, je m'en occupe.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Y a-t-il un problème ?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Capitaine, je traîne avec les gars ici depuis quelques années. Maintenant, l'agitation des Espagnols me tape sur les nerfs.";
			link.l1 = "Pas de conflits ! Et j'interdis à toi et à tes gars de même regarder dans la direction de leurs femmes ! Du moins, pour l'instant... Si les choses s'enveniment, prends un esquif et va... pêcher pendant quelques jours.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Oui, oui, monsieur !";
			link.l1 = "Parfait. Très bien, je vais voir ce qu'il mijote.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Je sais déjà, Capitaine. L'Espagnol veut que nous explorions l'île ? Sauter sur les rochers avec une carte comme une bande d'idiots ?";
			link.l1 = "C'est exact, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Six cents doublons et je le ferai.";
			link.l1 = "Es-tu fou? As-tu été mordu par une araignée locale ou un serpent venimeux? Que vas-tu faire d'un coffre d'or sur une île inhabitée? L'enterrer?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Allez, Capitaine. Un jour, nous quitterons cet endroit, et qui aura besoin de nous dans le grand monde sans une pièce? Bien sûr, nous avons une petite réserve cachée, mais ce n'est pas suffisant. Wulfric n'a jamais réglé ses dettes avec moi et les gars pour ses dernières aventures.\nC'est une chose de paresser sur la plage pendant des mois et d'entretenir votre flotte une fois tous les six mois. Mais travailler dur sur la terre ferme chaque jour, comme un maudit boucanier - c'est une toute autre histoire! C'est un boulot, et les boulots paient. Vous payez votre équipage, n'est-ce pas, Capitaine?";
			link.l1 = "Ça me paraît raisonnable. Je te donnerai les 600 doublons. J'espère que tu n'attends pas le paiement d'avance, n'est-ce pas ?";
			link.l1.go = "IslaMona_23";
			link.l2 = "J'ai une autre proposition. Tu travailles à terre, pas à gratter les bernacles des navires en mer. En ce moment, nous avons cruellement besoin de ce genre de travail.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Capitaine, je suis prêt à commencer dès maintenant, mais mes hommes travailleront beaucoup plus dur lorsqu'ils verront des doublons dans leurs mains. Je promets que nous ne laisserons pas un seul bout de terre inexploré sur cette île.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "D'accord. Voici ton or. Ne le gaspille pas tout de suite en boissons.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "D'accord, je vous apporterai vos doublons.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha ! Vous avez raison là, Capitaine ! Oh, et j'ai presque oublié. Il y a maintenant pas mal de gens qui vivent ici, et ils ont besoin de quelque chose à manger. Avez-vous vu ces dames ? Elles ne sont pas habituées à survivre et à se nourrir de la terre. Elles ne seront d'aucune aide.";
			link.l1 = "Ne me dis pas que je devrai trouver plus de boucaniers pour t'aider.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Oui-oui, Capitaine ! Nous sommes prêts à travailler sur la terre ! Oh, et encore une chose, j'ai presque oublié. Il y a maintenant pas mal de monde qui vit ici, et ils ont besoin de quelque chose à manger. As-tu vu ces dames ? Elles ne sont pas habituées à la survie et à se nourrir de la terre. Elles ne seront d'aucune aide.";
			link.l1 = "Ne me dis pas que je vais devoir chercher des boucaniers pour vous aider aussi.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "Non, pourquoi le ferions-nous ? Nous formerons et préparerons les plus capables d'entre eux pour leur subsistance. Mais jusqu'à ce moment merveilleux, vous devrez nous fournir de la nourriture. Quelques milliers de rations de provisions de bord suffiront. Et un quintal de médicaments pour l'avenir. Déchargez tout cela des navires dans notre entrepôt sur l'île.";
			link.l1 = "Je le ferai. Combien de temps as-tu besoin pour la mission de reconnaissance ?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "Nous aurons terminé dans deux à trois jours, nous avons déjà trouvé des choses intéressantes.";
			link.l1 = "Génial !";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "Dès que nous aurons terminé, dirige-toi directement vers ce rieur espagnol. Le fou doit tirer des conclusions de notre travail.";
			link.l1 = "Je vois que vous êtes déjà presque amis. Je lui rendrai visite dans trois jours alors. Eh bien, à la besogne. Bonne chance à nous tous !";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Wow ! Merci, Capitaine. Maintenant, nous avons le temps de préparer les dames pour cette vie folle dans la nature.";
			link.l1 = "Fais attention à ne pas en faire des pirates ! Merci, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Capitaine ! Je dois dire que j'ai commencé à me sentir plutôt mal à l'aise de vivre ici.";
			link.l1 = "Pourquoi cela, Rodgar ? La nostalgie du charme de la pauvreté et de la ruine ?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "On peut dire ça. Maintenant, la civilisation atteint même ici. Et les gens comme moi n'y ont pas leur place.";
			link.l1 = "Achète-toi une cravate et une canne. Tu te fondras parfaitement.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Plutôt, allons voir ton Espagnol et discuter des résultats de la reconnaissance. J'ai encore une idée folle...";
			link.l1 = "Je viens de lui parler ! Très bien, allons-y, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Comment trouves-tu de travailler avec lui ?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Des gens très instruits et travailleurs ! Et Jimenez est vraiment un maître. Autrefois, on aurait pu obtenir une belle somme d'or pour de telles personnes. Et leurs filles sont belles aussi...";
			link.l1 = "Je n'en veux rien entendre, Rodgar ! Allons parler à ce maître à nous.";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Si ils ne peuvent pas faire le boulot, on les vendra. Mais garde les filles, ha-ha ! Allons voir le maître...";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Sérieusement, Capitaine ? Je plaisantais seulement, allons-y...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Je savais que vous me soutiendriez, Capitaine ! Allons-y...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Il ne rit pas, cap...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "Ca aussi, capitaine. Nous en discuterons plus tard...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "Le gentilhomme a raison, Capitaine. Aucun de nous n'ira se casser le dos dans la jungle. Les affaires peuvent être sales, mais vous ne tirerez rien de plus de cet endroit qu'un repaire de pirates d'une autre manière.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "Et mes gars auront besoin de la même quantité d'or et d'une autre douzaine de bouteilles de bon rhum.";
			link.l1 = "Combien de bois pourras-tu fournir à chaque livraison ? Et pourquoi as-tu besoin d'or ?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Eh bien, tout d'abord, la vie sans loisirs est dénuée de sens, et bientôt même les pieux, hehe, catholiques commenceront à grimper aux murs. Et deuxièmement, s'il y a une taverne sur l'île, vous pourrez laisser une partie de l'équipage ici en attente. Vous voyez, convaincre les gens de vivre comme des sauvages gratuitement dans des huttes sur la plage pendant toute une année est assez difficile. Mais s'il y a un établissement avec une taverne, de la nourriture chaude, de la musique et des divertissements à proximité... De quoi d'autre un marin a-t-il besoin pendant une permission à terre ?";
			link.l1 = "Putains ?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Boissons?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Tu as raison, mais résolvons les problèmes un par un. D'abord, nous reconstruirons ta maison...";
			link.l1 = "... ";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "Il n'y a même pas pensé, capitaine.";
			link.l1 = "Merci, Rodgar. Je comprends qu'à présent je pourrai m'occuper de plus de navires dans cette petite baie, n'est-ce pas ?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Salutations, Capitaine ! Êtes-vous venu discuter du travail ?";
			link.l1 = "Non, pas du tout. Votre physionomie nordique me manquait juste.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Allons-nous marcher ? Je vais vous montrer votre usine.";
			link.l1 = "Mène le chemin.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hic ! Cap, nous célébrons !";
			link.l1 = "Rodgar ! Rodrigo ! Eh merde !";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "Qu'y a-t-il, c-c-capitaine ? Vous n'aimez pas la couleur des murs ?";
			link.l1 = "Je viens juste de réaliser que vous deux partagez le même nom ! Ha-ha-ha ! Un Espagnol et un pirate, avec le même nom, ont construit une taverne sur une île déserte et boivent ensemble comme si les dieux indiens allaient dévorer tout le monde et mettre fin au monde au lever du soleil ! Ha-ha ! Je suis avec vous !";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha ! Tellement vrai ! Santé !";
			link.l1 = "À la tienne !";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Tu veux un coup à boire, capitaine ?";
			link.l1 = "Deviens-tu aubergiste, Rodgar ?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Temporairement ! Les Espagnols apprécient particulièrement qu'un pirate s'occupe du bar - c'est le véritable exotisme et aventure pour eux. Mais dans l'ensemble, c'est agréable ici. Si tu décides de laisser un de tes hommes en réserve dans cette colonie, fais-le moi savoir - je m'en occuperai.";
			link.l1 = "Où vivront-ils cependant ?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Simple - nous construirons quelques cabanes sur la plage. De cette façon, ils courront de la taverne à la côte. Juste un rappel, cette île ne peut accueillir plus de trois cents personnes, alors gardez cela à l'esprit pour l'avenir. Parfois, nous vous demanderons d'apporter du rhum et du vin, donc ce serait génial si vous, Capitaine, pouviez stocker les marchandises dans l'entrepôt à l'avance.";
			link.l1 = "Je m'en souviendrai. Eh bien, compadre. Distrait les Espagnols et prends une pause. Juste, s'il te plaît, ne bois pas jusqu'à ce que tout le village brûle - je ne pourrais pas supporter la vue de ça !";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Capitaine ! Je suis sacrément heureux de vous voir ! Merci à Freyja, vous êtes arrivés juste à temps !";
			link.l1 = "Oui, nous nous sommes encore fourrés dans un beau pétrin. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Pas de pertes. Les Espagnols survivants nous ont rejoints les premiers, ont signalé qu'il pourrait y avoir d'autres invités, et nous avons réussi à apporter presque toutes les provisions et l'équipement de la zone à la colonie. La situation avec les esclaves ne s'est pas très bien passée, bien sûr.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "Et s'ils nous entraînent dans une attaque à découvert ?";
			link.l1 = "Alors, nous travaillons sans armes. Comme lors d'un défilé, nous marchons ensemble vers les portes et puis nous les frappons par derrière. Vous tenez les portes et fournissez le soutien. Voilà, bonne chance à nous !";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Hourra, Capitaine !";
			link.l1 = "D'accord ! C'était un tel coup, j'ai moi-même eu envie de m'allonger. Les gars, qu'avez-vous chargé là-dedans ?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Charge double, Capitaine. Ainsi, une seule décharge les découragera de se battre davantage !";
			link.l1 = "N'avais-tu pas peur que le canon explose avec une manipulation si délicate ?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "J'ai un talisman spécial laissé par Wulfric. Un souvenir de notre Danemark natal. Allons-nous tous à la taverne, Capitaine ? Nous sommes tous fatigués après aujourd'hui.";
			link.l1 = "Oui, ce serait formidable. Jouons aux cartes - nous parierons sur ton talisman miraculeux.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, après une telle performance divine aujourd'hui, Capitaine, je pourrais même envisager cette option !";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Capitaine, as-tu entendu cela ? J'ai encore des bourdonnements dans les oreilles. De qui est cette voix lugubre ?";
			link.l1 = "Ça, Rodgar, c'est un problème brûlant. Emmène-le à l'usine, mets-le à la chaîne, et attends d'autres instructions.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Oui-oui, capitaine !";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Capitaine, êtes-vous venu résoudre le problème avec le prisonnier ? J'en ai marre de rester ici à monter la garde.";
			link.l1 = "Nous devrons le tuer. Le risque est trop grand, donc nous n'avons pas le choix. Sinon, je ferais mieux de ne pas montrer mon visage dans les colonies françaises.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Je ne peux pas le laisser partir, sinon je ferais mieux de ne pas montrer mon visage dans les colonies françaises. Mettez-le aux fers et laissez-le travailler à l'usine. C'est mieux que de le tuer.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Compris ! Faisons-le rapidement. Allez-y, Capitaine. À demain.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Eh bien. Tu es vraiment un génie du mal. Je ne voudrais pas être ton ennemi. Eh bien, nous devrons d'abord faire un peu de travail explicatif avec lui. Allez-y, Capitaine. À demain.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Quel massacre ! Dommage que nous n'ayons pas pu tirer du canon, mais ils se sont précipités droit dans ton embuscade - c'était agréable à regarder !";
			link.l1 = "Oui, nous avons versé beaucoup de sang sur cette terre. Mais apparemment, il n'y a pas d'autre moyen de bâtir une maison dans ce monde.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Ne t'y attarde pas trop, Capitaine. Le destin lui-même les a amenés à Isla Mona. Et laisse-moi te dire, le destin peut être une sacrée garce !";
			link.l1 = "Le destin, ou l'île ?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Tous deux ont joué leur rôle.";
			link.l1 = "Haha ! Et les deux sont magnifiques ! Très bien, brave Viking. Ramasse les trophées et enlève ces corps. Enterre-les avec dignité. Ce sont les nôtres, après tout...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Oui, Capitaine. C'est exact ! Rodrigo l'a dit si magnifiquement que cela m'a tiré une larme. Il est clair pourquoi les saints pères veulent lui enfoncer le cul sur un pieu !";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, et ici je suis tombé nez à nez avec notre prélat dans le boudoir... Et laissez-moi vous dire, c'est le meilleur établissement de Santiago !";
			link.l1 = "Le meilleur endroit si vous aimez aussi les prélats.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Oui, j'ai vraiment transformé ce vaurien et hérétique Rodrigo en un vrai pirate.";
			link.l1 = "Au fait, éclaire-moi, Rodgar. Pourquoi y a-t-il si peu de pirates espagnols ?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Pourquoi si peu? Ah, tu veux dire les capitaines pirates? Eh bien, il y en a plein, ils opèrent juste principalement sous la Casa de Contratación à Séville. C'est comme le renseignement militaire, mais pour une raison quelconque, ils appellent ça une maison de commerce...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Oui, pourquoi ne pas leur envoyer un message et les inviter à venir. Eh bien, ils ont tous des lettres de marque, et ils sont idéalistes aussi. D'habitude, ils ne dépouillent pas les leurs, sauf si le raid a échoué, ha-ha ! Ils ne font que passer par Puerto Principe et se heurtent constamment à Pastor.\nRécemment, un s'est distingué... Diego de Montoya. Juste la dernière fois que je suis parti en campagne avec Wulfric, j'ai beaucoup entendu parler de ses aventures. Vous, capitaine, avez quelque chose en commun avec lui. Et en même temps, vous êtes très différent... Enfin, de quoi je parle ? Prenons un autre verre et jouons aux cartes.";
			link.l1 = "Tu n'as pas d'argent. Tu ne paries pas sur des doublons, n'est-ce pas ?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Nous parions un peso chacun. On joue jusqu'à vingt ? Hymenes, es-tu partant ?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Jouons, capitaine ?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Lance-le !";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Je passe aussi, Rodgar. Pesos ou pas, les gens perdent des navires comme ça. Avec des îles. Amuse-toi ici, et je vais encore jeter un coup d'œil.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Passe! Eh bien, eh bien, je ne joue plus avec toi ! Je suis sûr que tu as triché, Capitaine ! Et laisser partir un tricheur comme ça ne serait pas juste !";
				link.l1 = "Je t'écoute, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "J'ai gagné, cap. Mais je ne peux pas te laisser repartir les mains vides comme ça, haha !";
					link.l1 = "D'accord, vaurien. Ce sera une leçon pour moi...";
				}
				else
				{
					dialog.text = "J'ai gagné, cap'. Mais je ne peux pas te laisser partir les mains vides comme ça, haha !";
					link.l1 = "D'accord, vaurien. Ce sera une leçon pour moi...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ah, allons! Vous m'avez donné, à moi et à mon équipage, une chance d'une vraie vie loin des quartiers exigus, de l'eau croupie et du risque de prendre un éclat dans... le crâne. Tenez. Ce charme a été apporté par Wulfric du lointain Danemark et ensuite remis à moi pour que je... heh, n'aie pas à trop fouiller dans son sous-sol. Je n'en ai plus besoin, mais vous - oh, vous le trouverez fort utile.";
			link.l1 = "Merci, Rodgar. En effet, un objet utile. Et beau aussi...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Garde-le, Rodgar. Sans toi, cet endroit n'existerait pas. Que cela soit un rappel de ta patrie.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "Je suis ravi que vous ayez apprécié, Capitaine. Une autre tournée ?";
			link.l1 = "Détendez-vous ici, et je vais jeter un coup d'œil autour encore un peu.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Comme vous le souhaitez ! Alors j'en donnerai un à une dame chance, haha ! Un autre tour ?";
			link.l1 = "Vous autres, détendez-vous ici, et je vais encore jeter un coup d'œil aux alentours.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Eh bien, Capitaine. Vous avez réglé les affaires avec l'Espagnol, nous avons fêté ça, et le mal de tête s'est un peu estompé. La vie est belle !";
			link.l1 = "Que fais-tu, Rodgar ?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "Je chasserai comme d'habitude, surveillant ma... notre taverne, donnant des coups de pied aux esclaves à l'usine. Une retraite parfaite.";
			link.l1 = "Tu n'as que cinq ans de plus que moi, Rodgar. Et toi, Rodrigo ? Comment ça va ?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Par tous les moyens, capitaine ! Tout ce dont nous avons besoin, ce sont des planches et de la toile à voile. Rendez-vous à votre point de débarquement et ordonnez à l'équipage de préparer les matériaux.";
				link.l1 = "En route. Fais-le vite.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Bien sûr, capitaine, mais à mon avis, votre navire n'a pas besoin de réparations pour le moment.";
				link.l1 = "Je viens de demander...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "C'est possible, capitaine. Quelques restrictions cependant : il n'y a que deux endroits sur cette île adaptés pour cela. De plus, vous ne pouvez laisser ici qu'un seul officier par navire. Nous n'avons tout simplement pas assez de ressources pour maintenir les équipages ici. Pas encore. Enfin, il n'y a pas de place pour les navires de premier rang.";
			link.l1 = "Compris. Je suis prêt à laisser un navire ici.";
			link.l1.go = "shipstock";
			link.l2 = "Très bien, je vais la préparer.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Capitaine, il y a déjà trois de vos navires ancrés au quai. Il n'y a plus de place disponible.";
					link.l1 = "Tu as raison, j'ai oublié.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Capitaine, il y a déjà un vaisseau de premier rang ancré au quai. Il n'y a plus de place disponible.";
						link.l1 = "Tu as raison, j'ai oublié.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Capitaine, deux de vos navires sont déjà ancrés au quai. Il n'y a plus de place disponible.";
					link.l1 = "Tu as raison, j'ai oublié.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Capitaine, vous n'avez qu'un seul navire.";
				link.l1 = "Hm... Je devrais moins boire...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Quel navire veux-tu laisser ici ?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Attends, j'ai changé d'avis.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Voyons voir...";
			Link.l1 = "Très bien.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Attends, j'ai changé d'avis.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Voyons voir...";
			Link.l1 = "Très bien.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Attends, j'ai changé d'avis.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Voyons voir...";
			Link.l1 = "Très bien.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Attends, j'ai changé d'avis.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Voyons voir...";
			Link.l1 = "Très bien.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Attends, j'ai changé d'avis.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Capitaine, j'ai déjà mentionné que notre mouillage ne peut accueillir qu'un seul navire de premier rang. C'est trop grand pour l'espace disponible.";
					Link.l1 = "Tu as raison, j'ai oublié.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Capitaine, les navires de premier rang sont trop grands pour nos côtes. Je vous l'ai déjà dit.";
					Link.l1 = "Tu as raison, j'ai oublié.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Capitaine, emmenez tout son équipage sur votre vaisseau amiral sauf un officier.";
				Link.l1 = "Ah, d'accord ! Je ferai ça !";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Alors, nous devons garder ici un"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" nommé '"+chref.Ship.Name+"'. D'accord?";
			Link.l1 = "D'accord.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Attendez, j'ai changé d'avis.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
			if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				npchar.FstClassInHarbour = 1;
			}
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Très bien, nous veillerons à ce qu'elle soit livrée à un port sûr.";
			Link.l1 = "Excellent !";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Quel navire vas-tu prendre, capitaine ?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Attends, j'ai changé d'avis.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Capitaine, vous n'avez pas de place dans votre escadre pour un navire de plus.";
				link.l1 = "Hm. Il semble que tu as raison.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "La prends-tu ?";
			link.l1 = "Oui.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Attendez, j'ai changé d'avis.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = " Ici? Non. Mais Wulfric avait construit une énorme grange non loin d'ici. Un bâtiment solide, bien couvert de feuilles de palmier et de toile goudronnée. Il a une serrure et une pièce pour une cargaison suffisante pour remplir une douzaine de navires marchands. \nC'est vide maintenant, mais j'ai une clé si vous voulez l'examiner. On y va ? ";
			link.l1 = "Bien sûr ! Au fait : qu'en est-il des rats sur cette île ? Vont-ils gâcher mes marchandises dans la grange ?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Loup avait tout prévu aussi : il a ramené deux chats ici du continent. Il a oublié les mâles cependant, donc ces sacrées chattes font des bruits infernaux à chaque fois que la saison arrive. Mais elles chassent bien les souris et les rats. Ne t'inquiète pas, capitaine. Tes marchandises seront à l'abri des nuisibles et du vent.";
			link.l1 = "Super ! Je vais en faire bon usage. Garde ta clé pour toi et montre-moi cet entrepôt.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Suis-moi, capitaine.";
			link.l1 = "... ";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Eh bien maintenant... Une fille... Que fais-tu ici ?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "... ";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Señor! Señor "+pchar.name+" ne me tue pas s'il te plaît ! Je t'en supplie ! Je ne dirai rien à Tyrex ! Je déteste cette bête ! Je t'en supplie, por favor !";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Hé, fillette ! Tu as entendu ça ? Tu vas venir avec moi ou ce salaud costaud te tuera.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Je vais vous suivre, señor, où que vous m'emmeniez !";
			link.l1 = "Bien alors. Garde ta bouche fermée, ou je te tuerai si tu commences à crier ou à appeler Tyrex. Comment t'appelles-tu ?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Comporte-toi bien Mirabelle et cela se terminera bien pour toi. Reste près de moi et ne fais aucun bruit.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Je jure que je ne le ferai pas, señor.";
			link.l1 = "... ";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Señor ?";
			link.l1 = "Tu t'es bien débrouillée fille, je t'aime bien pour ça. Maintenant, nous allons sur mon navire où tu seras mise dans une petite cabine pour un certain temps. Je suis désolé mais je ne veux pas que tu courres vers Tyrex et lui dises quoi que ce soit.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Pas question, señor ! Je n'irais jamais voir Tyrex, este bastardo ! Je le hais ! Lo odio !!!";
			link.l1 = "Ouah ! Qu'est-ce qu'il t'a fait ?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Beaucoup... Je le déteste, je le déteste!";
			link.l1 = "Je vois. Une fois arrivés, tu vivras dans une maison assez chic. Seule. Garde-moi de bonne humeur et personne ne te fera jamais de mal. Maintenant, va à une chaloupe... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Sommes-nous arrives, senor ?";
			link.l1 = "Oui, ma douce. C'est mon village et ma maison. Je suis le propriétaire des lieux. Je suis un invité rare ici pourtant - trop de travail à faire là-bas. Assure-toi de garder ma maison propre pendant que tu y vis, sinon je te livrerai à Rodgar et ses charpentiers. N'hésite pas à te promener sur l'île, elle est très belle, mais il n'y a de toute façon aucune échappatoire.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Eh bien, nous y voilà. Voici ma demeure. Tout sur cette île m'appartient. Je ne viens pas souvent ici - je vis sur le navire après tout, mais quelqu'un doit tout de même s'occuper de la maison. Rodgar a gracieusement accepté de te confier ce rôle honorifique. Tu peux te promener autant que tu veux, même dans la jungle ou sur les plages, mais assure-toi d'avoir quelqu'un pour t'accompagner, car il y a encore des bêtes sauvages. Quoi qu'il en soit, tu ne peux pas partir d'ici sans un navire.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Je n'ai nulle part où fuir, señor "+pchar.name+"Je n'ai personne, et personne n'a besoin de moi. À moins que tu ne me vendes à un bordel...";
			link.l1 = "Au foyer, il y a une trappe qui mène sous terre, n'y allez pas, vous tomberez dans la grotte et vous briserez les os, ou vous ne pourrez pas revenir et vous pourriez mourir de faim. Et alors, ce serait dommage que je vous aie sauvé en vain.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Je n'ai nulle part où laisser senor "+pchar.name+"Je n'ai pas de famille et je ne sers à rien. Je pourrais finir dans un bordel à nouveau.";
			link.l1 = "Il y a une trappe qui mène à la caverne, restez loin de là. C'est sombre et dangereux là-dessous.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Je resterai à l'écart, señor.";
			link.l1 = "Il y a aussi une chambre à l'étage. Suivez-moi.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Voilà. Je t'ai montré toute la maison. Elle n'est pas pire que l'endroit de Tyrex où tu vivais auparavant. J'espère que cela te plaît.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Oui, señor. Vous avez une grande maison. Je promets d'en prendre bien soin en votre absence.";
			link.l1 = "Je suis heureux que tu sois si coopérative envers moi. J'espère que tu es honnête. Sois honnête avec moi ou tu le regretteras. Sois une bonne fille et ne me rends pas triste, et je serai bon pour toi. Charlie Prince tient sa parole !";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "Je te crois, ma chère. Je pense que tu seras plus en sécurité ici que d'être enchaînée dans cette sombre réserve où Tyrex te gardait.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Merci señor "+pchar.name+". Je vous remercie de ne pas laisser votre... camarade me tuer. Vous êtes si aimable envers moi...";
			link.l1 = "Hé, et tu es drôle,... Et ton visage est joli aussi, même avec une marque sur le front. J'espère que tout le reste est en place aussi... Eh bien, montre maintenant à ton capitaine ce que tu sais faire. Détendons-nous quelques heures après le roulis de la mer.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Très bien. C'est tout, j'ai - beaucoup de travail à faire. Et toi, installe-toi, rencontre Rodgar et les gars. Quand je reviendrai, nous discuterons un peu plus.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Merci, senor "+pchar.name+". Je vous remercie de ne pas avoir permis à votre... compère de me tuer. Vous êtes très aimable.";
			link.l1 = "Heh, tu es une drôle de petite chérie... Un joli minois aussi malgré la marque. J'espère que le reste est en place aussi... Maintenant, montre à ton capitaine ce que tu sais faire.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Très bien. C'est ça, j'ai - beaucoup de travail à faire. Et toi, installe-toi, rencontre Rodgar et les gars. Quand je reviendrai, nous discuterons un peu plus.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Seigneur "+pchar.name+" tu es si doux... Tu es un véritable gentleman. Tu dois être arrivé d'Europe il n'y a pas longtemps.";
			link.l1 = "Ne me flatte pas, petit menteur, je le crois. Heh, tu es douée, Mirabelle ! Tyrex a bon goût, hé-hé...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Je ne le suis pas. Vous êtes un gentilhomme. Mais vous faites semblant d'être grossier pour une raison quelconque. Mhmm... J'ai beaucoup aimé cela. J'attendrai de vous revoir...";
			link.l1 = "Ah oui, un gentilhomme... un gentilhomme de fortune, ha-ha ! Très bien ma douce, installe-toi ici pour l'instant.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Adieu, senor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", señor "+pchar.name+" ! Je suis très heureux de te voir. Comment vas-tu ?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Que diable m'emporte, que mon âme tremble !","Oh, mieux vaut vivre et mourir, sous le vaillant drapeau noir que je fais flotter!")+"Charlie Prince va bien, ma douce.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Ma douce, que dirais-tu de rendre un capitaine un peu plus heureux ?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Tout pour vous, señor !";
			link.l1 = RandPhraseSimple("Préparez les grappins !","Abordez-les !");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Senor, vous êtes un magicien ! J'espère que cela vous a plu aussi ? J'ai fait de mon mieux.";
			link.l1 = "Tu as fait du bon travail, ma chérie.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Ce n'est pas vrai, pas vrai ! Señor "+pchar.name+" est bon et gentil ! Il fait seulement semblant d'être un pirate maléfique ! C'est vous, señor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", señor "+pchar.name+"! Je suis très heureux de te voir. Comment vas-tu ? Pourquoi es-tu si triste ?";
			link.l1 = "Bonjour, Mirabelle. Pourquoi penses-tu que je suis triste ?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Eh bien, je le vois. Tu n'es pas dans ton état habituel. Veux-tu que je te remonte le moral ? Allez ! J'ai cueilli des fruits vraiment délicieux dans la jungle, et le poisson que Rodgar et ses gars ont pêché hier est rôti et encore chaud.";
			link.l1 = "Attends. Je veux te parler.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Bien sûr, señor, quoi que vous disiez. Je suis tout ouïe.";
			link.l1 = "Dis-moi comment tu es tombé entre les mains de Tyrex et pourquoi as-tu la marque d'un voleur sur le front. N'aie pas peur, je ne te ferai jamais de mal. J'ai seulement besoin d'entendre ton histoire.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, señor ! Mon histoire est brève et ennuyeuse. Je suis né à Porto Rico, mon père était un gentilhomme blanc, ma mère - une Indienne. Je n'ai jamais vu mon père. Quand j'étais enfant, j'étais serviteur et en grandissant, j'ai commis la folie de voler les bijoux de mon maître. Je n'en ai jamais eu à moi et j'en voulais un si désespérément, juste pour l'essayer pendant une journée. Bien sûr, ils ont tout découvert\nIl y eut un procès, j'ai été fouetté, marqué au fer et mis en prison à San Juan. Je n'y suis pas resté trop longtemps : un des officiers a passé un accord avec un chef et j'ai été vendu à un bordel de Philipsburg pour une poignée de doublons d'or\nJ'y ai passé environ un an. Un jour malheureux, nous avons été visités par Tyrex et son sale ami à lunettes.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Oui-oui, il s'appelait señor Pasquale Lavoisier. Je n'ai aucune idée de ce qu'ils ont vu en moi, mais peu de temps après leur visite, Tyrex m'a achetée à Madame Johanna et m'a enfermée dans une maison pleine de coffres et de marchandises. C'était le pire moment de ma vie, pire encore que les jours passés dans la prison de San Juan. Tyrex me rendait visite tous les jours, sauf quand il était en mer et alors je pouvais respirer librement, mais chaque fois que señor Lavoisier venait je... je.... C'était le pire de tout. Señor "+pchar.name+", s'il vous plaît, puis-je ne pas parler de cela ?\nJe ne sais pas combien de temps j'y suis resté. Et puis vous êtes venu et m'avez emmené loin de cette horrible maison. J'ai eu beaucoup de chance que vous ayez été si aimable.";
			link.l1 = "Gentille ? Mirabelle, mais j'ai fait exactement la même chose avec toi : je t'ai emmenée sur une île et je t'ai enfermée dans une maison.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Non, señor, ce n'est pas vrai. Suis-je enfermé ici ? Je fais une promenade autour de l'île chaque jour. C'est un endroit merveilleux et paisible. Dois-je faire beaucoup de travaux ménagers ? Pas du tout, et je m'y habitue de toute façon. Et vous n'êtes pas comme Tyrex, pas comme son ami marchand. Je suis toujours heureuse de vous voir, vous êtes si jeune et beau. Et un gentilhomme aussi...";
			link.l1 = "Mirabelle, veux-tu que je te conduise dans une ville ? Je te donnerai assez d'argent. Où ? Choisis n'importe quelle colonie.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Señor, voulez-vous me chasser ? Je vous en prie, ne le faites pas, je vous en supplie !";
			link.l1 = "Eh bien... Je pensais que tu voudrais retourner à la vie normale...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, señor "+pchar.name+", et qu'y a-t-il pour moi ? Comment vais-je me marier en étant une métisse marquée ? Je serai de nouveau vendue à un bordel. S'il vous plaît, ne me renvoyez pas. J'aime cet endroit, je ne me suis jamais sentie aussi paisible et en sécurité qu'ici. Rodgar et ses gars sont de bons types, nous sommes amis et ils ne m'ont jamais fait de mal, chacun d'eux risquerait sa vie pour moi. J'aime passer du temps avec eux et on s'amuse bien ! Parfois, on fait un feu sur la plage et je danse la samba. S'il vous plaît, señor, je ferai n'importe quoi pour vous, laissez-moi juste rester !";
			link.l1 = "D'accord, Mirabelle, reste ici puisque tu aimes tant cet endroit. Sache juste que tu n'es pas prisonnière ici, tu peux toujours me demander de t'emmener loin d'ici.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Mon cher bon seigneur, merci ! Merci ! Merci ! Je ne te demanderai jamais quelque chose comme ça - je veux rester prisonnier de cette île... et ton prisonnier, hi-hi... Tu es si gentil mais triste aujourd'hui ! Tu ne chantes pas et ne jures pas comme d'habitude.";
			link.l1 = "Je pourrais chanter mais plus de jurons, Mirabelle. Et... je suis désolé si j'ai jamais été impoli avec toi.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Seras-tu sévère et strict comme un lord anglais?.. Ah... señor, veux-tu que je danse et chante ce soir ? Juste pour toi. Maintenant, viens avec moi ! Il n'y a pas de meilleur remède à la tristesse que l'amour. Tu m'as tellement manqué.";
			link.l1 = "Hah ! Bon point, ma chère fille... Allons-y.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ah, señor "+pchar.name+", tu étais si doux aujourd'hui, mhm... Es-tu satisfait de moi, mon cher capitán ?";
			link.l1 = "Tout était délicieux, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", señor "+pchar.name+"! Je suis si heureux de te voir ! Comment vas-tu ?";
			link.l1 = ""+LinkRandPhrase("Ravi de te voir aussi, ma fille.","Salut, Mirabelle. Tu es toujours la même - joyeuse et belle, quel agréable spectacle.","Bonjour, belle. Tu es éblouissante !")+"Je vais très bien. J'espère que vous allez bien aussi.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, tu me manques déjà, toi et ta fouine. Vas-tu embrasser ton loup des mers ?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ah, mon doux capitaine, tu m'as manqué aussi ! Allez, je suis à bout !";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Señor Capitaine ! Capitaine "+pchar.name+" ! Je suis si heureux ! Tu nous sauveras !";
			link.l1 = "Je suis aussi content de te voir, Mirabelle. Alors, qu'en est-il des pertes ?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Capitaine, Capitaine, merci ! Vous êtes le meilleur, le plus gentil ! Vous ne m'avez pas seulement sauvé des monstres, mais vous m'avez aussi donné une nouvelle vie ! À nous tous !";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Señor Capitaine !";
			link.l1 = "Bonjour à toi aussi, beauté. Tu ne t'ennuies pas, n'est-ce pas ?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ah, Capitaine ! Depuis que vous m'avez sauvé de cette affreuse maison, ma vie a retrouvé des couleurs et de la joie.";
			link.l1 = "Es-tu heureux ?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Bien sûr ! Et j'aimerais partager ce bonheur avec vous... Je vous attendrai dans votre chambre, à l'étage.";
			link.l1 = "Quelle femme...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Señor Capitaine !";
			link.l1 = "Bonjour à toi aussi, beauté. Pas ennuyée, hein ?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, Capitaine ! Depuis que vous m'avez sauvé de cette maison épouvantable, ma vie a retrouvé des couleurs et de la joie.";
			link.l1 = "Es-tu heureux ?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Très ! Sauf...";
			link.l1 = "Je vois, tu veux me demander quelque chose ?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Oui, Capitaine ! J'aimerais... partager mon bonheur avec un certain homme...";
			link.l1 = "Aura-t-il à redire ?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "Non, non, Capitaine. Nous serions heureux ensemble, j'en suis sûr. Juste... le permettrez-vous ?";
			link.l1 = "Tu le mérites plus que quiconque. Mais je ne vais pas vous marier, ne demande même pas !";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha ! Mon gentilhomme ! Merci, Senor Capitaine. Je ne sais pas ce qu'on dit de vous dans le grand monde, mais j'ai toujours vu en vous la personne la plus gentille et la plus éclatante.";
			link.l1 = "Bonne chance à toi, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Merde de ladrones ! Peu importe, notre courrier est déjà en route vers Porto Bello. Bientôt notre escadron arrivera et...";
			link.l1 = TimeGreeting()+", Votre Altesse. C'est un plaisir de vous voir dans un si beau manoir. J'espère que vous le garderez après notre départ. Si j'étais vous, je ne compterais pas sur l'escadre, de plus, nous ne resterons pas ici plus de trois jours. Je parie que vous comprenez que les nobles dons de Porto Bello n'arriveront pas ici pour vous aider si tôt. Alors, passons directement aux affaires, voulez-vous ?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Déjà parler affaires ? Regarde par la fenêtre ! Regarde ce que tes coupe-jarrets font dans les rues et dans les maisons !";
			link.l1 = "Oh, votre Altesse, cela n'est rien comparé à ce qu'ils feront si vous ne coopérez pas suffisamment. J'espère que vous comprenez qui sont ces hommes...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "Je sais de quoi est capable cet infâme pirate Charlie Prince ! Je sais qui est son patron ! En temps voulu, nous détruirons votre repaire de bandits à Hispaniola ! Combien ?";
			link.l1 = "Ne perdez pas vos mots, mon cher gouverneur. Vous feriez mieux de me procurer 250 000 pesos.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Quoi?! Ton insolence est sans limites! C'est un vol!";
			link.l1 = "C'est du pillage, bien sûr. Quoi d'autre cela pourrait-il être ? Rassemblez vos élites, vos marchands et négociants, amassez l'or dans un grand coffre car sinon... je vous rendrai la vie bien plus difficile, à vous et à votre peuple.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Putain de pirate ! Batard ! Heretique ! Va te faire foutre !";
			link.l1 = "À cause de ta langue sale, j'augmente la rançon à 300 000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "BRULE EN ENFER, FILS DE PUTE!!!";
			link.l1 = "350 000. Veux-tu continuer?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Il n'y a pas une telle somme d'argent dans la ville !";
			link.l1 = "Tu mens. Cela ne se peut tout simplement pas. Nous pouvons rassembler au moins un million ici, mais je crains que nous n'ayons pas assez de temps pour le faire. Par conséquent, je serai aimable et généreux. Tu connais la somme. Va la chercher.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Je te le redis, Charlie Prince : il n'y a pas d'argent comme ça à Carthagène !";
			link.l1 = "Oh... comment peux-tu être si ennuyeux. Sabre! Fouille partout et amène ici tous ceux que tu trouves. Cherche bien! Et nous attendrons ici pour l'instant, ta grâce...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Eh, senor 'Têtu' ! N'avez-vous pas changé d'avis concernant la collecte d'argent dans la bonne ville de Carthagène ?... Que s'est-il passé, pourquoi êtes-vous si sérieux tout à coup ?! Ça va ? Dois-je vous apporter de l'eau ?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Autant que je comprends, ces deux dames sont votre épouse et votre fille, ai-je raison? La troisième fille ressemble à une servante, vous semblez vous en foutre donc nous ne lui ferons aucun mal, mais ces deux beautés pourraient attirer l'attention de mon frère d'armes, señor Cutlass. Il semble les apprécier, señor. Alors quoi? Allez-vous gérer la rançon?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Je... j'aurai besoin de temps.";
			link.l1 = "Aha ! Maintenant tu parles ! Alors, qui est le bastardo ici ? Tu t'en foutais de mes hommes terrorisant tes citoyens, mais tes deux femmes, c'est une tout autre affaire, n'est-ce pas ? As-tu osé marchander avec moi, salaud ? Je vais te montrer ce que cela signifie de défier Charlie Prince !";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Va chercher cette foutue rançon. 350 000 et pas un peso de moins. Tu as un jour. On va rester ici pour boire du vin et se mêler à ces charmantes femmes... Sois rapide amigo, sinon mon ami ici, señor Sabre, pourrait tomber amoureux de tes beautés et alors tu devras aussi les racheter. En avant ! Marche !";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Prends ton argent ensanglanté, Charlie Prince !";
			link.l1 = "As-tu réuni une rançon ? Splendide ! Mais tu es en retard d'une heure, mon cher gouverneur. Cette heure supplémentaire m'a permis, ainsi qu'au Cutlass, de comprendre que nos vies seraient bien trop ennuyeuses sans ces beautés qui ont été si aimables et bavardes avec nous...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Toi... toi !";
			link.l1 = "Ah, tu es trop nerveux à cause de ton travail, mon ami. Je plaisantais... Sabre! Allons-y, nous partons!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Ah, donc c'est Le Prince Charlie, le fameux pirate, la terreur des Espagnols du Main Sud !";
			link.l1 = RandSwear()+"Heh, je n'avais aucune idée que je suis si populaire à Tortuga. Comment t'appelles-tu, douce fille ?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Je m'appelle Camilla.";
			link.l1 = "Camilla... Je connaissais une fille du même nom en France. C'était il y a si longtemps!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(vomissant) ... merde... Je suis désolé princesse, mais le Prince est un peu ivre ce soir. Alors... hum.. pourquoi es-tu venue me voir ?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Pour diverses raisons. Ou peut-être pour aucune raison.";
			link.l1 = "Dieu, c'est trop compliqué. Tu sembles être un mystère, mademoiselle.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Chaque demoiselle doit avoir son mystère.";
			link.l1 = "On dirait que tu veux que je résolve ce mystère. Non? Je suis un maître pour résoudre les mystères des dames, je te le jure! Allons-nous à la taverne pour boire du vin? Je te trouverai le meilleur festin!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... J'aime les durs à cuire. Mais je ne boirai pas de vin en bas près des ivrognes de bas étage. Trouve-nous une chambre, nous boirons et parlerons là-bas.";
			link.l1 = RandSwear()+"Tu es brûlant ! Suis-moi !";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Allez... Sers-moi ça, ne fais pas attendre la dame !";
			link.l1 = "Bien sûr, ma douce !";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Rien qu'à y penser, je suis ici tout seul avec Charlie Prince, buvant un vin excellent...";
			link.l1 = "Tu vas apprécier ce voyage avec moi, oh je te le promets ! Charlie Prince est doux et aimable avec les dames qui se soumettent à lui. Te soumettras-tu, princesse ?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Tee-hee... Bien sûr, mon chou ! Tes promesses sont si tentantes, tu sais...";
			link.l1 = "Eh bien, ne perdons pas de temps alors, beauté ?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Oh! J'adore! De vrais hommes!..";
			link.l1 = "... ";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Avez-vous aimé cela, ma princesse ?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Bien sûr ! J'espère que je t'ai plu aussi.";
			link.l1 = "Heh! Même ma tête est maintenant aussi claire que du cristal !";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Prince, j'ai une requête pour toi. M'aideras-tu ?";
			link.l1 = "Je décrocherai une étoile du ciel pour toi, ha-ha ! Vas-y.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "Je dois me rendre à La Vega, pour voir Tyrex. J'ai peur de lui, mais vous faites des affaires ensemble. Je vous en prie, emmenez-moi à lui.";
			link.l1 = "Regarde ça ! Et pourquoi une fille si douce et fragile voudrait-elle voir le Gardien du Code ?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Cette douce et fragile demoiselle aimerait gagner quelques piécettes. Mon défunt père et mes frères ne m'ont pas laissé beaucoup d'argent. Tyrex peut arranger ça.";
			link.l1 = "Ah vraiment ? Et comment ? Tu veux une piste pour une galion espagnol ? Ha-ha !";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Piller les caravanes et les villes, c'est un métier pour les durs, tout comme toi, ma belle. J'ai une autre affaire pour Marcus. Il achète et vend des informations, n'est-ce pas ? J'ai quelque chose... Pas moyen que je l'utilise moi-même, mais lui pourrait. Je serai déjà content d'en tirer un petit bénéfice.";
			link.l1 = "Intéressant ! Dis-m'en plus.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... Je ne sais pas...";
			link.l1 = "Oh, allez ! Considérez-moi comme la main droite de Tyrex, j'ai déjà creusé pas mal pour lui, faites-moi confiance. Si vos informations en valent la peine - je les achèterai moi-même.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "D'accord. Je te dirai plus, mais pas de détails avant que je reçoive l'argent. Marché conclu, chérie ?";
			link.l1 = "Bien sûr, ma jolie. Charlie Prince ne fout pas ses partenaires... tu vois ce que je veux dire, ha-ha-ha ! Vas-y, je suis tout ouïe.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Mon père était capitaine d'un schooner marchand. Un jour, il a appris l'existence d'un ancien campement minier espagnol enfoui dans les jungles de la Terre Ferme. Il y a vingt ans, il a été détruit par un tremblement de terre. Les mineurs l'ont abandonné et les passages secrets ont été oubliés. Sauf un. Mon père l'a trouvé\nIl a emmené mes frères et un guide là-bas et ils ont découvert l'endroit rempli d'or extrait et fondu il y a des années. Beaucoup d'or. Un million de pesos au moins. Père était retourné au navire pour trouver des hommes pour transporter l'or, mais il a été choqué de découvrir qu'elle était partie. Il semble que son second avait déclenché une mutinerie et ils l'ont laissé, lui et mes frères, sur des rives désertes\nIls ont construit un long bateau et ont navigué le long de la côte en cherchant désespérément un endroit habité, mais... (sanglots) une tempête les a frappés et mes (sanglots) frères sont morts. Père a survécu, mais il n'a pas vécu longtemps après son retour à la maison - la mort de mes frères le tuait lentement jour après jour. Avant de mourir, il a fait une carte et me l'a donnée\nIl m'a dit que lorsque je me marierai, mon mari devrait y aller, prendre l'or et nous vivrons comme des rois. Bien sûr que nous le ferons, mais je ne laisserai pas mon homme entrer dans ces jungles maudites. Pas encore ! Un million de pesos, disait mon père, mais ce n'est tout simplement pas de mon niveau. Un tel prix, seuls les meilleurs et les plus robustes des hommes peuvent l'obtenir - des hommes comme Marcus Tyrex. C'est pourquoi je vais le rencontrer.";
			link.l1 = "Combien veux-tu pour la carte ?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Deux cents doublons d'or. Ce n'est rien comparé au prix. Tyrex acceptera cela, j'en suis sûr. Il est aussi riche que Crassus.";
			link.l1 = "Hé ! Et si tout cela n'était qu'une supercherie ?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "J'ai l'air suicidaire? Essayer de contrarier Tyrex? Chérie, mieux vaut vivre dans la pauvreté que de ne pas vivre du tout. Alors, tu m'y emmèneras? S'il te plaît...";
			link.l1 = "Où est la carte ? Me la montreras-tu ?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Mon pretre le garde en securite. Je te le montrerai pour 200 doublons.";
			link.l1 = "Très bien ! Je l'achète. Les étrangers dans les tavernes demandent parfois beaucoup plus pour des ordures.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Est-ce vrai, chéri? Je suis si heureux que je ne vais pas à La Vega! Pour être honnête, je crains Marcus. Je te crains aussi, d'ailleurs... mais un peu moins.";
			link.l1 = "Une si douce petite fille n'a pas besoin de me craindre. Où dois-je apporter l'argent ?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Passons un marché : retrouvez-moi dans notre église tous les jours de dix heures du matin à une heure de l'après-midi. Je me sentirai bien plus en sécurité sous la protection de ce lieu sacré. Nous conclurons notre marché là-bas.";
			link.l1 = "Tu me crains encore ? Ha-ha ! Ne t'inquiète pas Camilla, je ne te tromperai pas. Charlie Prince ne ferait pas une chose si basse pour deux cents doublons, d'ailleurs je veux t'aider.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Merveilleux. Très bien alors, beau garçon, je t'attendrai... Merci pour le moment incroyable que nous avons passé ensemble ce soir ! Je suis si heureuse que nous nous soyons rencontrés !";
			link.l1 = "À bientôt, jolie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Alors ? As-tu apporté l'argent, ma douce ?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Oui. Ayez votre or et maintenant donnez-moi la carte.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Je suis juste après ça.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Merci, ma douce... Tiens, prends-le. Je jure sur la mémoire de mon père - cette carte n'est pas une fausse, elle te mènera directement là où tu dois aller...";
			link.l1 = "Bien, ma douce. Que dirais-tu de fêter notre accord comme la dernière fois ?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "J'aimerais bien, Prince, mais je me prépare pour une confession devant mon prêtre, donc je suis obligé de rester loin de toute tentation pour l'instant. Faisons cela la prochaine fois.";
			link.l1 = "Eh bien, tu me taquines, fillette. Soit! Pas de temps à perdre : nous allons lever l'ancre. Je te jure que je doublerai ton intérêt si la carte de ton père me mène vraiment à l'or.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Tu es si généreux, chéri. Bon voyage !";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Vos salopards ont tué mon père et mes frères. Votre attaque sur Carthagène a apporté le chagrin à chaque famille là-bas. J'espère que vous avez peur maintenant, aussi peur que nous, citoyens de Carthagène, l'étions quand vos brutes se prélassaient dans les rues et dans les maisons. Vous brûlerez en enfer, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "Si peu de choses en ce monde me réjouissent autant que de regarder les rats dans la boîte se déchirer entre eux !\nSeul le rat le plus fort et le plus répugnant survit. Ensuite, tout ce qu'il vous reste à faire, c'est de l'écraser...";
			link.l1 = "Argh ! Qui es-tu ?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "Je suis don Enrico. Les salauds anglais m'appellent Fox, les Hollandais m'appellent Vos, les Français m'appellent Renaud. Mais je préfère mon surnom espagnol - Zorro. Je punis le mal qui torture et terrorise le peuple, la partie la moins protégée de la population. \nCe procès aujourd'hui jugera quatre pirates de Marcus Tyrex : Bold Jeffry, Pelly le Sabre, Luke le Lutin et Charlie Prince – ces bandits sont responsables d'un massacre à Merida et Cartagena. Le dernier salaud appelé Beau Jean n'est pas venu ici, il doit être le plus intelligent de votre bande.";
			link.l1 = "Quoi?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Tu es un salaud, Charlie Prince, mais tu n'es pas un idiot. J'ai déjà compris, je pense. C'est un piège pour vous tous tendu par moi avec l'aide de cartes fausses, de documents, de mots et de promesses d'or et d'argent. Je vous ai tous attirés dans ces cachots où vous vous êtes détruits les uns les autres poussés par vos traits dégoûtants : l'envie, l'avidité, la méchanceté et l'absence de scrupules. C'était vraiment un châtiment juste !";
			link.l1 = "Camilla... J'aurais dû savoir qu'il y avait quelque chose de louche chez cette fille !";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Une fille nommée Camilla vivait une vie paisible à Carthagène avec son père et ses frères, elle était sur le point de se marier lorsque toi et tes démons avez attaqué la ville. Tes pirates ont tué tous ses proches, alors elle a juré de faire tout son possible pour les venger. C'était un rôle difficile à jouer pour elle. Elle a même dû coucher avec un salaud responsable de la mort de sa famille. J'ai peur d'imaginer ce qu'elle ressentait pendant l'acte\nLa pauvre fille a passé des jours à l'église à prier pour le pardon. Elle a donné les doublons ensanglantés que tu lui as donnés aux victimes qui ont le plus souffert de ton attaque. Elle est maintenant dans un monastère, pauvre âme. Tu as brisé sa vie, ordure ! Réfléchis-y ! Pense à combien de Camillas, Isabelas, Rositas tu as violées et rendues veuves ! Combien de Juans, Carlos, Pedros vous, salauds, avez tués et torturés !\nSouviens-toi de Mérida ! Souviens-toi comment tu as promis au chef de la ville de ne pas y mettre le feu et puis tu as brûlé tout l'endroit jusqu'au sol !";
			link.l1 = "Je n'ai jamais voulu faire ça ! Quand j'ai quitté la résidence, le feu était déjà partout. Je n'ai pas ordonné cela...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Tu es responsable des actes de tes pirates. Des hommes morts pendent à ton cou et bientôt ils te traîneront en enfer !";
			link.l1 = "Viens donc ! Hein ? Bats-toi avec moi ! C'est ce que tu veux, non ?! Allons-y alors !";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "Non, Charlie Prince. Ne touche pas à ton arme, c'est inutile... Je pourrais te tuer facilement, cependant une mort rapide n'est pas suffisante pour un salaud comme toi. Tu resteras dans ce cachot pour toujours. La porte par laquelle tu es entré est bloquée par une pierre à l'extérieur, la porte derrière moi sera également bloquée, en plus il y a aussi des barreaux solides qui la protègent. C'est ainsi, il n'y a pas d'autre issue que ces deux portes\nQu'est-ce que... J'ai verrouillé toutes les portes !";
				link.l1 = "Qu'est-ce qui se passe...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "Non, Charlie Prince. Ne t'empare pas de ton arme, c'est inutile... Je pourrais te tuer facilement, cependant une mort rapide n'est pas suffisante pour un salopard comme toi. Tu resteras dans ce cachot pour toujours. La porte par laquelle tu es entré ici est bloquée par une pierre à l'extérieur, la porte derrière moi sera bloquée aussi, de plus il y a aussi des barreaux solides qui la protègent. C'est tout, il n'y a pas d'issue sauf par ces deux portes\nIl y a de l'eau en bas, donc tu auras suffisamment de temps pour réfléchir à tes actes. Tout seul ici, dans l'obscurité, peut-être, tu te repentiras de ce que tu as fait avant de mourir de faim ou de devenir fou\nUne dernière chose - le trésor en dessous est un faux. Les lingots d'or ne sont rien d'autre qu'un plomb coloré. Les doublons sont réels cependant, mais il n'y en a que quelques-uns, juste assez pour recouvrir les pierres dans les coffres. Une fin digne pour les pirates, hein ? Vous vous êtes entre-tués pour un faux trésor, Prince. Adieu maintenant. Prie pour ton âme de pécheur, Charlie Prince, si tu te souviens encore comment...";
		// belamour legendary edition -->
				link.l1 = "Je viens de tuer toute l'avant-garde de Marcus Tyrex ! Tu crois que ces barreaux rouillés vont m'arrêter ?! Je vais les briser avec ta propre tête !";
				link.l1.go = "enrico_5a";
				link.l2 = "Peut-être que je l'ai mérité. Mais je n'abandonnerai pas, tu entends ?! Je trouverai un moyen, je le fais toujours !";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Tu as raison, la porte est fiable, même si elle est ancienne. Merci de ne pas avoir abaissé la grille-cela m'aurait retardé. Mais pas pour longtemps.";
			link.l1 = "Hercule Tonzag, Gaston le Chauve ! J'aurais dû deviner qu'un homme comme toi s'allierait avec le Prince et tous ses semblables. Quelle chance de te rencontrer ici, aussi.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Chanceux, tu dis? Eh bien, si tu es pressé de mourir... Bien que je pensais que tu ne l'étais pas, vu que tu l'as laissé mourir de faim au lieu de l'affronter.";
			link.l1 = "Tu m'accuses de lâcheté ? Quelle folie de ta part. Comme je l'ai dit au Prince, la mort est un châtiment trop facile pour lui. Il n'est pas de taille face à moi.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "Et tu n'es pas de taille face à moi, Don.";
			link.l1 = "Dix ans auparavant ? Certainement. Maintenant ? A peine. De plus...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "En outre, quoi ? Pourquoi cette pause dramatique ? Bien que, compte tenu de votre masque de carnaval... Un peu tôt pour me mettre hors jeu, n'est-ce pas ?";
			link.l1 = "Tu as brisé la porte, mais la force brute seule ne suffira pas avec moi. Comment sont tes réflexes ? Ta vision ? Avec un seul oeil. Moi, j'ai toujours les deux.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Eh bien, pour l'instant, en tout cas. Heh-heh.";
			link.l1 = "Pour Porto Bello, tu mérites un supplice pire que le Prince !";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Oh, alors tu as entendu ce que j'ai fait ? Je suppose qu'ils vont continuer à bavarder à ce sujet parmi les tiens pendant un moment. Alors tu sais par quoi je suis passé.";
			link.l1 = "Tu es vieux, Tonzag, et cette fois ton arrogance causera ta perte. Et oui, je n'en ai pas seulement entendu parler - Carthagène, Mérida sont ton oeuvre. Tout comme Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Je l'aurais pris comme un compliment, mais non, ce n'est pas mon oeuvre. Bien que cela puisse sembler similaire, de loin. Trop amateur. D'ailleurs, même à Porto Bello, il y a eu... des incidents.";
			link.l1 = "Incidents ?! Ce jour-là, une personne est morte... Et étant donné que tu as déclenché ce massacre, je te tiens toujours pour responsable, même si tu n'as pas tué tout le monde toi-même. Je te reproche chaque 'incident'.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Une personne, dites-vous... Beaucoup sont morts ce jour-là. Soyez précis.";
			link.l1 = "Vraiment, tu n'as pas de coeur si tu peux dire cela ! Mais je vais répondre : celui que tu n'aurais pas dû tuer. Mon père, Don de la Vega. S'il était vivant, je n'aurais pas pris ce chemin, et vous seriez tous encore en vie.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Tais-toi, morveux. Ma chère épouse... est aussi morte là-bas.";
			link.l1 = "Tu attends des condoléances ? Tu n'en auras pas. C'est le châtiment du Seigneur pour toi. On dirait que tu as un coeur - petit et noir. Et je le trouverai avec ma lame.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Oh, les drames autour de mon coeur. Vous vous trompez si vous pensez avoir vu pire que moi.";
			link.l1 = "Penses-tu que je ne suis qu'un jeune riche gâté dilapidant de l'argent ? Sache ceci : je n'ai dépensé pas un seul doublon en jeux de hasard ou en femmes ! J'ai tout jeté dans la lutte contre des gens comme toi et j'y ai consacré ma vie !";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "Et pour quoi ? Cela ne semble pas très réussi. Les routes commerciales sont toujours infestées de pirates. Vous êtes seul dans votre croisade. Et ils sont une légion entière.";
			link.l1 = "Quelqu'un doit le faire. Au moins quelqu'un. Et peut-être qu'en tuant juste un capitaine pirate, je sauverai quelques vies.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Insensé. Idéaliste. Et... d'une certaine façon, noble, je dirais, si ce n'était pas pour tes méthodes. Déshonorables, comme tes ennemis. Au final, tu n'es... pas mieux.";
			link.l1 = "Ne me fais pas la morale ! L'honneur est pour ceux qui suivent ses lois. Je te comprends. Je pense comme toi. Et je punis.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Tu as raison. T'enseigner est inutile. Alors, nous ne nous séparerons pas en paix. Mais je me fiche de toi, Don Enrico. Tu ne vaux même pas mon temps.";
			link.l1 = "Que veux-tu dire...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Tout va bien, Capitaine ? Je vous avais prévenu d'être prudent. J'aurais dû écouter mon instinct.";
			link.l1 = "Oui, ça va. Merci, Hercule. Juste un peu...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...choqué? N'ayez pas peur de l'admettre - c'est normal pour quelqu'un de votre âge et dans une situation comme celle-ci. De plus, ce Don est un bon manipulateur.";
			link.l1 = "Uh-huh. Bien qu'il semblait avoir peur de toi. Cela m'a surpris. Mais cela m'a aussi ramené à la raison. Au fait, est-il toujours vivant ? On dirait bien. Tu ne devrais pas lui tourner le dos.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Vivant, mais abasourdi. Reprenant ses esprits. J'aurais dû viser la tête, pas le torse - il s'avère que notre noble hidalgo porte une cuirasse légère mais robuste sous son manteau. Heh, même Fleetwood se contentait d'un simple pourpoint. Sinon, il y aurait déjà une mare de sang ici.";
			link.l1 = "Et comment t'es-tu retrouvé ici ? Au même endroit que lui ?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Pas le temps pour ça maintenant. Il sera bientôt remis sur pied. Pour l'instant, nous allons soulever cette grille.";
			link.l1 = "Nous... quoi ?? Bien sûr, tu pourrais être Hercule, mais...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Les hommes de ma jeunesse étaient forgés durs. Ces gonds ont des pattes courtes. Allez, donne-moi un coup de main, Capitaine - je pourrais être Hercule, mais je prends de l'âge.";
			link.l1 = "D'accord, à trois ! Et soulève !";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Penses-tu que tu as ruiné tous mes plans et gagné ? C'était inattendu, bien sûr, mais j'ai encore tout prévu !";
			link.l1 = "Comme cette cuirasse légère sous tes vêtements. Pourquoi cela et pas une complète par-dessus ? Juste pour exhiber ton manteau ?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Je ne suis pas une demoiselle, Prince. Mes raisons sont purement pratiques - une cuirasse complète restreint trop mes mouvements. Chacun a sa propre approche.";
			link.l1 = "Et me voilà, un Français, déjà habitué à porter des cuirasses, contrairement à un Espagnol. Quelle ironie. Alors, et maintenant ? Vous n'avez pas pu nous piéger. Vous avez tout préparé... Un duel faisait-il partie des possibilités ? Ou bien la lame - et même la cuirasse - sont-elles pour tout sauf les vrais combats ?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Essayes-tu aussi de me traiter de lâche ? Comme je l'ai dit, tu mérites une longue souffrance, pas la mort dans un duel. Quel est l'intérêt si vos âmes n'ont pas le temps de supporter et de comprendre tous vos péchés ici, sur Terre ?";
			link.l1 = "La route de l'enfer est pavée de bonnes intentions, comme on dit... Et ne pas tourmenter vos victimes ternirait-il votre propre âme ?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Jamais. Pas question. Car je reste fidèle à moi-même et à mes principes.";
			link.l1 = "Aha, pas comme nous. Tu as tant dit sur le fait que nous sommes des canailles infâmes sans un brin d'honneur, alors... pourquoi ne pas être à la hauteur de tes attentes ? Nous nous occuperons de toi nous-mêmes. Ensemble.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "J'ai une proposition pour vous, Don Enrico. Je vous défie en duel, ici et maintenant. Comme un noble à un noble.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m. Tu n'aurais aucune chance autrement. Tonzag sera délicat, bien sûr... Alors je m'occuperai de toi en premier.";
			link.l1 = "Comme s'il te laisserait faire ça.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "Toi ? Un noble ? Peut-être es-tu un “prince”, mais je doute qu'il y ait une goutte de sang noble en toi.";
			link.l1 = "Tu m'as révélé ton vrai nom. Je vais te révéler le mien. Je suis Charles de Maure. Et nous avons suffisamment insulté l'honneur de l'autre pour que chacun de nous ait le droit de demander réparation. Défends-toi, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "Mais ne regrette pas ta décision plus tard.";
			link.l1 = "J'ai regretté bien des décisions dans ma vie, mais celle-ci n'en fera pas partie. En garde !";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Ça va, Capitaine ? Notre noble hidalgo ne portait pas seulement une cuirasse - il a aussi empoisonné sa lame. Tenez, prenez ça. J'en ai toujours quelques-uns sur moi quand je me promène dans la jungle - on ne sait jamais quand un serpent pourrait mordre ou un indigène pourrait lancer un dard empoisonné.";
			link.l1 = "Merci, Hercule. Je vais bien. Ton arrivée opportune m'a aidé à me ressaisir.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "N'en parle pas. Allons-y, je vais te sortir d'ici - il a mentionné bloquer l'entrée avec des pierres. J'ai trouvé un autre passage, un raccourci.";
			link.l1 = "Dis-moi, Hercule... que s'est-il passé exactement à Porto Bello ? Et quand ?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Je n'ai pas envie d'en parler aujourd'hui. Mais peut-être un jour, autour d'un verre de vin ou de quelque chose de plus fort. Pour l'instant, sortons d'ici - le morveux avait raison, je vieillis. Je veux me reposer sur le navire.";
			link.l1 = "Alors, montre le chemin.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Dis-moi, frère - comment as-tu pu te transformer en telle abomination ? Quand je t'ai dit de te familiariser avec les pirates, je ne parlais pas de brûler des villes, de tuer des civils innocents et de torturer des femmes. Même une guerre peut être menée avec honneur et dignité\nTu es la honte de notre famille. Heureusement que notre père n'est pas ici : il serait mort de honte en sachant que son fils est devenu un pirate et un bandit !";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Frère ! Frère !\nM'entends-tu ?\nIl y a un passage derrière l'une des deux portes. La porte peut être ouverte. Une clé est près de toi !\nTrouve-la sur les escaliers. Sur les escaliers !..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, bonjour mon brave coupe-jarret ! Pourquoi es-tu si triste ? La mer, l'or, le rhum et les femmes - que te manque-t-il d'autre ? Te souviens-tu de notre première rencontre ? Je t'avais dit à l'époque - j'ai besoin d'hommes qui n'ont pas peur de l'odeur de la poudre à canon ou de saigner les rivières rouges à sec. Tu as dépassé toutes mes espérances ! Tu es devenu un vrai pirate, Charlie Prince ! Ha-ha-ha !";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Un vrai putain de pirate ! Ah-ah-ha-ha !";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ouah-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Qui es-tu ? Que fais-tu ici ? Réponds vite !";
			link.l1 = "Je viens de Fadey, je suis venu pour un lot d'os noirs. Il aurait dû vous prévenir.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah ! Ne t'inquiète pas pour la peau, ami. Nous t'avons reconnu, Moscovit a donné une description très détaillée. Il a aussi demandé de ne pas être offensé par le prix. Donc, en tenant compte de l'avance déjà versée, cela fera 10 000 pièces d'argent pour toi. Ou, si tu paies en or, alors seulement 50 doublons. Eh bien, qu'as-tu décidé ? Ne tire pas la queue du chat !";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "Je paierai 50 doublons. C'est plus rentable.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "Je paierai 10 000 pesos.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Je suis désolé, mais je ne peux pas me permettre d'acheter des esclaves en ce moment.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "C'est formidable. Faites signe à vos hommes de prendre la marchandise.";
			link.l1 = "Certainement.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "C'est formidable. Faites signe à vos hommes de prendre les marchandises.";
			link.l1 = "Certainement.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Eh bien, comme tu veux. Il y aura toujours un acheteur pour ce produit. À bientôt, ami.";
			link.l1 = "Adieu.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Salutations, Capitaine. Vous êtes Charlie Prince si je ne m'abuse ? Ne vous inquiétez pas, mes murs n'ont pas d'oreilles. Honnêtement, je me fiche de votre nom. Ce qui compte, c'est que vous m'avez été recommandé, ce qui signifie que nous pouvons faire des affaires.";
			link.l1 = "Salutations à toi aussi, Gaspard 'Dentd'Or.' En fait, je me fiche de comment on t'appelle. J'ai entendu dire que tu pourrais être intéressé par l'achat de quelques breloques ?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "Exactement. Personne ne vous offrira un meilleur prix que moi. Eh bien, sauf peut-être les prêteurs sur gages, mais ils n'achètent pas grand-chose. Je suis prêt à acheter tout ce que vous proposez. Vous n'avez même pas besoin de m'apporter les objets de valeur personnellement : j'ai une porte dérobée menant à un quai isolé. N'hésitez pas à me vendre toutes les babioles que vous avez stockées dans les coffres de votre navire.";
			link.l1 = "Eh bien, c'est excellent ! Ravi de faire votre connaissance.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Maintenant, ça c'est mon affaire personnelle. Je préférerais que tu n'y mettes pas ton nez. Je dirai simplement que j'ai tout sous contrôle, donc tu peux commercer avec moi sans risque. Le reste ne te regarde pas.";
			link.l1 = "Eh bien, sans risque, c'est ce qui compte le plus ! Il y a autre chose que je voulais demander...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Comment puis-je vous aider? Vous voulez vous débarrasser de quelques perles ou gemmes en trop? Peut-être de l'or, de l'argent, des bijoux? Je vous achèterai tout.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Dis-moi, comment est-ce d'être un acheteur de biens volés ? N'as-tu pas peur des autorités ?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "J'ai quelque chose ici... Je veux l'échanger contre quelques pièces sonnantes et trébuchantes.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Eh bien, faisons l'échange. Doubloons ou pesos?";
			link.l1 = "Allons-y avec des pesos - pas besoin de doublons. L'argent courant est largement accepté partout.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "Tu l'as deviné - j'ai besoin spécifiquement de doublons. Donc je ne vendrai qu'en échange d'eux.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Je n'ai rien à vendre pour l'instant. Je voulais juste m'assurer que tu es prêt à acheter des objets précieux quand j'en aurai. À la prochaine !";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Es-tu toujours passé à l'intimidation, Capitaine ? J'ai entendu des menaces même de l'extérieur.";
			link.l1 = "Ils ne m'ont laissé aucun choix. J'ai offert des cadeaux à la femme de ce Tagofa pour son aide. Elle n'a même pas voulu m'écouter. Maintenant, que le chef leur parle. Et s'il échoue à ramener ces têtus à la raison, je lui arracherai le cœur de sa poitrine de mes propres mains. Et au fait, qui est Yahahu ?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "Tu n'aurais pas dû gâter les relations avec les Indiens. Nous, les pirates, n'avons pour alliés qu'une épée et un navire. Mais puisque c'est ta décision, qu'il en soit ainsi. Et Yahahu est un démon maléfique. Je ne sais rien d'autre sur lui.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Perdre du temps en persuasion, Leprechaun - c'est imprudent. Ou préférerais-tu renoncer au riche butin et maintenir de bonnes relations avec les Indiens ?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "Je préférerais obtenir les deux.";
			link.l1 = "Ça ne marchera pas d'avoir un pied dans chaque camp. Pas cette fois. Assez de disputes, tout est déjà fait. Demain, le chef nous informera de la décision de Tagofa, et j'espère qu'il ne me décevra pas. Sinon... je devrai prendre des mesures extrêmes. Ce que je voudrais éviter, bien sûr.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Eh bien, comment ça se passe ? Aurons-nous un guide ?";
			link.l1 = "Non, Jean, nous ne le ferons pas. Le chef et toute la tribu craignent les Kapongs comme le diable craint l'encens. Il semble que nous devrons abandonner notre plan.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax ne sera pas content de ce retournement de situation.";
			link.l1 = "Penses-tu que je suis incroyablement heureux que les choses se soient passées ainsi ? Les lâches Lokono ne veulent pas se mêler des Kapongs. Ils ne sont tentés ni par la persuasion ni par les récompenses.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "Alors, nous devrons recourir à des menaces. Dis-leur que tu réduiras leur fichu village en cendres et que tu tortureras ceux qui survivent jusqu'à ce que quelqu'un accepte de nous guider.";
			link.l1 = "Jean, as-tu complètement perdu la tête ? Je ne vais pas brûler les maisons d'innocents. Et certainement pas les torturer.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince est un modèle de bienfaiteur. Je n'aurais jamais attendu de telles poussées de tendresse de votre part.";
			link.l1 = "Ce n'est pas de la tendresse, Beau. Eh bien, nous torturerons un Indien à moitié mort. Par vengeance, il nous mènera directement entre les mains des Kapongs et il disparaîtra par des chemins connus de lui seul. Je ne risquerai pas la vie de mes hommes ainsi.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "Dans ce cas, Leprechaun et moi, nous partons. Voici cinquante mille pièces d'argent pour m'avoir libéré des plantations de Maracaibo. Je les gardais pour un nouveau navire. Et mon conseil pour toi : reste à l'écart de la vue de Marcus pendant un certain temps. Adieu, Charles Prince.";
			link.l1 = "Adieu, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Tout le monde du coin va se précipiter ici maintenant ! Es-tu sûr que faire sauter ces arbres était une bonne idée, Capitaine ?";
			link.l1 = "Merde ! Peut-être qu'il aurait été mieux que tout le monde travaille avec des haches... Mais il est trop tard pour cela maintenant.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "Vrai. Nous devrons faire avec ce que nous avons. Prépare-toi.";
			link.l1 = "Toi aussi, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Ils viennent toujours par ici. Alors, devrions-nous nous occuper de ceux-là aussi?";
			link.l1 = "Et s'ils étaient sans fin? Nous ne sommes pas ici pour ce genre de pétrin.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Eh bien, tout a une fin... Mais tu as raison. Retirons-nous. Et vite.";
			link.l1 = "Dépêchons-nous !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "Aussi implacables, ils nous ont rattrapés. Il y a un chemin ici, devrions-nous y aller ? Ce sera plus facile de tenir la ligne.";
			link.l1 = "Attends, Hercule. Entends-tu cela? Il y a déjà quelqu'un là-dedans. Toi et les gars, occupez-vous des choses ici. J'irai à l'intérieur, avant qu'ils ne prennent le trésor - je doute que quelqu'un soit tombé là par hasard.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "D'accord. Mais sois prudent, j'ai un mauvais pressentiment à ce sujet.";
			link.l1 = "Toi aussi! J'y vais.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Tu veux dire quelque chose, Capitaine ? Tu as été perdu dans tes pensées pendant toute notre marche jusqu'au navire.";
			link.l1 = "C'est vrai. J'ai réfléchi à ce que j'ai fait récemment. À propos de Terrax et... où cela m'a mené. Me suis-je rapproché de sauver mon frère ? Ou de rentrer chez moi ?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Bonnes questions. Et quelles sont vos réponses ?";
			link.l1 = "Juste une autre question. Si c'était futile avant, sera-t-il encore futile? Terrax ne m'aidera pas. Ni avec mon frère, ni avec Tortuga.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Probablement pas. Il n'en a pas l'utilité. Étonnant que vous ne l'ayez réalisé que maintenant. Mais quelle est votre prochaine question ?";
			link.l1 = "Pourquoi diable courais-je après Terrax comme un chien de poche, tirant les marrons du feu pour lui tout ce temps?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Eh bien, voilà une bonne question. Une question appropriée. As-tu une réponse cette fois-ci ?";
			link.l1 = "Plutôt une résolution. J'ai eu de la chance aujourd'hui. Mais aurai-je encore de la chance? Il est important de savoir quand s'arrêter. Et... de se respecter. J'en ai assez.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Avez-vous décidé de mettre fin à votre partenariat avec Terrax ?";
			link.l1 = "Oui. J'ai des choses plus importantes à faire. La famille, les amis. Avec eux, j'atteindrai mes objectifs. Et pas de cette manière. Et même si je le fais... ce ne sera pas avec Marcus. Je serai mon propre maître. Je prendrai mes propres décisions.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "L'homme que je suivais autrefois parle à nouveau. Ne te mêle pas encore avec les mauvaises personnes. Ne gâche pas le potentiel qui m'avait autrefois intrigué.";
			link.l1 = "Compris, Hercule. Et encore merci. Cette fois, pour m'avoir aidé à le réaliser pleinement. Je ne suis plus le Prince, un larbin. Je suis Charles de Maure, un noble fier. Embarquons sur le navire - nous sommes tous deux fatigués.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "C'etait un sacre coup, monsieur - un coup de canon a ma poupe! On aurait dit une bordee de la Valkyrie. Mais je crains que ces gaillards la-bas l'aient remarque aussi...";
			link.l1 = "S'ils l'ont remarqué, c'est leur problème. Personne ne les a invités ici. Prêt à leur donner une leçon, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Toujours prêt, monsieur !";
			link.l1 = "Excellent. Allons-y.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "J'ai bien peur que nous ayons bientôt de la compagnie supplémentaire, Capitaine. Quels sont vos ordres ?";
			link.l1 = "Nous nous enfoncerons plus profondément dans la jungle et nous cacherons - il n'y a aucun moyen de tous les repousser, et nous ne sommes pas là pour ça de toute façon.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Oui, monsieur.";
			link.l1 = "Alors, allons-y !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Ils nous ont retrouvés, Capitaine ! Mais nous pouvons nous abriter ici - on dirait que ce chemin mène quelque part, bien que je pense qu'il y ait déjà quelqu'un là-bas.";
			link.l1 = "Nous n'allons pas nous abriter ! On dirait que quelqu'un d'autre a eu vent du trésor. Voici le plan : je vais voir ce qui se passe avant qu'ils ne s'enfuient avec tout, et toi, tu les retiens ici avec les gars !";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Oui, monsieur.";
			link.l1 = "Excellent. Je descends maintenant ! Je te fais confiance pour gérer les choses ici.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Est-ce que vous allez bien, monsieur?";
			link.l1 = "Charlie ! Tu as choisi le moment parfait pour te soucier de moi. Garde tes mots. Tiens-tu le coup ? J'aurais dû te laisser sur le navire et prendre plus d'hommes à la place...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ah, juste une égratignure, monsieur. Un peu fatigué. Jamais combattu comme ça, même dans ma jeunesse! Mais je leur ai donné une telle raclée qu'ils entendront les knippels pour l'éternité!";
			link.l1 = "Marine Royale, vieille école ! On dirait que tu t'es battu comme un lion, Charlie. Mais tout de même, tu tiens à peine debout. Ne bluffe pas - à quel point est-ce que la blessure est grave ?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "Ce n'est rien de sérieux, Capitaine, juste de l'épuisement. L'entrée derrière vous s'est effondrée presque immédiatement, et nous avons dû repousser tous ces hommes pendant une éternité. À la fin, je me suis retrouvé seul, blessé. Alors, je suis venu ici pour dégager le chemin et recevoir les premiers soins.";
			link.l1 = "Je vois. Eh bien, tu as fait ta part aujourd'hui. Quant à moi... J'ai échoué. Nous avons tous été trompés et montés les uns contre les autres pour l'amusement de quelqu'un-il n'y avait même pas de trésor. Et je n'étais pas le seul imbécile là-bas.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Vous avez échoué?.. Mais vous êtes en vie, monsieur. Que s'est-il passé? Vous vous êtes échappé?";
			link.l1 = "Non, mais il y avait encore un peu de course impliquée. Désolé, vieux camarade, mais ce qui s'est passé là-dedans, je ne le dirai à personne - même pas à mes amis les plus proches. Cependant, j'ai tiré les conclusions nécessaires.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Quel genre de conclusions, monsieur ? Je ne comprends pas toujours votre raisonnement. Ma philosophie est simple - un bon couleuvrine et des grappes à la mâture.";
			link.l1 = "Dis-moi, tu as dû tuer des Espagnols auparavant, comme je l'ai fait récemment. À l'époque de tes jours dans la Marine Royale. Et plus tard, avec Fleetwood.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "Je l'ai fait. Espagnols, Hollandais-beaucoup d'autres aussi. Comme Dick me l'a dit une fois, notre service est dangereux et exigeant. Mais pourquoi demandes-tu cela? Quel est ton but?";
			link.l1 = "Je vais expliquer. Mais d'abord, une autre question. As-tu jamais douté de ce que tu faisais et pourquoi tu le faisais, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. Je me disais que j'agissais pour le bien de la Couronne. S'inquiéter des ordres est un boulot ingrat - il faut les suivre quand même.";
			link.l1 = "La Couronne... Eh bien, tu avais tes raisons. Je n'avais même pas ça - Michel m'a dit de m'approcher de Terrax. Mais cela valait-il tous les sacrifices ? Cela m'a-t-il aidé ou l'a-t-il aidé ? Oui, oui, nous n'aimons pas les dons... mais nous sommes tous humains.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Je crois que je commence à comprendre où vous voulez en venir, monsieur.";
			link.l1 = "Bien. Dis-moi, quand Fleetwood est parti, étais-tu content de ne plus avoir à tirer sur les marchands hollandais ? Certains d'entre eux étaient des gens honnêtes.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Je n'y ai jamais réfléchi, Capitaine. Mais je vais vous dire ceci - j'ai toujours pris plaisir à servir avec vous, monsieur. Que je sois damné avec une boule de mitraille autour du cou si je mens !";
			link.l1 = "Ha-ha-ha, d'accord. Mais dis-moi ça - qui penses-tu a eu le pire? Toi, en suivant les ordres ? Ou moi, qui n'était pas forcé de faire ce que j'ai fait ?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "Je ne sais pas, monsieur...";
			link.l1 = "Moi non plus. Mais ça n'a pas d'importance. Ce qui compte, c'est que je ne veux plus rien avoir à faire avec Terrax. Assez, c'est assez. Plus de Charlie Prince. Seulement Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "Mais cela ne faisait-il pas partie de votre plan pour sauver votre frère ?";
			link.l1 = "C'était. Mais au final, cela ne m'a servi à rien. Donc si je dois refaire quelque chose de ce genre - ce sera uniquement ma décision. Et seulement si cela me rapproche vraiment de mon but.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "J'espère que vous savez ce que vous faites, Capitaine. Et que vous ne finirez pas comme Terrax. Ou sur une potence.";
			link.l1 = "J'espère aussi. Mais ce dont je suis certain, c'est que mes objectifs et intérêts passeront en premier désormais. Maintenant, occupons-nous de tes blessures.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "Votre explosion a attiré l'attention, Seigneur Capitaine. Une escouade ennemie semble s'approcher de nous.";
			link.l1 = "Merde ! ...Tu penses qu'il y avait une meilleure façon de s'occuper de ces arbres ? Et qu'aurais-tu fait ?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "Je ne sais pas. Mais je sais ce qu'il faut faire maintenant - m'occuper de ces gens.";
			link.l1 = "Eh bien, soit. Je suppose que c’est exactement ce que nous ferons.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "De nouveaux venus arrivent, Seigneur Capitaine.";
			link.l1 = "Oui, j'ai remarqué, merci, Longway. Mais nous n'avons pas le temps pour ceux-là, alors retirons-nous dans la jungle - peut-être qu'ils nous perdront.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hmm, nous pourrions les gérer, bien sûr, mais comme tu dis.";
			link.l1 = "Nous n'avons pas besoin de ce combat, alors avançons.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "Ils ne nous lâcheront pas et finiront par nous attraper, Seigneur Capitaine ! Je vous l'avais dit, nous aurions dû les tuer plus tôt. Devons-nous tendre une embuscade dans cette grotte ? Bien qu'il semble que quelqu'un y soit déjà.";
			link.l1 = "Mieux vaut tendre une embuscade ici avec les gars ! Ce que je ne vais pas manquer, c'est ce trésor. On dirait que quelqu'un d'autre a eu vent du magot... Alors je vais aller vérifier moi-même.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Sois prudent, Seigneur Capitaine. Souviens-toi, même un grand dragon est mort un jour au sommet d'une montagne d'or.";
			link.l1 = "Je garderai cela à l'esprit, Longway. Essayons tous de ne pas mourir aujourd'hui.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Seigneur Capitaine, il semble que vous ayez réussi à vous échapper de là.";
			link.l1 = "Surpris, Longway ? Bien que je doive admettre que je suis moi-même quelque peu surpris. On dirait que tu es le seul à t'en être sorti vivant. Mais comment as-tu fait ?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Une bande de chats bagarreurs ne peut pas vaincre un tigre. Un nid de serpents ne peut pas abattre un dragon. Parmi les hommes blancs, peu sont des adversaires dignes des miens.";
			link.l1 = "Mais souviens-toi, Longway, une meute de chiens peut déchiqueter un lion.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Maintenant, le Seigneur Capitaine partage-t-il sa sagesse avec Longway ? Dommage que vous n'ayez pas écouté mon conseil plus tôt.";
			link.l1 = "À propos du dragon sur la montagne d'or ? C'est vrai, j'ai failli en devenir un - failli mourir, en fait. Mais pas sur une montagne d'or - il n'y en avait pas. Ce que j'ai trouvé à la place était autre chose, tout aussi important.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "La prochaine fois, 'presque' pourrait ne pas arriver. Qu'avez-vous trouvé, Seigneur Capitaine ?";
			link.l1 = "Oui, je le vois maintenant. Ce que j'ai trouvé était... sagesse. Expérience. Compréhension. Une décision. Dis-moi, Longway, qu'avons-nous fait dernièrement ?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Nous sommes des pirates. Travaillant pour ton nouveau maître, Lord Terrax. Contrebande, pillage de villes, tuerie, sauvetage et aide à son peuple.";
			link.l1 = "Ce n'est pas mon maître, tu sais. Mais bon sang, tu l'as décrit si parfaitement ! J'ai oublié la fierté, le respect de soi, et je l'ai suivi comme un petit chien.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway vous comprend, Seigneur Capitaine. Moi aussi, j'ai travaillé pour van Merden et Rodenburg, oubliant l'honneur, la fierté et le respect pour atteindre un but précieux.";
			link.l1 = "Dis-moi, te condamnes-tu pour cela ? Te détestes-tu ?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Condamner ? Parfois. Haïr ? Non. Je sais et je me souviens de qui je suis. Je me souviens de mon but, mon étoile guide. Rien n'est plus important dans la vie. Et vous, avez-vous un but ?";
			link.l1 = "Pas une étoile polaire comme toi, mais tout de même un objectif important, oui - sauver mon frère. Mais je me suis égaré de cet objectif. Et c'est quelque chose que je ne peux pas me permettre de répéter.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Laisse-moi partager avec toi un autre morceau de sagesse de l'Empire Céleste. Il n'y a pas de personnes entièrement bonnes ou mauvaises. Chaque personne possède à la fois le Yin - l'obscurité et l'ignorance - et le Yang - la lumière et la sagesse. L'équilibre change chez chacun.";
			link.l1 = "Alors, mon Yang est Charles de Maure. Et mon Yin est Charlie Prince. Bien que peut-être même Charles de Maure devra prendre des décisions sombres et difficiles un jour.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "C'est la vie, Seigneur Capitaine. Chaque personne est tenue de faire des choix sombres et lumineux.";
			link.l1 = "Pourtant, le masque de Prince a failli se fondre en moi. Mais je vais m'en débarrasser. Charles de Mort est un noble, pas un garçon de courses. Désormais, ce sera ainsi. Je revendique ma fierté et ma dignité. Dorénavant, je suis mon propre maître.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway approuve votre décision, Seigneur Capitaine.";
			link.l1 = "Merci, Longway. D'ailleurs, ne regrettes-tu pas de ne pas etre un capitaine libre? Me servir, comme tu dis, 'ton maitre'?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway regrette de ne pas commander son propre navire. Mais le mien reconnaît le vôtre. Pour avoir montré du respect et de la sagesse envers le mien, contrairement au barbare blanc typique. Peut-être que le mien aimerait une vie différente. Mais le mien ne regrette pas d'avoir aidé le vôtre.";
			link.l1 = "Je suis heureux de l'entendre, Longway. Maintenant... quittons cet endroit et le chemin du Yin. Et apportons plus de Yang dans nos vies. Ai-je bien compris ?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Oui, c'est exact. J'espère que tu suivras un bien meilleur chemin à partir de maintenant.";
			link.l1 = "Dao ?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "Le Chemin, Seigneur Capitaine. Ou l'Essence. Mais dans notre cas - le Chemin.";
			link.l1 = "Quel que soit le chemin que l'avenir me réserve, je ne m'écarterai plus de ce qui compte vraiment. Quittons cet endroit, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Capitaine Charles, beaucoup de gens viennent par ici. Votre signal de fumée les a attirés. Et ils ne sont clairement pas nos amis.";
			link.l1 = "Oh, si seulement c'était juste un 'signal de fumée', comme tu l'as appelé - cela a résonné à travers toute la jungle. Il n'y a pas le choix - défendons-nous. Nous n'avons certainement pas besoin d'une attaque par derrière par toute une escouade.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Oui, Capitaine Charles. Frappez le premier !";
			link.l1 = "Attaquez ! Ne ménagez pas les balles !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Encore d'autres arrivent ! Encore plus de monde.";
			link.l1 = "Retraite dans la jungle, Tichingitu ! Nous nous cacherons et attendrons. Je suis venu ici pour le trésor, pas pour un combat !";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Si besoin, nous pouvons tendre une embuscade dans la jungle.";
			link.l1 = "C'est bien vrai. Maintenant, avançons - rapidement, mais silencieusement.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Capitaine Charles, regarde ! Il y a un passage devant. Et j'entends des pas et des voix de là-bas.";
			link.l1 = "Quelqu'un d'autre a découvert le trésor ? Nom d'un chien ! Entends-tu ce bruit derrière nous aussi ? On dirait qu'ils nous ont rattrapés. Tichingitu ! Je vais voir ce qui nous attend devant. Retenez-les avec les gars !";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Nous essayons ! Toi, vas-y !";
			link.l1 = "Je compte sur toi !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Capitaine Charles ! Vous survivez ! Tichingitu sera content de cela.";
			link.l1 = "Merci, mon ami. Je suis heureux aussi. Je suis content d'avoir survécu, et que tu ailles bien. On dirait que tu es le seul survivant de toute l'escouade. Y en avait-il beaucoup? Tu les as vraiment bien retenus.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Beaucoup. Mais moi, je suis l'un des meilleurs guerriers de notre village Maskog. Que t'est-il arrivé là-bas ? As-tu trouvé le trésor que tu cherchais ?";
			link.l1 = "Non, Tichingitu. Nous avons été trompés - il n'y avait pas de trésor. Dis-moi, que penses-tu de ce que nous faisons tous ces derniers temps ?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "Qu'avons-nous fait, Capitaine Charles ? Naviguer. Battre vos ennemis.";
			link.l1 = "Il semble que tu ne me comprennes pas. Dis-moi alors, es-tu triste d'être exilé de ta tribu ? Veux-tu y retourner, tes frères te manquent-ils ?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Bien sûr, mes amis et ma famille me manquent. Mais rentrer ? Mon foyer n'existe plus sans... elle. Et puis, il y a ce satané coyote, le chaman !";
			link.l1 = "Je suis désolé, je ne voulais pas aborder cela. Vous savez, j'ai récemment rejoint une tribu, pour ainsi dire. Une tribu de capitaines comme moi. Mais à la fin, j'ai réalisé que ce n'était qu'une meute de chacals qui se croient des loups de mer...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "Et que se passe-t-il? Que faisons-nous maintenant?";
			link.l1 = "Bonne question. J'ai failli devenir moi-même un chacal avec ces chacals. Alors, ça suffit pour moi. Mes amis et mon équipage - c'est ma 'tribu'.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu est heureux que vous ayez trouvé votre tribu, Capitaine Charles.";
			link.l1 = "Merci, mon ami. J'avais besoin de dire cela. Toi et moi sommes nos propres chefs et tribu. Et maintenant, il est temps de revenir à des affaires vraiment importantes.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Quelqu'un arrive ! Et, à en juger par le bruit, ce n'est pas pour se joindre à nous dans la célébration de l'Action de grâce.";
			link.l1 = "Maudites racines ! Bon, nous allons devoir nous occuper de ces vauriens maintenant - mieux vaut maintenant que lorsque nous transporterons le trésor au navire.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Tu as bien raison. Prêt ?";
			link.l1 = "Tu n'avais pas besoin de demander. Ce n'est pas comme si nous avions le choix.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Ils sont partout, comme des rats dans les bas-fonds de Londres, Votre Honneur ! Quel est le plan - devrions-nous tenir notre position et échanger des coups de feu avec les gars ?";
			link.l1 = "Pas maintenant, reculez ! Nous sommes ici pour le trésor, pas pour nous battre !";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Héhé, pas d'objections ici.";
			link.l1 = "Alors, accélérez le pas !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Hé, Capitaine, regarde - on dirait que ce chemin mène quelque part. Et ça a l'air plutôt animé là-bas, à en juger par le bruit !";
			link.l1 = "Se pourrait-il que quelqu'un d'autre ait eu vent du trésor ? Tommy, entends-tu cela ? Ils nous ont rattrapés. D'accord, j'avance, et vous tous, donnez-leur un accueil digne de ce nom ici !";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Maintenant je l'entends ! Qui qu'ils soient, tu ferais mieux de te dépêcher, héhé. Sinon, à quoi bon avoir fait tout ce chemin jusqu'ici ?!";
			link.l1 = "Oh, je détesterais que ce soit le cas.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ah, c'est vous, capitaine ! Eh bien, vous avez survécu. Je ne vais pas mentir - je ne m'y attendais pas. Mais je suis content, ne vous méprenez pas, héhé.";
			link.l1 = "Je ne m'y attendais pas non plus, je ne vais pas mentir. Mais le fait que tu aies survécu – cela ne me surprend pas du tout. T'es-tu échappé ?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Vous me faites tort ! Tommy Irons ne s'enfuit jamais ! Il revient simplement avec des renforts. Mais ce n'était pas nécessaire – mes gars et moi, nous nous en sommes sortis seuls, bien que, encore une fois, je sois le seul à en être sorti vivant, héh...";
			link.l1 = "Peut-être que cette fois-ci tu aurais dû demander des renforts. Mais moi... j'ai pris la fuite.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Tu t'es enfui ? Heh, tu m'as encore surpris. Mais je voulais en fait me précipiter vers toi dès que j'avais terminé ! Je suis meilleur que n'importe quels renforts, tu sais. C'est juste que...";
			link.l1 = "Qu'est-ce qui ne va pas, Tom ?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Bon sang, pendant que je faisais l'idiot, l'entrée derrière toi a été bloquée par des rochers. Je n'ai pas pu passer. C'est même embarrassant d'avoir pris autant de temps à la dégager et de ne pas avoir pu t'aider là-bas. Je me suis un peu perdu tout seul en cherchant mon chemin pour ramener les gars et aider à déplacer les rochers... Quand je suis revenu, tu étais déjà rentré.";
			link.l1 = "Ouais, peut-être que j'aurai honte d'admettre ce qui m'est arrivé aujourd'hui.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "Et que s'est-il passé ? N'aie pas peur, dis-moi. Mais si c'est drôle, je vais rire, juste pour que tu saches. Sinon comment cela devrait-il être ? Un ami t'offre son épaule et te pousse du coude en riant.";
			link.l1 = "Eh bien, tu sais vraiment comment réconforter. Dis-moi, Tommy. Tu as dit que tu aimais la piraterie. Étais-tu content de t'y remettre avec moi ?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Je vais te dire ça comme ça. Que je sois un pirate ou non, ce que j'ai toujours foutrement aimé, c'est l'aventure ! Je vois que ma réponse ne te satisfait pas. Ces trucs-là, les grandes affaires, ce n'est pas mon truc.";
			link.l1 = "Ce n'est pas que cela ne me satisfait pas. Mais ce n'est pas ce que je voulais discuter. Tu sais... J'ai réalisé qu'avec Tiraqs, je me suis complètement écarté de mes objectifs. De plus... Charlie Prince était une sorte de larbin, pas un courageux capitaine pirate, tu comprends, Tom? Ça me suffit.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Je comprends. C'est pourquoi j'étais surpris que tu laisses Terrax te contrôler ainsi. Ça ne te ressemblait même pas.";
			link.l1 = "Peut-être que j'étais vraiment Charlie Prince à l'époque. Mais que nous retournions à la piraterie ou non, c'est moi qui déciderai ! Et seulement si cela sert vraiment mes intérêts et me rapproche de mon objectif !";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "Ah, ça c'est mieux ! Mais je veux dire, que ce soit Charlie Prince ou Charles de Maure - c'est toujours toi. Donc avec toi, c'était toujours sacrément intéressant !";
			link.l1 = "Ravi de l'entendre, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Souvien-toi, presque personne ne t'aidera sauf toi-même. Il vaut mieux faire ce que tu aimes, même seul, que de laisser les autres décider pour toi!";
			link.l1 = "C'est vrai. C'est exactement ce que j'ai ressenti avec Terrax. Même si je finis par suivre quelqu'un à nouveau, ce ne sera que sous des conditions dignes, pas comme un fichu garçon de courses !";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Tu as raison ! Maintenant, sortons d'ici - mes jambes sont déjà chancelantes.";
			link.l1 = "Eh bien, j'allais justement dire ça, ha-ha. Mais tu as raison, allons-y. Nous avons beaucoup de travail important devant nous, Tom. Pas de ce genre de trucs.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Capitaine, on dirait qu'on a de la compagnie ! Nous ne sommes pas seuls ici.";
			link.l1 = "Juste ce qu'il nous fallait... Très bien, occupons-nous d'eux maintenant. Plus tard, ils ne feront que causer plus de problèmes.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Ouais, Capitaine.";
			link.l1 = "Prépare-toi !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Ils sont de plus en plus nombreux !";
			link.l1 = "Alors il n'y a aucun intérêt à continuer cela ! Repliez-vous ! Nous les perdrons et nous irons directement au trésor !";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Oui, Capitaine !";
			link.l1 = "Avance, avance !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Capitaine, on dirait qu'il y a une entrée ici ! Et quelqu'un est déjà à l'intérieur.";
			link.l1 = "Ecoutez bien - nous sommes suivis. Je vais entrer et vérifier pendant que vous gardez cette position. Couvrez-moi, les gars !";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Oui, Capitaine !";
			link.l1 = "Tiens bon. Bonne chance à toi - à nous tous !";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu es "+GetSexPhrase("un voleur, je vois ! Gardes, saisissez-le","une voleuse, je vois ! Gardes, saisissez-la")+"!!!","Je n'en reviens pas ! J'ai détourné le regard une seconde - et tu plonges dans mes affaires ! Arrêtez le voleur !!!","Gardes ! Vol ! Arrêtez le voleur !!!");
			link.l1 = "Aaaah, diable !!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
