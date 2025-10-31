// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Parle, garçon, mais fais vite. Je suis un homme occupé.";
				link.l1 = "J'ai entendu dire que vous engagez des capitaines.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "As-tu des affaires pour moi ?";
			link.l1 = "Non, désolé. Je m'en vais.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Vous deviez être à mi-chemin de Sint Maarten à l'heure qu'il est, kapitein.";
				link.l1 = "Je me prépare à mettre les voiles, monsieur.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ah, capitaine, vous voilà ! Je ne vous ai pas vu arriver, je viens de finir de lire la lettre de Ridderbrock. Vous avez fait forte impression. Il vous appelle le 'gardien des marchands et le fléau des pirates. Un don de Dieu pour la Compagnie !' Que dites-vous de cela ?";
				link.l1 = "Je préférerais rester un simple capitaine. Un simple mais riche capitaine.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Pourquoi es-tu encore ici et pas en route pour Cuba ?!";
				link.l1 = "Oui, oui, je suis en route, monsieur.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, capitaine ! Je dois avouer que je commençais à m'inquiéter. Comment cela s'est-il passé ?";
				link.l1 = "Ce n'était pas sans difficultés, mais je vous en parlerai plus tard. Les affaires d'abord. Señor "+GetFullName(sld)+" m'a dit de te dire ceci : 'cet homme doit mourir'. Alors Geraldi considérera l'incident clos. Il a aussi dit que cette décision est la volonté de leur famille.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Content de te voir, kapitein ! C'est bien que tu sois venu me voir.";
				link.l1 = "Bonjour, monsieur. Je suppose que vous avez une autre mission de la Compagnie pour moi ?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Je vous ai dit d'amarrer votre navire. Êtes-vous trop stupide ou ignorant pour suivre des ordres directs ?";
					link.l1 = "Ni l'un ni l'autre, monsieur. Je suis en route.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alors, vous avez amarré votre navire. Maintenant, je vais vous prêter mon chebec. Êtes-vous prêt à commencer cette mission immédiatement ? Mon navire est bien équipé et prêt à naviguer, donc il n'y a plus rien à craindre pour vous.";
					link.l1 = "Oui, bien sûr. Je suis prêt, Monsieur Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Pourquoi es-tu encore ici ? Va voir Longway immédiatement.";
				link.l1 = "Désolé, je suis en route.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Capitaine... Je suis déjà au courant de votre voyage.";
					link.l1 = "Oh, vraiment ? Alors vous devez savoir que...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Capitaine... Je suis déjà au courant de votre voyage.";
					link.l1 = "Vraiment ? Alors vous devez savoir que...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Capitaine... Je suis déjà au courant de votre voyage.";
					link.l1 = "Vraiment ? Alors tu dois savoir que...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Vous voilà, Kapitein... Je sais déjà tout sur votre voyage.";
					link.l1 = "Vraiment ? Alors tu dois savoir que...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Va à Antigua. Maintenant.";
				link.l1 = "Désolé, je suis en chemin.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "J'ai été informé de votre arrivée, kapitein. Je sais aussi que vous avez perdu mon Mirage au combat.";
					link.l1 = "Vous êtes bien informé, Monsieur Rodenburg. Malgré tous mes efforts, nous n'avons pas pu la sauver.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "J'ai été informé de votre arrivée, kapitein. Je vois que le Mirage est amarré en toute sécurité. C'est bien.";
					link.l1 = "C'était selon vos instructions, monsieur. Vous m'avez ordonné de tuer Fleetwood et il est mort. Vous m'avez ordonné de ramener le Mirage au port local et elle est ici.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ah, vous voilà. Ravi de vous voir. J'ai une autre mission pour vous, comme promis.";
				link.l1 = "Je vous écoute, mynheer.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, je suis heureux de te voir, mon garçon. Tu étais en retard et j'ai commencé à m'inquiéter. As-tu pu obtenir quelque chose d'Abigail ?";
				link.l1 = "Non seulement cela, j'ai aussi résolu vos autres problèmes. J'ai trouvé l'île et la fortune perdue de Shneur. Solomon est heureux et Abigail acceptera votre proposition. Félicitations, mynheer !";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, je suis content de te voir, mon ami. As-tu pu obtenir quelque chose d'Abigail?";
				link.l1 = "Oui. J'ai eu une conversation avec Abigail et son père. Il y a un problème, monsieur: la fortune perdue de son père. Abigail se sent indigne de vous, elle craint les commérages et les murmures des gens si elle, en tant que fille sans dot, devait épouser un gentilhomme tel que vous. J'espère que vous comprenez.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, mon ami ! J'espère que vous m'apportez de bonnes nouvelles ?";
				link.l1 = "Ton plan a réussi. Abigail dira oui. Félicitations, mynheer.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Je t'attendais. Mon garçon, tu es en grand danger.";
				link.l1 = "Que veux-tu dire ?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Mes agents au quai m'ont dit que tu étais arrivé. Johan van Merden est-il mort ?";
				link.l1 = "Oui. Lui et son complice sont partis. Ce fut un combat difficile, mais je l'ai mené à bien.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Nous n'avons plus rien à discuter, kapitein.";
			link.l1 = "Compris, je pars.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Qu'est-ce que c'est ? Le temps, c'est de l'argent.";
		link.l1 = "Désolé, je m'en vais.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Peut-être. Qui es-tu ? Parle vite, le temps c'est de l'argent.";
			link.l1 = "Je suis capitaine "+pchar.name+", mon navire et  peuvent vous être utiles.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, un alliage inconnu à essayer dans le creuset.";
			link.l1 = "C'est pourquoi je suis ici, mynheer.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Très bien, nous verrons de quelle trempe vous êtes fait. D'accord Kapetein quel que soit votre nom, connaissez-vous Balthazar Ridderbrock ? Non ? Quelle chance. Des idiots aussi avides, grognons et colériques que lui sont des raretés.\nMais il semble que de telles qualités exceptionnelles ne suffisaient pas pour cet homme, alors il a eu la sagesse d'offenser un flibustier du nom de "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" dans la taverne locale et a appelé la garde au moment même où la partie offensée a touché une épée...";
			link.l1 = "...et ils ont pendu le pirate avec la première corde libre ?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "Ce n'est pas si simple. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+"n'est pas un pirate ordinaire, mais un corsaire néerlandais, un vétéran des deux dernières guerres contre les Anglais. Les contribuables locaux l'apprécient beaucoup. Je ne peux pas en dire autant de Ridderbrock.";
			link.l1 = "Alors notre corsaire est toujours en vie ?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Oui, mais il est vraiment en colère. C'est pourquoi Ridderbrock a une peur bleue.";
			link.l1 = "Je suppose que ma bonne fortune est sur le point de se terminer. Quand rencontrerai-je le sieur Ridderbrock ?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Imminemment. Les braves gens de Philipsburg attendent une cargaison de sucre, celle que notre connaissance commune Ridderbrock a promis de livrer. Je ne considère pas cet homme digne du cuir de ses bottes, mais hélas il travaille pour nous, alors allez au bureau du port. Trouvez Ridderbrock là-bas et dites-lui que je lui ai ordonné de mettre les voiles immédiatement.\nVous le suivrez, et... l'escorterez à Philipsburg en un seul morceau. Je ne veux pas "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" envoyer la réputation de la Compagnie par le fond des Caraïbes avec sa cargaison.";
			link.l1 = "Pouah, une mission d'escorte. Qu'en est-il du paiement pour cette...désagréable tâche ?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitein, fais d'abord le boulot. Balthazar te paiera dès qu'il atteindra sa destination. À Philipsburg ! Pas au fond de l'océan ! Ensuite, reviens me voir une fois le travail accompli. Si tu réussis, tu pourras compter sur mon soutien continu et celui de la Compagnie. Congédié.";
			link.l1 = "Au revoir, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Oui, Ridderbrock est un avare bâtard même pour un compatriote hollandais. Qu'importe, il ne me concerne plus. Parlons de vous, Kapitein Quelque Soit Votre Nom. J'aime votre style, alors je vais vous proposer un autre travail. Cette fois, je paierai moi-même.";
			link.l1 = "Je vous écoute, monsieur.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "J'ai besoin d'un homme pour une affaire très importante. Vous avez bien géré l'affaire Ridderbrock, donc la Compagnie croit que je peux vous la confier.";
			link.l1 = "Je suppose que c'est un honneur. Quel est le problème ?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Je ne peux pas vous donner de détails exacts, mais sachez que ce n'est pas mon travail, c'est celui de la Compagnie, donc vous avez une chance de gagner nos bonnes grâces, ce qui, je vous assure, est très profitable.\nNaviguez jusqu'à Santiago à Cuba et livrez ce paquet à Don "+GetFullName(sld)+". Il occupe une haute position dans la banque de Geraldi et il est aussi mon... notre partenaire d'affaires. Vous devez lui livrer cet or que je vais vous donner tout de suite. Je fais confiance à votre honnêteté, kapitein. Eh bien, sinon à votre honnêteté, alors à votre instinct de survie. La Compagnie retrouve toujours ceux qui tentent de nous voler.";
			link.l1 = "Doutez-vous de moi, monsieur ?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "Pour le moment, je ne doute pas de vous. Croyez-moi, je ne vous parlerais même pas de cette affaire si j'avais des doutes. Sachez que nous avons perdu beaucoup de temps à préparer ce travail, donc vous n'avez que quinze jours pour livrer."+sTemp+"\nMon message et mon paquet doivent être livrés à temps. C'est vital, garçon. Dépêche-toi, mais fais attention, ce ne sera pas une promenade de santé.";
			link.l1 = "Quelque chose d'autre ? Pourquoi m'avertissez-vous, monsieur Rodenburg ?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Disons simplement que j'ai mes soupçons. Ne t'inquiète pas, si tu fais cela aussi vite que le dernier boulot, alors tu auras une chance de devenir un agent précieux pour les affaires délicates de la Compagnie.";
			link.l1 = "Tout ce que j'ai à faire, c'est de livrer cette lettre et l'argent au banquier de Santiago en quinze jours ? Ça ne semble pas trop difficile en apparence.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Pas si vite, garçon... Je crois que tu ne saisis pas vraiment la gravité de cette situation. Réussir ce boulot me rendra très redevable envers toi. Par contre, échouer me rendra furieusement en colère. Dans ce cas, je te pisserai dessus. Nous nous comprenons, kapitein "+GetFullName(pchar)+"?";
			link.l1 = "Je prends note. Vous avez ma parole. Je ferai de mon mieux pour vous garder de bonne humeur.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Très bien. Maintenant, prends la lettre, ces coffres et souviens-toi des termes et conditions. Et une chose de plus : évite les ennuis à Santiago.";
			link.l1 = "Très bien.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Doit mourir'... juste comme ça. Je ne m'y attendais pas. Hum. Vous avez bien fait votre travail, kapitein. Maintenant, donnez-moi un compte-rendu.";
			link.l1 = "Rien de spécial... c'était une promenade de santé.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "J'ai été assommé et enlevé par un homme à Santiago. Il était très intéressé par vos affaires avec Geraldi. J'ai réussi à m'échapper mais j'ai dû le tuer d'abord. Le seul indice qu'il a laissé tomber était le nom d'un certain homme nommé Gaston, je n'ai aucune idée de ce dont il s'agissait.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "J'ai été assommé et enlevé par un homme à Santiago. Il était très intéressé par vos affaires avec Geraldi. J'ai réussi à m'échapper mais j'ai dû le tuer d'abord. Je n'ai pas pu lui soutirer d'informations avant de l'envoyer en enfer.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "La gratitude de la Compagnie ne se limite pas à de simples mots. Prends ta récompense, tu l'as bien méritée.";
			link.l1 = "Travailler pour la Compagnie est assez lucratif.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Quoi ! Un enlèvement... Attendez, cependant... Gaston ! Je comprends... je suppose. Hélas, mon garçon, tu as été entraîné dans une affaire sordide. Nous sommes en eaux inconnues, donc nous devrons voir comment cela évolue. Heureux que tu sois arrivé vivant.\nParlons de choses plus agréables - accepte cette récompense, elle est bien méritée.";
			link.l1 = "Travailler pour la Compagnie est assez lucratif";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "« Sornettes ! Vous enlever... J'ai quelques soupçons cependant. Vous en apprendrez davantage si vous continuez à travailler pour moi. Vous avez de la chance et je suis heureux que vous ayez réussi.\nParlons de choses plus agréables - acceptez cette récompense, elle est bien méritée. »";
			link.l1 = "Travailler pour la Compagnie est assez lucratif";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Exactement, mon garçon ! Tu peux devenir un agent bien payé de la Compagnie si nous continuons à travailler ensemble. Maintenant, vas-y, repose-toi de ton voyage. Tu as été à la hauteur de mes attentes. Je serais vraiment reconnaissant si tu revenais dans une semaine, nous avons encore beaucoup de travail à faire.";
			link.l1 = "Vous pouvez compter sur moi, Mynheer Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Vous êtes intelligent, capitaine. Exactement. Eh bien, parlons des détails de la mission à venir...";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "J'ai une mission très sérieuse et importante pour vous et j'attends de vous que vous fassiez tout selon mes instructions. Comme vous le savez, la relation entre les Provinces-Unies et l'Angleterre est... pas cordiale. Les Britanniques sont convaincus qu'ils sont ceux qui devraient gouverner le monde. Le problème est que tout le monde n'est pas d'accord avec une telle affirmation. Partout où ils naviguent pour faire des affaires, soyez assuré que la Compagnie néerlandaise des Indes occidentales y est arrivée en premier. Nous, les Néerlandais, avons la plus grande flotte commerciale du monde et nos escadrons militaires peuvent défendre les intérêts de la République ici et à l'étranger. Les Anglais nous envient pour notre pouvoir commercial et ils font ce qu'ils peuvent pour saboter les activités de la Compagnie. Maintenant, il y a un certain capitaine de la marine anglaise nommé Richard Fleetwood. Bien qu'il soit un officier commissionné du Commonwealth, il opère actuellement comme pirate. Il attaque et pille tout navire osant naviguer sous pavillon néerlandais dans les Caraïbes. Il explique ses actions comme des contre-mesures au 'navire fantôme' qui coule les marchands anglais. Il prétend que ce 'navire fantôme' est un corsaire naviguant sous une lettre de marque néerlandaise.\nAvez-vous entendu parler du 'navire fantôme', kapitein ?";
			link.l1 = "On peut entendre ce genre de balivernes dans n'importe quelle taverne. Il suffit d'acheter du rhum à un vieux maître d'équipage et vous entendrez toutes les histoires que vous voulez...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Ce n'est pas une chimère de soûlard. J'ai enquêté sur les agissements de ce 'vaisseau fantôme'. J'ai découvert qu'il s'agit d'un navire de bois et de toile, avec un équipage d'hommes ordinaires, une goélette nommée 'Mirage'. Elle est sous le commandement d'un homme nommé Jacob van Berg qui la fait passer pour le légendaire 'Hollandais Volant'.";
			link.l1 = "Van Berg ? C'est un nom néerlandais. Un véritable 'Hollandais volant', hein ?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Correct. Jacob van Berg est un Hollandais, originaire de Leyde. Mais la République l'a condamné à la potence il y a longtemps. C'est un criminel en fuite, un pirate qui n'agit que dans ses propres intérêts. Richard Fleetwood traque van Berg. Nous utiliserons ce fait contre cet Anglais insolent.\nJe préférerais ne pas tuer Fleetwood sur-le-champ, bien qu'il l'ait mérité depuis longtemps. La mort ne serait pas suffisante pour lui. Je veux non seulement le tuer, mais aussi détruire son nom et son honneur. C'est ce que je souhaite. Cela apprendra également une leçon aux autres porcs anglais arrogants.\nParlons des détails.";
			link.l1 = "Monsieur, cela commence à ressembler à une affaire personnelle...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Ce n'est pas ton problème. Tu suivras les ordres, puis tu seras payé. J'ai découvert où Jacob van Berg se cache avec son 'Mirage', grâce à mon agent. Il opère depuis une ville dans le sud de la Côte Espagnole. Va le voir et découvre où il a amarré son vaisseau fantôme.\nEnsuite, tue-le, trouve son 'Mirage', prends-la comme trophée, et ramène-la ici. Tu dois capturer le 'Mirage', ne pense même pas à la couler.";
			link.l1 = "Ça semble assez simple. Où devrais-je chercher van Berg ?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Tous les détails vous seront fournis par mon agent. Son nom est Longway, un Chinois. Je vous confie mon navire personnel, le chébec 'Meifeng' pour cette mission. Longway en est le capitaine, mais il prendra vos ordres.\nAllez au bureau du port local et amarrez tous vos vaisseaux là-bas. Revenez me voir une fois que c'est fait.";
			link.l1 = "Très bien, je rendrai visite au maître du port. Je ne te ferai pas attendre trop longtemps.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway vous attend dehors. Il vous montrera votre nouveau navire et vous donnera des informations concernant l'emplacement de van Berg. Bonne chance, kapitein, et ne me décevez pas. Souvenez-vous que vous devez me ramener le 'Meifeng', alors essayez de ne pas la couler en prenant le 'Mirage'.";
			link.l1 = "J'arrive !";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Espèce d'imbécile incompétent. Tu as échoué dans ta mission de capturer le navire pirate. Tous mes plans sont ruinés. Je te retire 'Meifeng'. Va-t'en, nous n'avons plus besoin de toi.";
			link.l1 = "Je suis désolé. Adieu, Monsieur Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Espèce d'idiot baveux. Tu as perdu le 'Meifeng'. C'est inacceptable... Je vais te prendre le 'Mirage' et retenir ton paiement en compensation de ma perte. Dégage, nous n'avons plus besoin de toi.";
			link.l1 = "Je suis désolé. Adieu, Monsieur Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Mon Dieu, vous êtes vraiment un spécimen rare. Un incompétent maladroit ET un idiot. Vous avez échoué à capturer le Mirage et perdu le Meifeng avec. Sortez de mon bureau, bordel !";
			link.l1 = "Je m'en vais.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Bien joué. La nouvelle de votre succès est déjà parvenue à mes oreilles. Van Berg est mort et vous avez capturé son navire. Votre paiement est de 50 000 pesos, prenez-le. \nJe récupère le 'Meifeng' de vous. Il est maintenant temps pour vous de prendre le commandement du 'Mirage', elle jouera un rôle important dans la prochaine étape. Êtes-vous prêt ?";
			link.l1 = "Oui, Monsieur Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Maintenant, nous nous occupons de Fleetwood. Tu vas l'attirer en utilisant le 'vaisseau fantôme' Mirage qu'il chasse avec tant d'enthousiasme. Installe un piège près de la Dominique, le Mirage servira d'appât.\nD'abord, tu feras savoir à Fleetwood que le Mirage a été aperçu non loin de la Dominique. Notre brave Anglais laissera tomber tout ce qu'il fait et se précipitera immédiatement à la Dominique à la recherche de sa proie. Ne parle pas directement à Fleetwood ou tu ne survivras pas à la rencontre. Trouve la pharmacie à St. John's. L'apothicaire John Murdock est un vieil ami à moi.\nDis-lui que tu agis sous mon commandement et il t'aidera à trouver des oreilles locales à remplir de mensonges croustillants sur le 'vaisseau fantôme' attaquant les marchands anglais autour de la Dominique.";
			link.l1 = "Je peux faire ça. Le but est de tendre une embuscade à Fleetwood à la Dominique, n'est-ce pas ?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Exactement. Longway et 'Meifeng' vous attendront près de la Dominique. Vous deux pouvez facilement vous occuper du chien anglais. Abordez son navire et fouillez sa cabine. Je veux son journal de bord. Je paierai un supplément pour cela.\nMais votre priorité principale est de tuer ce salaud de Fleetwood, donc si l'abordage est impraticable - envoyez-le par le fond. Avant tout, vous devez préserver 'Mirage' à tout prix. Elle a un rôle crucial à jouer dans la prochaine étape du plan.";
			link.l1 = "Compris.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Un conseil, kapitein. Ne jetez pas l'ancre à St. John's. Débarquez dans l'une des baies de l'île et marchez jusqu'à la ville à travers la jungle, sinon John ne vous parlera pas. Si vous attirez trop l'attention sur vous, il fera semblant de ne pas vous connaître. De plus, soyez prudent en mer - le 'Mirage' est tristement célèbre parmi les colonies anglaises, alors évitez leurs navires de guerre et leurs colonies si vous ne voulez pas être attaqué par une meute de loups de mer. C'est tout. Que Dieu soit avec vous.";
			link.l1 = "D'accord.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Vous êtes revenu, kapitein... Avez-vous le journal de bord de Richard Fleetwood ?";
				link.l1 = "Malheureusement non. Je n'ai pas eu l'occasion de monter à bord de son navire avant qu'il ne la saborde.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Vous êtes de retour, kapitein... Avez-vous le journal de bord de Richard Fleetwood ?";
				link.l1 = "Malheureusement, je n'ai pas réussi. J'ai réussi à aborder le Valkyrie et à tuer l'homme en combat rapproché, mais je n'ai pas trouvé son journal. Un de ses hommes a mis le feu à la soute et nous n'avions que quelques secondes pour nous échapper avec la vie sauve.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "Vous êtes revenu, kapitein... Avez-vous le journal de bord de Richard Fleetwood ?";
			link.l1 = "Je l'ai fait. La voilà. J'ai réussi à aborder le Valkyrie, bien que ce fut une affaire serrée. Le salaud a fait exploser sa soute et son navire a volé en éclats. Nous avons à peine échappé avec nos vies.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Quel dommage, cela aurait répondu à bien des questions que nous avions. Peu importe maintenant. Tu as tué ce chien anglais insolent et c'est ce qui compte le plus. Voici ta récompense - 100 000 pesos. Je te prends le 'Mirage', nous allons retourner ce navire en Angleterre.";
			link.l1 = "Que diable ?! C'est un beau navire, je voulais le garder !";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Excellent ! Vous êtes un homme très capable. Si tous nos capitaines étaient comme vous, la République néerlandaise serait la première parmi les plus grandes nations maritimes de l'histoire. Voici votre récompense - 100 000 pesos et 50 000 pesos supplémentaires pour le journal de bord. Je prends le 'Mirage' de vous, nous allons retourner ce navire en Angleterre.";
			link.l1 = "Que diable ?! C'est un bon navire, je voulais le garder !";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Mon garçon, tu es un excellent soldat, mais fais-moi confiance et écoute mon expérience en matière de politique. Souviens-toi de ce que j'ai dit à propos de Fleetwood ? Je vais clouer son nom et sa réputation à une meule et la jeter dans les profondeurs. Et ces nobles arrogants de Port Royal devront l'avaler et s'étouffer. Nous allons faire de Richard Fleetwood le capitaine du 'navire fantôme' Mirage, un loup-garou jouant les deux nations d'Angleterre et des Pays-Bas l'une contre l'autre, pillant, saccageant et assassinant les citoyens paisibles des deux juste pour s'enrichir ! Quelle parodie ! J'ai déjà préparé des preuves et des témoins, mais le 'Mirage' servira de pièce maîtresse à ma pièce parfaite.";
			link.l1 = "Eh bien, putain de moi alors. Tu vas sacrifier mon excellent navire pour ton plan !?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Surveille ta langue, garçon, c'est la guerre. Parfois, nous devons sacrifier non seulement des hommes, mais aussi des navires et des colonies riches pour atteindre nos objectifs politiques. Chaque guerre entraîne des pertes... En parlant de pertes, j'ai de mauvaises nouvelles pour toi.\nPendant ton absence, Willemstad a été attaquée par des corsaires anglais. Le fort a réussi à les chasser, mais pas avant qu'ils n'atteignent le port avec des brûlots.\nTon navire a été pris à l'ancre et brûlé jusqu'à la ligne de flottaison. C'est une perte totale.";
			link.l1 = "Mynheer, vous vous foutez de moi en ce moment. Nom de Dieu! Que vais-je faire maintenant ?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Ne vous fâchez pas, kapitein, j'ai aussi de bonnes nouvelles. Pour apaiser votre indignation, je vous offre mon Beau Vent, le chébec 'Meifeng'. Vous êtes libre d'utiliser le navire comme bon vous semble, dans les limites du raisonnable. De plus, retrouvez-moi demain à la résidence du gouverneur, vous avez été nommé pour une distinction d'État avec la gratitude de la République néerlandaise et de la Compagnie des Indes occidentales. Ne quittez pas la ville avant de l'avoir reçue, kapitein.";
			link.l1 = "Ca apaise un peu la douleur de mes pertes. Je suis honoré. Au fait, monsieur, où est passé Longway ?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway a soudainement disparu juste après que je lui ai ordonné de naviguer vers la Dominique. J'ai des soupçons que des agents anglais se sont mis à ses trousses... ou peut-être pas. J'enquête.";
			link.l1 = "Je vois. Son aide à la Dominique aurait été fort bienvenue. Fleetwood et sa 'Valkerie' formaient un duo redoutable. J'espère que Longway est toujours en vie... Tot zeins, mynheer !";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Tu n'es pas juste un clown ordinaire, tu es tout le cirque. Nous étions si près de l'acte final et tu l'as gâché... Je te paierai 30 000 pesos pour l'élimination de Fleetwood. Je n'ai plus de missions pour toi et notre arrangement est terminé. Va-t'en.";
			link.l1 = "Comme tu veux.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "J'ai de mauvaises nouvelles pour vous.\nPendant votre absence, Willemstad a été attaqué par des corsaires anglais. Le fort a réussi à les chasser, mais pas avant qu'ils n'entrent dans le port avec des brûlots.\nVotre navire a été pris au mouillage et brûlé jusqu'à la ligne de flottaison. C'est une perte totale.";
			link.l1 = "Je suppose que je vais juste aller me faire foutre alors ! Merci pour rien !";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Capitaine "+GetFullName(pchar)+" ! Pour avoir éliminé Richard Fleetwood, un dangereux criminel d'État, pour avoir exposé une conspiration anglaise traîtresse contre la République, pour votre bravoure et votre courage, vous êtes récompensé par mille doublons d'or au nom de la République des Pays-Bas !\nVous recevrez également cet outil de navigation précieux - le rêve de tout marin militaire.";
			link.l1 = "Je suis heureux de servir la République !";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Félicitations encore, mon ami. Et s'il vous plaît, rendez-moi visite dans une semaine. Nous avons besoin de vous pour une affaire extrêmement délicate.";
			link.l1 = "Compris, Monsieur Rodenburg. Je vous rendrai visite dans une semaine.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Laissez-moi vous raconter une histoire. Cela vous aidera à comprendre combien votre prochaine tâche est délicate. Il y a quelques mois, un fluyt battant pavillon anglais en route vers Willemstad a été attaqué par feu Jacob van Berg. Il a pris le navire et l'a sabordé non loin d'une île qui ne figure sur aucune de nos cartes. Seuls deux des passagers du fluyt ont survécu. Un Juif nommé Solomon Shneur et sa fille Abigail. Tous les autres passagers ont péri, y compris le reste de leur famille. Nos deux Juifs ont atteint l'île en flottant sur des débris\nSolomon a même réussi à traîner un coffre rempli de l'or de la famille avec eux. Très économe de sa part. Un autre personnage de notre histoire, Richard Fleetwood, naviguait à proximité et a entendu les bruits de combat. Il est arrivé trop tard pour attraper van Berg, et le 'Mirage' s'est enfui. Fleetwood a décidé de vérifier l'île pour voir s'il y avait des survivants\nIl a sauvé Solomon et Abigail d'une mort certaine sur cette île déserte. Malheureusement pour le vieux Juif, Solomon n'a pas l'œil d'un marin. Il a pris le 'Valkerie' de Richard pour le 'Mirage' de Jacob et - terrifié que le pirate revienne finir le travail - a caché son or quelque part sur l'île. En conséquence, lui et sa fille sont arrivés ici sans un sou, déposés par Fleetwood à la Lagune Blanca, près de Willemstad, leur destination originale.\nSolomon m'a raconté cette histoire. La République néerlandaise soutient la pratique libre de la religion. Dans le cadre de cette politique, la Compagnie soutient la communauté juive ici. Par conséquent, je me suis assuré qu'ils aient un toit sur leur tête, et de quoi manger et s'habiller. J'ai beaucoup visité leur maison. Abigail est une... jeune femme remarquable. Sincère et confiante\nJe ne vous mentirai pas, capitaine, je la veux et j'ai l'intention de faire d'elle ma femme. Elle m'aime en retour, mais quelque chose s'est mis entre nous.";
			link.l1 = "Son père n'est pas trop emballé par un gendre goyim ?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha ! Vieux Solomon serait au septième ciel si j'épousais Abigail, gendre incirconcis ou non. En fait, il la pousse à accepter ma proposition. Non, non, cela va au-delà des Juifs et des Gentils. Je te demande, mon garçon, de résoudre ce problème pour moi. Parle à Abigail et découvre ce qui ne va pas\nTu es un étranger, elle pourrait te dire des choses qu'elle ne dirait jamais aux gens familiers en raison de sa charmante modestie. La maison de Shneur est située à droite du bureau de la compagnie, si tu te places dos à celui-ci. Je sais que tu es un beau parleur\nMais souviens-toi d'une chose : Richard Fleetwood était le véritable capitaine du 'bateau fantôme'... Garde cela à l'esprit en parlant à Abigail.";
			link.l1 = "Ha! Bien sûr que je m'en souviens, Monsieur Rodenburg. N'est-ce pas le fait officiellement reconnu après tout ? Je ne perdrai pas de temps alors, je vais aller rendre visite à votre bien-aimée immédiatement.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "As-tu vraiment trouvé l'île où Salomon a caché son or ? C'est des plus excellents ! Je commençais à penser que tu es capable de réussir n'importe quelle tâche... As-tu trouvé autre chose dans la cachette ?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "Non, rien d'autre. Seulement de l'argent.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "Il y avait un objet intéressant - un crâne de jade. Je l'ai donné à Solomon, il a dit que c'était un héritage familial. Il a aussi dit que tu comptais l'acheter de lui...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Soit. Toutefois, c'est assez étrange. Qu'importe... Je vous dois une dette, monsieur, et je ne l'oublierai jamais. J'ai préparé une récompense pour vous - 50 000 pesos et cet amulette. Elle est à vous maintenant.";
			link.l1 = "Merci, Monsieur Rodenburg !";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Excellent ! Oui, je vais acheter cet artefact à Salomon, il n'en a pas besoin et j'ai un acheteur très généreux pour cela. J'ai préparé une récompense pour vous - 50 000 pesos et cet amulette. C'est à vous maintenant.";
			link.l1 = "Merci, Monsieur Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Je n'ai pas de travail digne d'un kapitein comme vous en ce moment. Mais ne quittez pas Curaçao trop longtemps, j'aurai bientôt besoin de vos services à nouveau.";
			link.l1 = "Je l'ai compris, monsieur. Adieu !";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, et c'est tout ? Ridiculement absurde...comme une femme. Écoute-moi, mon garçon, ce problème peut être facilement résolu. Je sais combien d'argent se trouvait dans la cachette de Salomon : 200 000 pesos. Je suis prêt à épargner cette somme pour mon bonheur et celui d'Abigail. Je te donnerai l'argent et tu quitteras Curaçao pour une semaine ou deux. Ensuite, tu retourneras voir Salomon et lui donneras l'argent. Fais semblant d'avoir trouvé la cachette. Le loup sera rassasié et la brebis intacte. Tiens, prends la somme requise.";
			link.l1 = "Un bon plan simple. Allons-y.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Partez en mer ouverte et revenez dans dix jours. Allez faire quelque chose de productif. Cherchez la Manga Rosa, fabriquez des matériaux, ou autre chose.";
			link.l1 = "Quoi que vous disiez, Mynheer Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Splendide ! Encore une fois, vous avez parfaitement fait le travail. Je vous dois, monsieur, et je ne l'oublierai jamais. J'ai préparé une récompense pour vous - 50 000 pesos et cet amulette. C'est à vous maintenant.";
			link.l1 = "Merci, Monsieur Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Oui, exactement ainsi. Mon ami, parfois il est difficile de voir qui est votre ami et qui est votre ennemi. Parfois, vous manquez le moment où votre plus proche associé se transforme en votre némésis. Notre connaissance mutuelle de St John's, John Murdock - également connu sous le nom de Johan van Merden - est un ex-agent de la Compagnie qui s'est vendu à la Marine anglaise.\nSa toute dernière mission est d'éliminer l'une des étoiles les plus brillantes de la Compagnie... vous.";
			link.l1 = "Je suis flatté. Heureux que tu me l'aies dit, sinon je ne l'aurais pas vu venir.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Précisément, kapitein. C'est un chien rusé. Trouvez ce salaud et tuez-le avant qu'il ne frappe. Naviguez vers Antigua et cherchez une entrée secrète dans sa pharmacie. Il y a une trappe devant l'église qui mène à un tunnel secret. Utilisez-la.";
			link.l1 = "Je m'en occuperai.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Encore une chose, kapitein. Une fois que Johan sera mort, fouille son cadavre, la maison et la cave. Il possède une archive - un gros registre où il notait des remarques compromettantes durant son travail pour la Compagnie. Cette information nous détruira tous si nos ennemis la trouvent.\nTrouve cette maudite archive et livre-la moi, je te paierai un supplément pour ça. Maintenant va. Bonne chance, Kapitein "+pchar.name+", et essayez de revenir en un seul morceau. La République a besoin de vous !";
			link.l1 = "Je vous promets, mynheer, de revenir en un seul morceau. C'est assurément dans mon meilleur intérêt !";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Excellent, capitaine ! Je suis ravi, vraiment. Avez-vous trouvé son archive ?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Oui, la voici. Il n'y avait pas d'autres documents sur le cadavre du chimiste ou dans ses coffres.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "Non. Je l'ai cherché partout mais n'ai rien trouvé.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "C'est bien dommage, mais cela me convient. Je suis sûr que Johan n'a pas eu le temps de le donner aux Anglais, sinon nous aurions déjà des cordes autour du cou... Il est probable qu'il l'ait caché dans une cachette secrète... qu'il y reste pour l'éternité ! Je vous félicite, kapitein, pour la conclusion réussie de notre mission !";
			link.l1 = "Gratitude !";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Splendide ! Maintenant, il est en lieu sûr où il doit être. Vous avez prouvé une fois de plus que vous êtes le meilleur... Donnez-moi le livre... Il y a une récompense pour l'archive - ce beau mousquet. Il m'a servi avec grande distinction et maintenant il est à vous !";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Quel est votre jeu, Capitaine ? Plusieurs pages manquent - des pages qui sont très importantes pour moi. Pensiez-vous que je ne m'en apercevrais pas pour que vous puissiez les utiliser contre moi ? Ou espériez-vous en tirer davantage ? Je crains de devoir vous décevoir sur les deux points.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = " (Digne de confiance) Je m'excuse. Ma seule faute était de ne pas avoir vérifié les archives moi-même au préalable.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Est-ce que j'arracherais vraiment les pages pour ensuite remettre les archives avec un air nonchalant ?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "La cupidité, la stupidité et l'insolence poussent parfois les gens aux actes les plus insensés, Capitaine.";
			link.l1 = "Aucun de ces trois-là ne m'a motivé, je vous assure.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Alors, vous dites que van Merden a retiré ces pages et les a cachées ailleurs ?";
			link.l1 = "Exactement. Je pourrais retourner et les chercher - mettre toute la pharmacie sens dessus dessous, voire tout Saint John - si vous jugez cela nécessaire.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Pas besoin, monsieur. L'essentiel est ici de toute façon, et sans les pages manquantes, le reste ne me pose aucune menace.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Alors, c'est plutôt un manque de soin ou de curiosité plutôt que de la malhonnêteté ou une intention secrète ? Penses-tu que c'était déjà ainsi quand tu l'as trouvé ?";
			link.l1 = "Très probablement, Monsieur Rodenburg. Peut-être que van Merden a arraché ces pages à l'avance.";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Peut-être est-ce pour le mieux. Sans ces pages, le reste de l'archive ne me pose aucune menace - surtout entre des mains ignorantes.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "Il y a une récompense pour l'archive - ce fin mousquet. Il m'a servi avec grande distinction et maintenant il est à vous !";
			link.l1 = "Merci!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Nous avons bien réussi, vous et moi, kapitein. Il n'est pas exagéré de dire que rien de tout cela ne serait arrivé sans vous. Vous atteindrez des sommets de carrière incroyables si vous continuez à servir la République, peut-être même serez-vous anobli.";
			link.l1 = "Je suppose que c'est un adieu, Monsieur Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "Adieu, "+pchar.name+"J'ai accompli tout ce que je voulais ici, donc je rentre chez moi à Amsterdam dans une semaine. Ma nouvelle épouse Abigail et mon beau-père Solomon m'accompagneront. Peter Stuyvesant a déjà trouvé un nouveau vice-directeur pour la Compagnie, alors parlez-lui si vous avez besoin de quelque chose\nPour votre service, je vous présente le Meifeng. Elle est à vous maintenant, kapitein, vous la méritez.";
			link.l1 = "Merci, Mynheer Rodenburg. Je me suis fortement attaché à la Meifeng et j'ai déjà commencé à la considérer comme la mienne.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "Et maintenant, je dois te demander de me laisser, mon garçon. J'ai beaucoup de choses à faire avant que nous ne prenions la mer... Viens me voir à Amsterdam un jour ! Nous partagerons un verre et nous rappellerons le bon vieux temps...";
			link.l1 = "Ouais, monsieur. J'espère que vous êtes tous heureux et prospères dans votre nouvelle vie ! Adieu !";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Oui, mynheer. J'espère que vous êtes tous heureux et prospères dans votre nouvelle vie !\n(par les dents serrées) ... J'espère que nous ne nous reverrons plus, espèce de crétin arrogant. Attendez de découvrir les joies d'être marié à une 'modeste' harpie juive.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Dieu dans les cieux ! Chien de Fleetwood ! Tu peux gagner aujourd'hui, mais Lucas Rodenburg vendra chèrement sa vie.";
			link.l1 = "Je ne pense pas. Tu me remettras ta vie gratuitement, espèce de radin hollandais.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Du fond de l'enfer, je chierai dans ta bouche ! Je viens de mettre le feu à la cale et l'incendie va bientôt se propager à la poudrière ! Nos navires sont accrochés de si près qu'il n'y a aucun espoir de fuite ! Tu brûleras ou tu nourriras les requins !";
			link.l1 = "Mordious ! Repliez-vous, hommes, nous devons battre en retraite !";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Je ne partirai pas avant que ton âme ne quitte ton corps. Ne bouge pas, ça va faire mal.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Pourquoi es-tu ici, espèce de salaud ? Es-tu venu te moquer de moi ? Peut-être vas-tu enfin me dire quel est ton rôle dans cette pièce. C'est toi qui as capturé la brigantine, n'est-ce pas ? Était-ce ton plan depuis le début ?";
			link.l1 = "Je suis ici pour te transmettre quelques salutations, Lucas Rodenburg. Les meilleures salutations de John Merdock, que tu as trahi. Tu étais mon travail et je l'ai accompli. Adieu pour l'instant.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan ? Haha ! Alors c'était lui l'auteur de tout cela ! Ce vieux scélérat ! Mais le jeu n'est pas encore fini. Jacob van Berg vient te chercher et tu ne t'échapperas pas ! Toi et ton navire êtes perdus, misérable mendiant des mers !";
			link.l1 = "Économise ta voix pour le tribunal du bourreau, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
