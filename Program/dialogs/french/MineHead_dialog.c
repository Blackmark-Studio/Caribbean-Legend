// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	location = &Locations[FindLocation(pchar.location)];
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Tu oses montrer ton visage ici ?! Je ne sais pas, si tu es courageux ou stupide...","Comment ces fainéants ont-ils laissé un ennemi s'introduire dans ma résidence ? C'est au-delà de ma compréhension...","Certainement, mes gardes ne valent pas un sou, si de tels salauds, se promènent ici..."),LinkRandPhrase("De quoi avez-vous besoin,"+GetSexPhrase("canaille","puant")+"?! Mes soldats sont déjà sur votre piste, "+GetSexPhrase(", pirate crasseux","")+"!","Sale meurtrier, quitte ma résidence immédiatement ! Gardes !","Je n'ai pas peur de toi, "+GetSexPhrase("rat","salope")+"! Bientôt tu seras pendu dans notre fort, et tu n'iras pas loin après ça..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Ces soldats ne valent pas un seul peso...","Ils ne m'auront jamais."),RandPhraseSimple("Ferme ta bouche, "+GetWorkTypeOfMan(npchar,"")+", ou je vais arracher cette langue pourrie de la tienne !","Je te suggérerais de t'asseoir tranquillement, et peut-être, tu t'en sortiras vivant..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Ennemi dans la mine ! Alarme !";
				link.l1 = "Aaah, diable !";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", monsieur. Je suis "+GetFullName(npchar)+", l'ingénieur des mines de la mine de Los-Teques. Qu'est-ce que vous avez besoin ici?","Bonjour, senor. Que vouliez-vous?","Hmm... vouliez-vous quelque chose de moi, senor? Je vous écoute.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Je suis nouveau ici, et je voudrais en savoir plus sur cette mine...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "J'ai une cargaison dans ma cale qui pourrait t'intéresser. Des esclaves pour ta mine, pour être précis. Envie de marchander ?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Je suis juste entre pour dire bonjour, et je pars deja.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "La mine de Los-Teques extrait l'or pour la Couronne espagnole. Tout ce que nous extrayons appartient à l'Espagne. Nous trouvons ici non seulement de l'or, mais aussi des pépites d'argent et des pierres précieuses de valeur. Nous ne vendons pas d'or ici, tout ce que nous extrayons est livré à l'Ancien Monde sous un convoi renforcé\nMais nous avons deux exceptions pour les pépites d'or et d'argent. Premièrement, vous pouvez acheter une certaine quantité d'entre elles dans notre magasin local auprès d'un quartier-maître. Parfois, le salaire n'arrive pas à temps, donc nous devons garder quelques économies de pièces ici pour de tels cas, c'est pourquoi le commerce local est autorisé\nDeuxièmement, nous ressentons constamment un besoin de main-d'œuvre, donc nous échangeons des pépites contre des esclaves. Par conséquent, parlez-moi si vous avez quelque chose à offrir, nous ferons des affaires\nJe crois que les règles de conduite de la mine sont évidentes : ne volez pas, ne distrayez pas les détenus et ne dérangez pas les soldats sinon vous n'aimerez pas les conséquences.";
			link.l1 = "Bien, merci !";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Bien sûr, monsieur ! Combien en avez-vous ?";
			link.l1 = "J'ai "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = int(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (int(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (int(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Seigneur, malheureusement, nous n'avons pas besoin de plus d'esclaves pour le moment. Mais la situation peut changer à tout moment, alors revenez dans quelques semaines ou à un autre moment.";
				link.l1 = "D'accord, monsieur, je comprends. Vous n'en avez pas besoin maintenant, mais vous pourriez en avoir besoin plus tard.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bien sûr, monsieur ! Combien en avez-vous ?";
				link.l1 = "J'ai "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Pour chaque esclave, je suis prêt à vous payer soit un lingot d'or, soit deux lingots d'argent. Que choisissez-vous?";
			link.l1 = "Lingots d'or.";
			link.l1.go = "slaves_g";
			link.l2 = "Lingots d'argent.";
			link.l2.go = "slaves_s";
			link.l3 = "Je suis désolé, monsieur, mais je viens de changer d'avis. Une autre fois.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "D'accord. Combien d'esclaves allez-vous me vendre?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "D'accord. Combien d'esclaves allez-vous me vendre?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = int(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Seigneur, je n'ai pas de temps pour des blagues stupides. Si vous êtes d'humeur à plaisanter, allez à la taverne!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Senor, je pense que vous avez besoin de vous reposer. Peut-être que vous êtes très fatigué ou que vous avez un coup de chaleur. Allez à la taverne, reposez-vous bien, puis nous pourrons poursuivre notre marchandage.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > int(location.quest.slaves.qty))
			{
				dialog.text = "Malheureusement, senor, nous n'avons pas besoin de tant d'esclaves pour le moment. La mine a actuellement besoin "+FindRussianQtyString(int(location.quest.slaves.qty))+". Allez-vous vendre autant?";
				link.l1 = "Oui, bien sûr!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... Je suppose que non.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Excellent. Veuillez ordonner de les amener aux portes de la ville. J'enverrai mes hommes pour eux.";
			link.l1 = "Ne vous inquiétez pas, senor. Vos esclaves vous seront livrés à temps. Je donnerai tous les ordres pertinents immédiatement.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = int(location.quest.slaves.qty);
			dialog.text = "Excellent. Veuillez ordonner de les amener aux portes de la ville. J'enverrai mes hommes pour les chercher.";
			link.l1 = "Ne vous inquiétez pas, monsieur. Vos esclaves vous seront livrés à temps. Je vais émettre toutes les commandes pertinentes immédiatement.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = int(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
