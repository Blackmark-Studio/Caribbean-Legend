// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Que veux-tu, garçon ? Parle à Requin, c'est lui qui commande ici.";
				link.l1 = "Puis-je au moins te dire bonjour ou est-ce contre les règles ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Shark m'a dit que tu as une carte de l'Île. La vends-tu ?";
					link.l2.go = "map";
				}
				dialog.text = "A-ah, "+GetFullName(pchar)+"Tu as affaire avec moi ou tu veux juste parler encore une fois ? Si c'est le cas, apporte une bouteille de rhum la prochaine fois, ha-ha !";
				link.l1 = "Non, je n'ai pas d'affaires particulières pour vous. J'apporterai du rhum la prochaine fois, juste pour vous.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha ! Tu es un plaisantin, n'est-ce pas, garçon ? Très bien... Je m'appelle Layton Dexter, je suis le second de Shark et de nos jours je suis son adjoint dans cette maudite Cité des Navires Abandonnés. En attendant, je vends des provisions et j'essaie de soutirer de l'argent à ce fainéant de Fazio.";
			link.l1 = "Et mon nom est "+GetFullName(pchar)+"Enchanté de vous rencontrer !";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Je suppose que tu as déjà entendu que Steven est mort. Les Narvals l'ont fait.";
			link.l1 = "Tu as raison, je le sais... Alors quoi, tu es l'amiral maintenant ?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Exactement. Chad a fait défection aux Narvals, Steven est mort et donc - étant le second en commande, naturellement, je suis maintenant l'amiral. Des objections?";
			link.l1 = "Non. Pas d'objections.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Bien. Écoutons vos questions.";
			link.l1 = "Allez-vous vous venger des Narvals pour la mort de Steven?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "Tu veux dire, vais-je leur déclarer la guerre ? Non. Il y a de meilleures façons de les faire payer. D'abord, je vais tripler le prix qu'ils paient pour les provisions\nS'ils attaquent le 'San Augustine', nous leur ferons voir de quel bois on se chauffe. Ensuite, je vais négocier avec les Rivados. Bien sûr, nous ne pouvons pas faire confiance à ces sales nègres et ils nous en veulent pour la mort de leur sorcier, mais tout problème peut être aplané avec du rhum et de la nourriture.";
			link.l1 = "Je vois. Bien, Layton, je dois y aller...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Attends. Steven m'a dit que tu essaies de quitter la Ville des Navires Abandonnés d'une manière ou d'une autre et de revenir ici sur un navire ?";
			link.l1 = "C'est le plan.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Prends ces instructions de navigation. Grâce à elles, tu pourras revenir ici par mer sans encombre. Cela signifie : tu n'échoueras pas sur les récifs, tu ne seras pas emporté par le courant, et ton navire ne s'écrasera pas sur les autres épaves à la périphérie extérieure\nSans elles, tu ne trouveras pas de passage ou ton navire rejoindra ses sœurs ici. Souviens-toi que tu dois utiliser un petit navire avec un faible tirant d'eau pour passer les hauts-fonds. Lougre, goélette, brigantin, brick... rien de plus grand qu'une quatrième classe. Compris ?";
			link.l1 = "Oui, c'est le cas. Merci ! C'est exactement ce dont j'ai besoin.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "N'oubliez pas de remplir votre cale de provisions. Je vous les vendrai à bon prix. Ne montrez ce document à personne, notre base doit rester secrète. Je vous donne ce document uniquement parce que Steven lui-même allait vous le remettre, et vous êtes un ami de Jan Svenson.";
			link.l1 = "Ne t'en fais pas pour ça. Merci encore et à bientôt !";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = " As-tu des progrès dans ta fuite de la Cité des Navires Abandonnés, "+pchar.name+"?";
			link.l1 = "Pas de progrès pour le moment, Layton. Je travaille dessus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Te voilà, "+pchar.name+"J'ai quelques choses à discuter avec vous.";
			link.l1 = "Autant que je l'ai compris, tu as pris la place de Steven après sa mort. Alors es-tu l'amiral maintenant ?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Exactement. Étant le second en commandement, je suis maintenant l'amiral. Des objections ?";
			link.l1 = "Aucune objection. Vous avez tout à fait le droit de garder cette position.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Je suis heureux que nous nous comprenions. Faites-moi savoir si vous avez besoin de quoi que ce soit.";
			link.l1 = "Vas-tu te venger des Narvals pour la mort de Steven ?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Vous voulez dire, si je vais leur déclarer la guerre alors ? Non. Il y a de meilleures façons de les faire payer. Je vais tripler le prix qu'ils paient pour les provisions.\nS'ils attaquent 'San Augustine', nous leur ferons voir de quel bois on se chauffe. De plus, nous avons de bonnes relations avec les Rivados maintenant, donc les Narvals ne risqueront rien en agissant bêtement.";
			link.l1 = "Je vois. Veux-tu me dire autre chose ? Ou puis-je partir maintenant ?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Je le fais. Je ne vois qu'une seule manière d'obtenir les Narvals. Ce n'est pas parfait, mais je ne vois pas d'alternative. Nous les attaquerons de deux directions. Un groupe de hardis coupe-jarrets sur des chaloupes abordera le 'Ceres Smithy', tandis qu'un second groupe avec les Rivados prendra d'assaut l'Esmeralda. Cela les éliminera complètement, ou les fera fuir vers le 'San Gabriel'. Le second scénario est le plus probable, San Gabriel est une position hautement fortifiée et l'assiéger prendra beaucoup de temps. Mais dans tous les cas, nous gagnerons.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "Nous attendons les résultats de votre conversation avec Donald Greenspen. C'est une affaire très importante, alors ne perdez pas de temps.";
			link.l1 = "Je suis en route !";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Oui, j'ai la carte. Voudrais-tu l'acheter ? Tu es le bienvenu, si c'est le cas. Elle sera à toi pour seulement deux cents doublons.";
			link.l1 = "Que dirais-tu des pesos ?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "Non. Je veux de l'or. Pas de marchandage.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "D'accord. Prends ton or, j'accepte.";
				link.l1.go = "map_2";
			}
			link.l2 = "Je n'ai pas tant d'or. Peut-être plus tard...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveItems(pchar, "gold_dublon", 200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Bon marché, garçon ! Prends ta carte. Elle vaut son prix - j'ai rampé dans la Ville pendant une semaine entière pour la dessiner, alors je te l'ai vendue à bon marché, en fait.";
			link.l1 = "Bon marché ?! Bien sûr. Eh bien, merci quand même.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Arrête là, camarade ! Oui, le Requin avait raison, ce type est devenu fou. Tant d'hommes sont morts à cause de lui... Enchaînez-le les gars et jetez-le dans la cale !";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steven m'a nommé amiral de la Cité à sa place - Je suppose que vous et lui retournez ensemble aux Caraïbes. Je resterai ici et continuerai les affaires, Steven et moi sommes réticents à perdre une base aussi formidable. Et je veux vous dire que vous serez toujours un invité bienvenu ici.";
			link.l1 = "Merci, Layton. Je pense que je reviendrai souvent sur ton Île.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "Ah, mon vieil ami "+GetFullName(pchar)+"! Tu as réussi à trouver la Ville des Navires Abandonnés en utilisant les instructions de navigation de Steven, n'est-ce pas ? Je suis très, très heureux de te voir. Tu es toujours un invité bienvenu ici.";
			link.l1 = "Merci, Layton. Je pense que je reviendrai souvent dans ta Ville.";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Très bien. Avez-vous de la nourriture à vendre ? Je suis prêt à vous l'acheter pour le double du tarif habituel.";
			if (iTrade > 0)
			{
				link.l1 = "Oui, je peux vous vendre des provisions.";
				link.l1.go = "trade";
			}
			link.l2 = "Malheureusement, je n'ai rien à vous vendre pour le moment.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Dommage. N'oublie pas de l'apporter la prochaine fois - je paierai bien.";
			link.l1 = "D'accord. Je vais essayer de ne pas l'oublier...";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Combien?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "Bon sang, t'es complètement ivre, l'ami ! Je suis impressionné ! Va dormir un peu, on échangera plus tard.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Je ne bougerai même pas mon cul de la chaise pour une somme si dérisoire. Apporte-moi plus !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "Et comment vas-tu naviguer sans aucune provision sur ton navire, camarade ? Veux-tu que tes gars meurent de faim ? Garde au moins "+FindRussianQtyString(GetCrewQuantity(pchar))+"pour vous-même.";
				link.l1 = "Hm, tu as raison.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Wow, l'ami, c'est trop pour nous ! Nous ne pourrons pas le manger avant qu'il ne pourrisse. Pour l'instant, je ne peux pas en prendre plus que "+iTemp+".";
			 link.l1 = "Quoi que tu dises.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Bonjour, mon ami."+FindRussianQtyString(iTemp)+" ? Très bien. Je vous paierai "+FindRussianMoneyString(iMoney)+". Marché ?";
			link.l1 = "Bien sûr ! C'est un plaisir de faire affaire avec vous !";
			link.l1.go = "trade_2";
			link.l2 = "Hm. Non, j'ai changé d'avis.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Marché conclu. Je vous paierai "+FindRussianMoneyString(iMoney)+" pour les marchandises. Est-ce suffisant ?";
			link.l1 = "Bien sûr ! Beau commerce !";
			link.l1.go = "trade_4";
			link.l2 = "Hm. Non, j'ai changé d'avis.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Que le diable m'emporte ! Mon entrepôt est plein ! Je n'aurai pas besoin d'acheter de provisions pour les six prochains mois.";
				link.l1 = "Bien. Alors je vous apporterai la prochaine cargaison de provisions dans six mois.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Super ! Apportez-m'en plus la prochaine fois.";
				link.l1 = "Bien sûr !";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Chouette ! Mon entrepôt est plein maintenant. Je n'aurai pas besoin d'acheter de victuailles pour le prochain semestre.";
				link.l1 = "Bien. Alors j'apporterai la prochaine cargaison de provisions dans six mois.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Super ! Apporte-m'en plus la prochaine fois.";
				link.l1 = "Bien sûr!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+" ! Heureux de te voir ! Que veux-tu ? ";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Veux-tu m'acheter des provisions ?";
				link.l1.go = "trade";
			}
			link.l2 = "Ce n'est rien, je voulais juste savoir comment vous alliez.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
