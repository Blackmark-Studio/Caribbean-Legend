// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Que puis-je faire pour vous, Monsieur? Je ne parle pas avec des gens que je ne connais pas. Si vous êtes venu pour bavarder ou demander quand le Train d'Argent Espagnol arrive à Maricaibo en 1640, alors je dois vous décevoir. Je ne perds pas mon temps avec des bavardages inutiles.";
					link.l1 = "Bon après-midi, Monsieur Fadey. Vous ne me connaissez peut-être pas encore, mais vous connaissez certainement mon frère. Permettez-moi de me présenter - Charles de Maure, frère de Michel de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, toi encore Charles ! Kak dela ? Que se passe-t-il cette fois ?";
					link.l1 = "Tu as dit que tu t'es fait voler... As-tu trouvé les coupables ?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Alors Charles, es-tu allé parler avec ce sauvage ?";
					link.l1 = "J'ai... C'est pourquoi je suis revenu vers toi.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ah, c'est encore toi, mon cher ami ! Alors, as-tu apporté la rançon de doublons pour l'Indien ?";
					if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
					{
						if (PCharDublonsTotal() >= 80) // belamour legendary edition
						{
							link.l1 = "Oui. Voici vos 80 doublons.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Non, je n'ai pas encore récolté assez.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 100) // belamour legendary edition
						{
							link.l1 = "Oui. Voici vos cent doublons.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Non, je n'ai pas encore collecté assez.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, eh bien c'est Monsieur de Maure en personne ! J'ai dit entrez, ne restez pas là ! Qu'est-ce qui vous amène à mon antre ?";
					link.l1 = TimeGreeting()+"Fadey, mon frère m'a dit de te voir. Il a dit que tu m'aiderais à trouver du travail.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, c'est toi ! Qu'est-ce qui t'amène ici, Monsieur de Maure ?";
					link.l1 = TimeGreeting()+", Fadey. Mon frère a insisté pour que je ne vous parle pas de cela, mais je n'ai pas pu m'en empêcher... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ah, vieil ami ! Entre, entre, "+pchar.name+" ! Comment vas-tu ?";
					link.l1 = TimeGreeting()+", Fadey. Content de te voir. En fait, j'ai un sujet important à discuter. Or noir.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ah, c'est encore toi, mon cher ami ! As-tu mis la main sur le butin ? As-tu trouvé assez de doublons ?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Da, Monsieur Fadey ! Voici votre or.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Non, je faisais juste un tour. Je cherche encore le bon montant.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, je viens d'avoir une idée. Je n'ai plus besoin des esclaves. Tu dois m'excuser, je te verrai plus tard !";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ah, mon vieil ami ! Entre, entre, "+pchar.name+" ! Comment allez-vous ?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", j'ai encore besoin de ton aide.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Heureux de te voir. J'ai affaire avec toi.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, c'est encore toi, mon cher ami ! Eh bien, as-tu trouvé l'argent ?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Je les ai, Monsieur Fadey ! Voici vos 300 doublons.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Je l'ai, Monsieur Fadey ! Voici vos 40 000 pesos.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Non, je fais juste une visite. Je cherche encore le montant adéquat.";
						link.l3.go = "exit";
					}
					link.l4 = "Excusez-moi, Fadey, mais je ne peux pas me le permettre. Je vais essayer de me débrouiller tout seul. À plus tard !";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Entrez, entrez, "+pchar.name+"Je vois dans tes yeux que tu veux entendre parler de mon succès.";
					link.l1 = "Exactement, Fadey. Je fais confiance que tu as ce que je veux.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, c'est encore vous, mon cher ami ! Alors, avez-vous trouvé l'argent ?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Prends 300 doublons. Je demanderai aux marins de transporter cette caisse jusqu'à mon navire. Oh, que ferais-je sans toi, Fadey ?! Tu n'as aucune idée de combien tu m'as aidé !";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Prenez 40 000 pesos. Je demanderai aux marins de porter cette caisse à mon navire. Oh, que ferais-je sans toi, Fadey?! Tu n'as aucune idée à quel point tu m'as aidé!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Non, je suis juste passé. J'essaie encore de réunir assez.";
						link.l3.go = "exit";
					}
					link.l4 = "Excusez-moi, Fadey, je suis complètement fauché. Gardez l'acompte, j'espère que cela suffira pour compenser vos frais avec cette affaire, et je vais essayer de me débrouiller seul. À bientôt !";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ah, Marque-Je veux dire "+pchar.name+"Allez, dis-moi ce que tu as pour moi !";
					link.l1 = TimeGreeting()+", Fadey. Ravi de te voir. Je suis venu te parler affaires.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"Je parie que vous êtes impatient de découvrir les résultats de ma conversation introspective avec le prêtre.";
					link.l1 = "Bien sûr que je le suis ! Comment cela s'est-il passé ?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ah pardonnez-moi, je suis tellement distrait par le tintement dans vos poches !";
					link.l1 = "Quelle avarice, Fadey ! Voici ton or.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Ah, mon vieil ami ! Entrez, entrez, "+pchar.name+"Alors, tu as du nouveau ?";
					link.l1 = "Bonjour, Fadey. Je te demande encore une fois ton soutien.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Qu'est-ce que tu es ? Une statue ? Si tu as quelque chose à dire, crache le morceau, sinon, dégage, "+pchar.name+" !";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Regarde, Fadey. Je suppose que c'est un shamshir persan, peut-être l'un de ceux volés de ta collection ?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "J'ai de bonnes nouvelles pour toi. J'ai ici un autre shamshir persan pour toi.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "J'ai un troisième shamshir persan. Comme tu l'avais demandé, je l'ai rapporté dès que j'ai pu.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Je suis ici au sujet de l'armure légère dont nous avons discuté.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, j'aimerais acheter un peu de ta corde célèbre.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, j'ai besoin de ton aide.";
				link.l1.go = "help";
 				link.l9 = "Non, rien pour le moment.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Que puis-je faire pour vous, Monsieur ? Je ne parle pas aux gens que je ne connais pas.";
				link.l1 = "Oh, je suis juste passé voir qui habite ici.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ah, alors vous êtes le petit frère du bon vieux Michel ! Cela change la situation ! Entrez, entrez, Monsieur, asseyez-vous. Voudriez-vous lever un verre de vodka pour célébrer notre rencontre ? Il me reste encore quelques bouteilles et ce serait un plaisir d'en partager une avec le frère d'un bon ami, da !";
			link.l1 = "Veuillez me pardonner, Monsieur Fadey, mais boire n'est pas au programme ce soir. Je préférerais aller droit au but.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Qu'est-ce que vous dites ! Ce rhum local est une eau-de-vie faible comparée à la vodka russe ! Vous ne savez pas ce que vous manquez, que la Mer me prenne si je mens ! Bon, passons aux affaires alors. Je suis tout ouïe, Charles.";
			link.l1 = "Monsieur, je soupçonne que ce que je m'apprête à vous dire sera fort désagréable, mais hélas, je suis contraint par le devoir de vous le dire ! Michel m'a confié que vous lui devez une belle somme d'argent suite à des jeux de hasard avec lui. Il m'a également ordonné de récupérer cet argent pour lui, car mon frère est... dans l'incapacité de venir vous voir en personne pour le moment.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Oh, jeune homme ! Bien sûr, je me souviens de tout et j'admets que je dois à votre frère. Une dette de jeu est sacrée, honorer ce devoir est la seule chose qui nous sauve de l'anarchie mortelle et des bandits dangereux ! Mais je vous en prie, comprenez ma situation ! Une histoire désagréable m'est arrivée récemment - j'ai été volé de la manière la plus impertinente !\nDes voleurs maudits ont pris tout ce qu'ils pouvaient, tout ce que j'avais gagné en années de labeur, mon argent et ma collection inestimable ! Je ne peux tout simplement pas rembourser une dette maintenant, niet.\nMais, Monsieur de Maure, je n'abandonne pas mes obligations ! Je vous demande seulement de me rencontrer à mi-chemin. Puisque je n'ai aucune pièce en ma possession maintenant de toute façon, je vous offre ce rare poignard excellent. Regardez !\nC'est un véritable chef-d'œuvre d'acier, la fierté de ma collection volée. En outre, il a été enchanté par des chamans indiens et possède de puissants pouvoirs cachés ! Les Indiens l'appelaient la Griffe du Chef.\nJe n'aurais jamais accepté de le donner parce que j'ai payé une grande somme pour le poignard, bien plus que ma dette, mais compte tenu des circonstances et de ma relation avec votre grand frère, je suis prêt à vous le donner. Beri, c'est une très bonne affaire !";
			link.l1 = "Je préférerais vraiment l'argent plutôt qu'un couteau...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Mais je n'ai pas l'argent et j'ai cet artefact rare et enchanté ! Crois-tu vraiment, mon vieux, que je t'offrirais ce magnifique poignard magique au lieu de quelques misérables pièces d'argent dans d'autres circonstances ? Tu peux trouver des pesos partout, même traînant dans la rue ! Tu dois admettre que je suis dans une situation délicate ici. Mon cœur saigne rien qu'à penser à me séparer de cette pièce d'artisanat incroyable, mais une dette de jeu est une dette d'honneur, donc je suis prêt à te le donner uniquement à toi, bien qu'il me soit très cher, parce que tu es un véritable homme d'honneur et un véritable ami.";
			link.l1 = "D'accord, puisque tu jures que tu n'as pas d'argent, je vais prendre ce poignard magique à toi. J'espère pouvoir le vendre à bon prix...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "«Vendre ça»!? Sors d'ici, espèce de stupide-Je veux dire Charles! Nyet, je peux à peine croire mes oreilles! Je donne mon bien le plus précieux pour lequel j'obtiendrais au moins dix fois plus en Europe, et tu restes là, effrontément à dire que tu vas juste aller le mettre en gage!? Pourquoi ce poignard, jeune homme, a sauvé la vie d'un homme! Laisse-moi te raconter-";
			link.l1 = "Et quel est ce pouvoir caché dont vous avez parlé ?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, ho ho ! Maintenant Charles, je suis un bon chrétien, tu sais, pas un chaman indien. Je n'ai aucun moyen de connaître toutes les propriétés cachées de cette lame. Mais elles existent, oh ça oui ! Tiens ce poignard dans ta main et tu ressentiras toi-même la puissance qu'il renferme ! Prends-le, beri ! Alors, qu'en dis-tu ? Ressens-tu quelque chose ?";
			link.l1 = "Hm... Je ne ressens rien. Bien qu'il s'ajuste confortablement à ma main.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ha ! Voilà ! Mais ce n'est là que la moindre de ses qualités. Si tu manies ce poignard au combat, je suis sûr qu'il montrera sa puissance de bien des manières dramatiques ! Eh bien, alors, le prends-tu ?";
			link.l1 = "Eh bien, ai-je le choix ? Je le prendrai puisque tu n'as pas de pièces...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Merci, Charles. Tu ne le regretteras pas, oh certainement pas ! Voilà. Et n'oublie pas de dire bonjour à Michel de ma part ! Dis-lui de passer de temps en temps, dès qu'il en a l'occasion.";
			link.l1 = "Oh je lui dirai...";
			link.l1.go = "exit";
			link.l2 = "Vous avez dit que vous aviez été volé... Avez-vous trouvé les coupables ?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "Le problème, c'est que je ne l'ai pas fait. Ces vauriens ont vidé toute la maison, s'enfuyant avec tout l'argent, l'or, mes économies de longues années de dur labeur. Maintenant, cela ne me dérange généralement pas, après tout, un vrai gentleman, même s'il perd tout ce qu'il possède, ne doit montrer aucune émotion ! L'argent doit être si loin sous un gentleman qu'il ne vaut guère la peine de s'en soucier. Mais le pire, c'est qu'ils ont raflé ma magnifique collection de shamshirs persans ! Il n'y a pas une collection comme celle-ci dans tout le Nouveau ou l'Ancien Monde réunis. De véritables épées de cavalerie persanes remarquables...";
			link.l1 = "Des épées persanes, dites-vous ? Cela semble assez intéressant. Alors, vous êtes collectionneur, n'est-ce pas ?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Eh bien, j'aime collectionner des choses rares... Ecoute, Charles, peut-être pourrais-tu m'aider dans cette affaire...";
			link.l1 = "Aider ? Mais comment ? Vous voulez dire en attrapant les voleurs ?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Non. Je ne suis pas particulièrement intéressé par les voleurs. Je voudrais récupérer mes sabres de cavalerie persans. Si vous les trouvez, je vous assure que cela en vaudra la peine, je vous le promets.";
			link.l1 = "Hm. Mais où devrais-je même les chercher ? Autour des Caraïbes ? Ou peut-être partout dans le monde ?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Eh bien, peut-être que vous les apercevrez sur les îles chez certains marchands de rue, ces vauriens ne peuvent même pas comprendre la valeur de ces épées de cavalerie et ils les vendront sûrement pour des miettes. Donc, si vous voyez les épées persanes quelque part, apportez-les-moi. Serez-vous capable de les reconnaître ?";
			link.l1 = "Je pense que oui. D'accord, je garderai les yeux ouverts et si je vois des lames inhabituelles correspondant à la description, je te les apporterai sans faute.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Vous savez, je ne suis pas un expert en armes fines. J'ai bien peur de ne pas pouvoir vous aider. Ce serait donc malhonnête de ma part de vous donner de faux espoirs.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Horosho ! J'espère que tu auras de la chance et que tu trouveras ces artefacts, et je te récompenserai comme il se doit. Bonne chasse, traqueur- je veux dire capitaine ! Da, Charles, peux-tu imaginer, j'ai subi une autre tentative de vol récemment !\nUn voleur a essayé de s'introduire chez moi il y a seulement quelques jours\nC'était vraiment trop pour moi ! Cette fois-ci, il n'a pas échappé, je l'ai attrapé, lui ai donné une bonne raclée, et l'ai remis aux gardes de la prison en ville. J'espère qu'ils le pendront bientôt !";
			link.l1 = "Penses-tu qu'il est l'un des voleurs qui ont fauché tes shamshirs ?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Quel dommage, mais il ne sert à rien de pleurer après la lune. Da, Charles, peux-tu imaginer, j'ai récemment subi une autre tentative de vol !\nUn voleur a essayé de s'introduire chez moi il y a quelques jours à peine\nC'était vraiment trop pour moi ! Il ne m'a pas échappé cependant : j'ai réussi à l'attraper, je lui ai donné une bonne raclée, et je l'ai envoyé à la prison locale. On ne peut pas être heureux aux dépens du malheur des autres. J'espère qu'ils le pendre bientôt !";
			link.l1 = "Tu penses qu'il fait partie des voleurs qui ont piqué tes shamshirs ?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Nyet, je ne pense pas. Il était après l'argent. Je l'ai attrapé dans ma chambre, fouillant dans mes coffres\nUn Indien de quelque jungle profonde sur le Main espagnol. Il a l'air ridicule, différent de ceux d'ici. Tout couvert de peinture de guerre et vêtu d'un costume coloré... Tu devrais visiter le cachot et voir ce bouffon par toi-même si tu veux, tant qu'il est encore vivant.";
			link.l1 = "Hm... Peut-être que je passerai le voir.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Allez-y, jetez un coup d'œil au spectacle de monstres... Horosho, Charles, c'était une conversation agréable. Bon voyage de retour en Martinique, poputniy veter !";
			link.l1 = "Tous mes voeux, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Comme c'est intéressant ! Je vous écoute.";
			link.l1 = "Fadey, j'ai parlé avec cet Indien. Et je suis venu te voir pour demander de l'aide pour le sortir de là. Le pauvre bougre voulait juste quelque chose à manger...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, et tu as cru à cette histoire ? Les jeunes hommes de nos jours sont si crédules...";
			link.l1 = "Fadey, je suis peut-être plus jeune que toi, mais même moi, je peux discerner quand on me dit la vérité et quand on me ment. En plus, penses-tu vraiment qu'une pendaison est une punition appropriée pour ce genre de crime ? Cela semble excessif. Chez nous, tu recevrais juste quelques coups de fouet ou une marque au fer rouge pour un récidiviste.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Excessif!? Il est entré par effraction dans ma maison ! Ce sauvage n'aurait jamais dû venir ici ! Que feriez-vous si vous étiez à ma place ? Je suis sûr que vous transformeriez ses entrailles en extérieurs et le feriez nourriture pour les vers, hein ?!";
			link.l1 = "Non, je ne le ferais pas, Fadey, tu es toujours en colère à cause de ta collection de shamshirs volée. Si cela n'était pas arrivé, tu serais plus enclin à donner une bonne raclée à ce stupide peau-rouge et un coup de botte au cul, ai-je tort ?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles...Tu es comme ton frère... Horosho. Réglons cela comme des hommes d'affaires honnêtes. Puisque tu veux cet Indien à ce point, indemnise-moi pour le préjudice moral et les dégâts matériels qu'il a causés et je dirai au commandant que je ne souhaite pas porter plainte. Qu'en dis-tu ?";
			link.l1 = "Combien ?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, tu commences déjà à apprendre les coutumes des Caraïbes, Charles. Cent cinquante doublons d'or, pas un kopek de moins.";
			link.l1 = "Fadey, que Dieu ait pitié...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Bien, bien. Cent doublons d'or. Mais c'est mon offre finale. Et nous parlons de doublons, pas de pesos. Notre banquier sera sûrement capable de trouver cette somme à échanger.";
			if(PCharDublonsTotal() >= 100) // belamour legendary edition
			{
				link.l1 = "J'ai la somme dont tu as besoin maintenant. Tiens, voici tes cent doublons.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "Fadey, écoute... Je comprends ta frustration, mais je suis le seul prêt à te dédommager en vrai argent pour cet inconvénient.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "D'accord, je vais chercher ce dont tu as besoin.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Tu as un avenir ici, mon ami, je peux te le dire. Bien! Quatre-vingts pièces d'or - et pas une de moins!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "Et dépêche-toi, Charles ! Tu n'as que dix jours avant qu'il ne soit exécuté.";
			link.l1 = "Je garderai cela à l'esprit. Adieu !";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(pchar,"questTemp.Sharlie.Tichingitu80"))
			{
				RemoveDublonsFromPCharTotal(80);
				DeleteAttribute(pchar,"questTemp.Sharlie.Tichingitu80");
			}
			else RemoveDublonsFromPCharTotal(100); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Très bien. Je vais rédiger un mot tout de suite et y apposer mon sceau, attends une seconde... voilà. Remets ceci au commandant et tu pourras emmener ton Indien avec toi. Pas sûr de comprendre pourquoi tu t'inquiètes tant pour lui, mais c'est ton problème. Que vas-tu faire, l'exposer lors d'un bal masqué? Haha, quelle idée!";
			link.l1 = "Dieu voit tout, Fadey. Sauver la vie d'un homme est une noble action.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je suis d'accord avec ta première affirmation, mais la seconde est discutable, Charles. Et si tu sauvais un tueur ou un violeur de la justice qui l'attend au bout d'une corde ? Bah, peu importe, ce n'est plus mon problème. Que Dieu soit avec toi. Va voir le commandant avant que ton ami à la peau rouge ne devienne pâle d'une corde autour du cou...";
			link.l1 = "Je suis en route. À plus tard, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Tu as l'air sombre, mon ami ! Je suppose que tu es sur le point de m'apporter de mauvaises nouvelles ?";
			link.l1 = "C'est tout ce qu'il y a à dire, aye. Je vais être franc avec toi, Fadey : Michel a dit que tu m'as roulé avec cette merde de 'griffe du Chef'. Il a dit que ce n'est pas un artefact, et que je pourrais l'acheter à n'importe quel marchand de rue pour quelques centaines de pesos. J'ai demandé autour des vendeurs de rue qui traitent des articles en métal. Ils m'ont donné exactement ce prix.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Oh, Monsieur de Maure... Je suis blessé ! Je suis surpris par votre frère. Ces marchands idiots dans la rue peuvent dire ce qu'ils veulent, mais lui ! Dites-moi, Charles, si quelqu'un vous apportait une vieille épée de chevalier à deux mains des jours de Charlemagne et vous proposait de vous la vendre, que donneriez-vous pour cela ?";
			link.l1 = "Une espadon ? Tu te fous de ma gueule, Fadey ? À quoi me servirait une vieille lame de bourreau rouillée ? C'est le dix-septième siècle de Notre Seigneur Jésus-Christ ! Je ne donnerais pas un seul peso pour ça !";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ah, vois maintenant ta myopie, mon ami ! Tu n'y arriveras jamais avec cette attitude. Et si tu m'apportais un tel artefact, je paierais trois cents doublons pour cela. Demande pourquoi ? Parce que c'est une antiquité, un trésor historique difficile à trouver de nos jours ! Tu ne comprends pas, et pourtant tu juges ! \nAvec Dieu et Sa Sainte Mère comme témoins, la griffe du Chef est un poignard de maître, mes sources me disent que Cortez lui-même le possédait. LE Hernan Cortez ! Le légendaire conquistador qui a pillé Tenochtitlan et capturé l'empereur des Aztèques ! Et tu te moques et dis que c'est une pacotille commune !\nDe plus, je t'ai déjà dit que ce n'est pas n'importe quel poignard, c'est un poignard enchanté ! Es-tu encore si naïf que tu n'as pas vu toutes les merveilles des Caraïbes ? Sortilèges et magie, rituels et malédictions ? Charles, c'est le Nouveau Monde, la patrie des Mayas et des Aztèques dont la connaissance de ces arts diaboliques atteignait des sommets inconcevables pour nous, chrétiens !\nCe poignard a des pouvoirs cachés. Hélas, personne ne sait encore quel genre de pouvoirs. Tu as une chance unique et incroyable de découvrir par toi-même de quoi il est capable et pourtant tu continues de prétendre que c'est une 'merde' et que ton pauvre vieux ami Fadey a essayé de te tromper !\nSi seulement j'avais assez d'argent pour couvrir ma dette envers ton frère, je te l'échangerais immédiatement contre ta monnaie méprisable... C'est un objet très précieux et sa valeur ne se mesure pas qu'en argent, da !";
			link.l1 = "D'accord, d'accord, calme-toi Fadey. Je te crois. Tes arguments sont assez convaincants et l'ardeur flamboyante que tu démontres est soit un témoignage de ta sincérité, soit de ton extraordinaire fourberie.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Merci! Vous avez bien fait, Charles, de ne pas vous offusquer et de venir directement à moi pour une explication. Je suppose que maintenant l'affaire est réglée ?";
			link.l1 = "Oui, Monsieur Fadey. Complètement. Maintenant, s'il vous plaît, permettez-moi de prendre congé...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Stoi, Charles ! Je vais être honnête, j'aime ton style. Peut-être que toi et moi pourrions devenir les meilleurs amis un jour. Et pourquoi ne pas faire le premier pas vers cette amitié dès maintenant ? J'ai mis à rafraîchir deux bouteilles d'excellente vodka russe dans de l'eau de source glacée en bas à la cave. Que dis-tu, toi et moi ouvrons une bouteille à la santé de ton frère ?";
			link.l1 = "Hm. Je suis désolé, Monsieur Fadey, mais il est déjà temps pour moi de prendre la mer. Je suis un peu pressé.";
			link.l1.go = "vodka_no";
			link.l2 = "Tu avais offert la dernière fois et j'ai refusé... Ce serait impoli de refuser deux fois. Bien, Fadey. J'en suis!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "C'est bien dommage. Comparé à la vodka, le rhum n'est que de l'eau, un liquide bon marché et insipide. Mais puisque tu es pressé, je ne te retiendrai pas plus longtemps. Bonne chasse, Charles !";
			link.l1 = "Pareille à vous, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "C'est ce que j'aime entendre! Splendide! Asseyez-vous et reposez vos pieds! Je vous en prie, Monsieur, faites comme chez vous pendant que je vais chercher la vodka. Oh, combien ces après-midi avec des amis m'ont manqué! Ah, la vodka est bien fraîche, vous allez l'apprécier, nazdoroviya! Laissez-moi disposer quelques cornichons et du jambon fumé.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Ouah... Alors, dis-moi, Fadey, c-comment ça s'fait? Hips ! On a bu... d-deux b-bouteilles de v-vodka... au fait ! - tu as l'air t-tout à f-fait sobre et moi... je suis ivre comme un polonais. C-comment ça se fait, hein ?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, mon cher, détends-toi. Qu'est-ce qu'une mouffette a à voir avec tout ça ? Nous venons de descendre une excellente vodka. Dors un peu et tu seras frais et dispos au réveil. Même ta tête se dégagera sans gueule de bois. Tu verras.";
			link.l1 = "O-ouais, la vodka... c'est... c'est absolument magnifique, cette vodka. Je n'ai jamais bu quelque chose comme ça.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha ! Tu as bien raison ! Ce genre de vodka était fabriqué selon des recettes secrètes et expédié de ma patrie, la Russie, et même là-bas, tout le monde ne sait pas la faire correctement. Je n'achète que le meilleur ! Comme cette bouteille ici que toi et moi avons eu la chance de déguster.";
			link.l1 = "B-mais dis-moi, Fadey : c-comment p-peux-tu boire a-autant sans être ivre ? C-comment tu fais ça, hein ? P-partage le secret avec moi. P-peut-être que ça s-sera utile plus tard... Hic !";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Eh bien, tu ne peux pas te comparer à moi, jeune Charles ! Regarde-toi, maigre comme un fouet. En plus de ça, tu n’as pas l’habitude de boire sérieusement, hein ! Mais comme nous sommes de vrais amis, je vais te révéler quelques secrets sur comment boire sans te pisser dessus.";
			link.l1 = "Je vous  en  p-prie, f-faites...hic !";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Eh bien, si tu veux boire sans te faire exploser instantanément, tu dois suivre quelques règles clés. Surtout, ne bois jamais si ton estomac est vide. Mange quelque chose de copieux avant que la session de boisson ne commence\nDeuxièmement, n'oublie pas de manger quelque chose après chaque verre. Viande ou poisson seront les meilleurs, quelque chose de savoureux et salé. Troisièmement, ne lave pas l'intérieur de ta bouche avec la vodka, avale-la d'un coup\nDe plus, prendre un petit - pas plus d'une demi-pinte - verre avant le plat principal préparera ton corps à recevoir des doses sérieuses d'alcool. Ne fais pas trop cet amuse-bouche, sinon l'effet sera tout à fait l'opposé et tu te détruiras avant de prendre la mer\nEnfin, un entraînement disciplinaire est la clé, boire des quantités modérées de rhum ou d'autres types d'alcool régulièrement te rendra plus résistant à ceux-ci.";
			link.l1 = "Hm-mm... A-alors c'est comme ça que tu fais ! Je m'en souviendrai t-tout à fait...hic!.. de toutes tes ins-structions, Fadey. M-merci. Et m-maintenant je pense que ce serait une b-bonne idée pour moi d'aller me c-coucher, parce que je ne me sens pas très bien en ce moment.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Repose-toi, Charles. Nous avons passé une belle soirée, toi et moi ! Bonne chasse à toi !";
			link.l1 = "Au revoir, Fadey ! Je pars pour - hic ! - le Réalisateur de Souhaits !";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Quoi, il a vraiment dit que je vous aiderais ?";
			link.l1 = "Eh bien, à peu près. Donneras-tu un coup de main au frère de ton vieil ami ? Ce n'est pas comme si je te demandais l'aumône comme un mendiant. Je te demande de me donner une chance de gagner de l'argent.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Oh Charles ! Tu es en retard. Si tu étais venu plus tôt, j'aurais trouvé ce qu'il te fallait, mais maintenant - prosti. Ne t'inquiète pas, promène-toi dans les villes, bavarde avec les gens. Il y a beaucoup de travail à faire dans les Caraïbes.";
			link.l1 = "Je vois, c'est regrettable. Adieu!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hum. Nyet, je ne vais pas te refuser bien sûr. Si tu veux nourrir un homme, ne lui donne pas un poisson, mais une canne à pêche. N'est-ce pas, Monsieur de Maure ? Alors tu as besoin d'un travail... Assez facile. Je vais discuter avec un homme que je connais et je te recommanderai à lui. Et tout le reste dépendra de la façon dont tu fais le travail.";
			link.l1 = "Magnifique. A qui dois-je parler ?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Passez par la boutique demain. Un homme du nom de Gerard LeCroix vous y attendra. Il vous donnera du travail. Il ne restera dans cette colonie que jusqu'à demain soir. Voyez-le bientôt et faites le travail correctement. Ne me mettez pas dans une position délicate.";
			link.l1 = "Marché conclu. Merci, Fadey !";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ah, comment puis-je vous aider, mon ami ?";
			link.l1 = "Fadey, écoute, j'ai vraiment besoin d'acheter cinquante esclaves aux contrebandiers. Le problème, c'est que je suis un inconnu pour eux et j'ai besoin que tu me présentes. Sans toi, ils ne m'écouteront même pas, et c'est une question de vie ou de mort pour une personne très importante.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho ! Vous diversifiez votre activité, à ce que je vois ! Que c'est lucratif ! Je vais vous aider, cher ami. Mais comme vous le savez, je ne travaille pas gratuitement. Il faudra 150 doublons d'or pour convaincre le vendeur de vos bonnes intentions d'acheter les nègres et, bien sûr, un petit supplément pour mes efforts assidus...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Je n'attendais rien de moins, Monsieur Fadey ! Voici votre or.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Je vais chez l'usurier immédiatement ! Tenez bon, Monsieur Fadey, je reviens tout de suite !";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, il semble que j'ai trouvé quelque chose et je n'ai plus besoin des nègres. Je suis désolé. Au revoir !";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Excellent, mon ami. Mais si tu veux me tromper avec la nécessité de ton achat et que c'est pour des fins futiles, tu me mettras en grande colère. Tu ne veux pas ça. Demain à dix heures au coucher du soleil sur la plage de Capster, je te fixerai un rendez-vous, ne me fais pas défaut.";
			link.l1 = "Vous n'avez rien à craindre, je reviendrai pour la marchandise.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Bonjour bonjour ! Dites-moi, bon compagnon, qu'est-ce qui vous amène dans ma modeste demeure ?";
			link.l1 = "J'ai besoin d'armes. Les marchands locaux ne peuvent pas trouver la quantité dont j'ai besoin, mais je pense que tu peux m'aider.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Tout d'abord, dis-moi, cher ami, ce dont tu as précisément besoin. Ensuite, je te dirai exactement si je peux t'aider.";
			link.l1 = "J'ai besoin de 30 pistolets de soldat, de deux mousquets à mèche, de 70 cartouches pour eux et de 90 potions de guérison.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", tu me fais peur. D'abord cinquante negres, puis des armes. Essaies-tu de déclencher une révolte d'esclaves, mon ami ?";
					link.l1 = "Très perspicace, Fadey. Comme je l'ai dit plus tôt, tout cela est nécessaire pour le salut d'une personne importante. Ne t'inquiète pas, elle sera arrachée des griffes des Espagnols, ainsi ta réputation ici ne souffrira pas.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "C'est bon à entendre. Je peux aider.";
			link.l1 = "Je suis heureux de l'entendre. Combien ?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Je suis heureux que vous vous soyez expliqué. Et si cela a vraiment un rapport avec les Espagnols, alors je vous aiderai. Mais s'il s'avère que vous m'avez trompé, je serai très en colère.";
			link.l1 = "Aie un peu de foi en moi, Fadey. Combien ?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Bien, alors ... des pistolets et quelques mousquets, avec poudre et balles pour chacun... Donc ... je ne peux pas promettre que j'obtiendrai absolument tout ce que vous avez demandé mais je ferai tout mon possible. En attendant, j'ai besoin d'un acompte de 40 000 pesos, ou 300 doublons si vous préférez.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Prends des doublons, Fadey. Il se trouve que j'en ai quelques-uns sur moi en ce moment.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Tous mes doublons sont épuisés, prends des pesos, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Je dois parler à mon banquier. Je reviens tout de suite !";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Excusez-moi, Fadey, mais je ne peux pas me le permettre. Je vais essayer de me débrouiller tout seul. À bientôt !";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Viens demain, "+pchar.name+", et j'aurai le matériel dont vous avez besoin.";
			link.l1 = "Alors je ne vais pas m'en mêler. À demain !";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Viens demain, "+pchar.name+", et j'aurai le matériel dont vous avez besoin.";
			link.l1 = "Alors je ne me mettrai pas en travers. À demain !";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Eh bien, mon garçon, j'ai eu la chance de trouver tout ce que tu as demandé dans un délai si court. Tu devrais être reconnaissant ! Maintenant, le paiement final. Donne-moi exactement autant que ce qui a été donné comme dépôt, et prends tes armes.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Prends 300 doublons. Je ferai porter les armes à mon navire par mes hommes. Que ferais-je sans toi, Fadey ? Tu n'as aucune idée à quel point tu m'as aidé !";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Prends 40 000 pesos. Je ferai transporter les armes sur mon navire par mes hommes. Que ferais-je sans toi, Fadey ? Tu n'as aucune idée de combien tu m'as aidé !";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Eh bien, diantre, comment ai-je pu oublier l'argent ? Je reviendrai bientôt.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Excusez-moi, Fadey, je suis fauché. Gardez l'acompte, j'espère que cela suffira à compenser vos dépenses avec cet accord, et je vais essayer de me débrouiller seul. À bientôt !";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Aider ceux dans le besoin est un honneur. Aider ceux qui paient est un plaisir. La prochaine fois que vous êtes à Basse-Terre, assurez-vous de me rendre visite pour me dire bonjour.";
			link.l1 = "C'est absurde - être à Basse-Terre et ne pas voir mon ami Fadey ! Jusqu'à la prochaine fois !";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Aider ceux qui sont dans le besoin est un honneur. Aider ceux qui paient est un plaisir. La prochaine fois que vous serez à Basse-Terre, assurez-vous de me rendre visite pour me saluer.";
			link.l1 = "C'est absurde - être à Basse-Terre et ne pas voir mon ami Fadey ! À la prochaine !";
			link.l1.go = "exit";
		break;
		// <-- legendary edition

		case "guardoftruth":
			dialog.text = "Eh bien, qui douterait que tu viennes pour affaires, mon ami ! Hélas, pas de vodka à t'offrir pour le moment, j'ai tout bu. Dis-moi dans quel pétrin tu t'es encore fourré.";
			link.l1 = "Un certain corsaire a offert à une paroisse locale une croix pectorale en or avec du lazurite pour obtenir le pardon de ses péchés. C'est un objet unique et précieux. Le problème est que cette croix a été volée à une autre paroisse. Non seulement cela, mais un prêtre a été assassiné pendant le vol.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ô immaculée Théotokos ! Ça alors !";
			link.l1 = "Ouais. Je représente les paroissiens volés et j'essaie de rendre la croix à ses propriétaires d'origine.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Une noble action, et très pieuse. Essaye-tu de gagner des points avec le Tout-Puissant ?";
			link.l1 = "Mais le père local refuse de me le rendre, malgré tout ce que je lui ai dit. Je ne comprends pas. Comment peut-on placer calmement une croix volée avec le sang d'un homme innocent dessus dans la Maison de Dieu ? C'est un blasphème !";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Eh bien, techniquement, chaque calice consacré porte le sang du Christ Innocent... mais je m'égare. Je suppose que vous voulez que je vous aide ?";
			link.l1 = "Je le fais ! Vous avez une grande influence à Basse-Terre. Vous êtes très respecté, donc peut-être que le prêtre écoutera vos admonitions.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", avez-vous raconté l'histoire exacte de cette croix volée à notre prêtre ?";
			link.l1 = "Bien sûr ! J'ai fait appel à ses sentiments religieux, à la solidarité chrétienne, à sa foutue conscience pour l'amour de Dieu, mais il a fermé les oreilles.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Avez-vous essayé d'utiliser d'autres méthodes pour le convaincre ?";
			link.l1 = "Tu veux dire le soudoyer ? Je ne vais pas soudoyer un prêtre. S'il s'agissait d'un banquier, ou d'un marchand, ou même d'un gouverneur, j'essaierais de résoudre le problème de cette manière, mais pas un prêtre !";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Mon cher ami naïf, si les oreilles du prêtre sont vraiment fermées aux proclamations de conscience, alors ses mains seront sûrement ouvertes à l'or... Ou l'inverse. Je vais t'aider, je pense que garder un tel trésor souillé ici est voué à causer de plus gros ennuis plus tard. Cependant, cela nécessitera certaines dépenses."link.l1 ="Pourquoi cela ne m'étonne-t-il pas ? Combien cette fois ?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Passe demain, "+pchar.name+", je ne puis encore nommer le prix. Mais tu auras cette croix volée, sois-en assuré.";
			link.l1 = "Très bien Fadey, je ne te dérangerai plus alors. À demain !";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Comme promis, j'ai la croix. Quant aux détails... oh, oubliez-les... toutes des sottises pardonnées par le sang versé de notre Précieux Sauveur";
			link.l1 = "Combien vous dois-je ?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Deux cent cinquante doublons. Pour couvrir mes frais, et bien sûr j'apprécierais un petit extra pour mon aide vertueuse...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Oui oui, Monsieur Fadey. Voici votre or.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Je dois aller chercher l'or dans ma cabine. Je reviens tout de suite.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "D'accord. Voici la croix volée.";
			link.l1 = "Merci, Fadey. Tu ne peux même pas imaginer combien tu as fait pour moi !";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je suis toujours heureux d'aider un ami aimable - et plus important encore - généreux. Passe plus souvent. Peut-être que nous aurons de la vodka quand elle me sera livrée depuis la mère patrie.";
			link.l1 = "Volontiers !";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Eh bien, eh bien, la mer ne t'a pas encore réclamé! Raconte-moi tout. Quelles mésaventures t'ont amené à ma porte cette fois-ci?";
			link.l1 = "Je ne sais pas si je dois appeler cela des malheurs ou non, mais néanmoins je suis ici. Fadey, le premier jour où nous nous sommes rencontrés, tu m'as donné un poignard rare, la Griffe du Chef. Maintenant, je sais qu'il appartenait auparavant à un homme nommé Archibald Calhoun. S'il te plaît, dis-moi ce que tu sais sur cet homme.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Rien ne peut vous être caché, "+pchar.name+"Tu vois à travers tout, tout comme ton frère. Oui, j'ai gagné ce poignard lors d'une partie de dés contre Calhoun. Qui est-il ? Je n'en ai moi-même pas la moindre idée. Nous nous sommes rencontrés par hasard à la taverne, nous avons commencé à discuter, avons bu un peu, et il a commencé à me parler de certains péchés de son passé qui le pesaient...";
			link.l1 = "Qu'es-tu, son confesseur? Quels péchés?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald était consumé par le souvenir d'un homme torturé à mort par l'Inquisition à cause de lui et d'autres âmes innocentes qu'il avait tuées. Il n'arrêtait pas de se traiter de Judas. Il disait que Dieu le punissait pour ses péchés et que l'Inquisition le traquait\nIl a mentionné que l'inquisiteur espagnol Vincento lui-même voulait sa mort et avait envoyé des mercenaires pour le chasser à travers les Caraïbes. Puis l'alcool l'a emporté sur son meilleur jugement et nous avons parié pour ce vieux poignard.";
			link.l1 = "C'est tout? Tu ne l'as jamais revu?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Bien sûr que non, il est mort maintenant. Une bande de misérables pirates a envoyé son flûte au casier de Davy Jones et tout l'équipage à Mictlantecuhtli. À vrai dire, les rumeurs disaient qu'ils avaient été attaqués par des professionnels déguisés en pirates... des agents de l'Inquisition. Le Père Vincento attrape toujours son homme, dit-on.";
			link.l1 = "Archibald Calhoun est vivant. Je l'ai vu il n'y a pas longtemps avec un certain William Paterson. Il sert comme son second.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh ho, quelle surprise ! Archibald peut au moins reprendre son souffle sous l'aile du capitaine Paterson. Il est en bonne compagnie. Les Espagnols craignent Patterson comme la peste. Ils n'oseront pas comploter contre Archibald tant qu'il est sous la protection de Paterson.";
			link.l1 = "Connaissez-vous Paterson ?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Qui ne connaît pas William Paterson !? C'est un nouveau venu dans les Caraïbes, tout comme vous. Et tout comme vous, il s'est déjà forgé une réputation imposante. M. Patterson est le plus proche ami du Colonel Fox et bien en cour auprès de Lord Windsor lui-même, le gouverneur général de toutes les colonies anglaises dans les Caraïbes. Il rend souvent visite au palais du gouverneur à Port Royal, en Jamaïque.";
			link.l1 = "Compris. Merci pour l'information, Fadey !";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh, n'en parle pas, ami. Viens me rendre visite un de ces jours ! Bonne chasse !";
			link.l1 = "Certainement !";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Jetons un coup d'œil, "+pchar.name+"... Da ! C'est l'un d'eux ! Voilà mon garçon, tu as fait ma journée ! Où l'as-tu trouvé ?";
			link.l1 = "Peu importe. L'important est qu'il ait trouvé son chemin de retour vers vous.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Je paierai bien pour votre enquête approfondie. Trois cents doublons d'or devraient suffire pour vos peines...";
			link.l1 = "Me payes-tu avec quelques-uns des doublons que tu m'as extorqués auparavant ? Bien sûr, je ne les refuserai pas. Voici ton shamshir.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Spasiba, mon ami ! Merci pour l'épée et pour tes mots sardoniques. Tu es sage au-delà de ton âge, "+pchar.name+", mais les liens d'amitié entre les hommes surpassent la valeur de l'or. En parlant d'or, - je vous paierai en totalité. Tenez, prenez vos doublons.";
			link.l1 = "Merci.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Et en parlant des liens d'amitié, les tiens et les miens en particulier, "+pchar.name+"J'ai quelque chose qui pourrait bien t'intéresser.";
			link.l1 = "Laissez-moi deviner, plus de vodka ?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha ! La vodka est bonne, mais ce n'est pas la seule chose pour laquelle mon pays est connu. Il y a un matériau spécial que seule la Russie produit. Je fais venir ce matériau de mes contacts chez moi pour le commerce ici. Chaque capitaine le veut, car il améliore n'importe quel navire. Je parle des cordages en chanvre. Des cordages imperméables à l'humidité et au sel de mer. On dit que c'est le meilleur matériau pour le gréement. Chaque mois, je reçois une certaine quantité livrée depuis Reval. Normalement, mon entrepôt a quelques centaines de bobines vers le milieu de chaque mois. Alors, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Compris. C'est une offre formidable, Fadey ! Je pense que je vais profiter de l'opportunité que tu m'as présentée. Alors, chaque vingtième jour du mois, cinq cents doublons pour cinquante pièces ?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Da. Va chercher ton achat. Mais attends, attends, cher ami ! En plus de ce shamshir, que tu m'as rendu par véritable bienveillance, il y en avait deux autres. Je te prie, s'il te plaît, si tu les trouves, ramène-les-moi et je te paierai plus qu'un prix équitable pour leur retour.";
			link.l1 = "D'accord, Fadey. Si je les trouve, je les ramènerai.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Bonne nouvelle pour toi. J'ai un autre shamshir persan.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Oh, mon bon ami ! Tu as essuyé mes larmes ! Laisse-moi voir... Da ! C'est ça, mon précieux shamshir ! Voici, comme je te l'avais promis, trois cents doublons en récompense.";
			link.l1 = "Merci!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Je vous prie d'accepter ma gratitude et un modeste mais très utile cadeau. Je n'en ai pas besoin, mais vous ou votre charpentier de marine le trouverez fort utile\nRegardez, voici cette belle bague ! Elle est à vous maintenant. Mais ce n'est pas une bague ordinaire, c'est une bague enchantée. Elle aide dans la menuiserie et la réparation de navires. Beaucoup d'artisans aimeraient l'avoir, mais je l'ai gardée pour une occasion spéciale. Prenez-la, mon ami, je souhaite qu'elle allège votre fardeau !";
			link.l1 = "Vous transportez certainement beaucoup d'artefacts intéressants. Merci, Fadey !";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Il ne reste qu'un seul shamshir de ma collection perdue à retrouver. Je compte sur vous, "+pchar.name+", et de ta chance. Si tu le trouves, n'hésite pas à te hâter de revenir vers moi.";
			link.l1 = "Certainement ! À bientôt...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Pourquoi devrais-je me presser? L'épée est avec moi.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Oh, merci Dieu, que j'ai demandé précisément à vous de l'aide, "+pchar.name+". Tu es un homme miraculeux, mon ami ! Montre-le-moi... Ohooo ! C'est, c'est elle. Ma chérie ! Krasavitsa ! Merci mille fois, brave homme, je te fais une révérence ! Tiens, voici ton argent. Quatre cents doublons et pas un kopek de moins ! Je ne serai pas avare.";
			link.l1 = "Merci, Fadey. Un plaisir d'aider.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "Ma collection de shamshirs est enfin réunie ! Personne n'osera plus me la voler, je m'en assurerai ! J'ai une récompense très spéciale pour vous, brave homme. Dans deux semaines, un marchand m'apportera une armure d'escrime excellente en provenance d'Europe. Commandée par un noble, c'est une pièce d'armure tout à fait unique. Alors, si vous le voulez, vous pouvez l'acheter pour seulement sept cents doublons d'or. Je dirai au noble qu'elle a été perdue en route.";
			link.l1 = "Qu'y a-t-il de si bien avec cette armure ?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "C'est très confortable et durable, et pourtant cela fonctionne aussi bien qu'une cuirasse en fer. En plus, ça a fière allure ! Tu devrais revenir dans quelques semaines et y jeter un œil. Mais ne traîne pas plus d'un mois, sinon je le vendrai au client d'origine.";
			link.l1 = "D'accord. Je passerai chez toi dans deux semaines.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Da, c'est déjà livré et ça t'attend. As-tu apporté l'argent ?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Oui. Voici sept cents doublons.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Bon sang. J'ai oublié l'argent sur le navire. Je le ramène dans une seconde !";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Oui, mon bonhomme ! Tenez, prenez-le. Cette armure en osier vous servira bien, je vous l'assure. Il n'y a rien de tel, nulle part dans les Caraïbes !";
			link.l1 = "Oui, je vois cela. Merci ! J'ai hâte de l'essayer...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Pourquoi as-tu besoin d'attendre ? Vas-y. Voyons comment ça s'adapte.";
			link.l1 = "Ça marche. À plus tard, Monsieur Fadey !";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Entrez, mon cher ami. La marchandise est prête à être achetée. 2125 doublons pour deux cent cinquante pièces.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Tout est comme convenu. Prends l'argent.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = " Laisse-moi juste apporter les pièces de ma cabine.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Entrez, mon cher ami. La marchandise est prête pour vous. Cinq cents doublons pour cinquante pièces.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Tout est comme convenu. Prends l'argent.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Permettez-moi d'apporter les pièces de ma cabine.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadeï, serait-il possible d'augmenter le volume de nos transactions ? Je suis prêt"+GetSexPhrase("","e")+" à vous acheter cinq fois plus de marchandises ! Je pense que cela nous profiterait à tous les deux. Qu'en pensez-vous ?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadeï, j'ai apporté l'argent ! Trois mille doublons d'or, comme convenu.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Ravi de faire affaire avec vous, "+pchar.name+"Je vais ordonner à mes hommes de charger les cordages sur votre navire.";
			link.l1 = "Merci !";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Si tu as encore besoin de cordages, reviens dans un mois.";
			link.l1 = "Très bien, Fadey. À plus tard !";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Que puis-je faire pour vous, mon cher ami ?";
				link.l1 = "Vous êtes un homme influent, Fadey. Un ami du gouverneur, et, selon les rumeurs, vous avez des relations à la cour. Pourriez-vous solliciter les autorités au cas où j'aurais des ennuis avec la loi ?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Comment puis-je vous aider, mon ami ?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "J'ai un problème avec les autorités anglaises.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "J'ai eu des ennuis avec les autorités françaises.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "J'ai un énorme problème avec les contrebandiers.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Désolé, je pense pouvoir m'en occuper moi-même.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, mon bonhomme, qui vous a dit cela ? Tout le monde ment. Mais puisque vous êtes le frère de Michel et un bon ami à moi, je peux essayer de régler les choses pour vous. Je peux faire des démarches auprès des autorités anglaises et françaises uniquement, bien que mes connexions aient leurs limites. Je ne fais pas affaire avec les Espagnols et les Hollandais\nJe vous avertis également que mon influence ne suffit qu'à vous sauver de petites infractions. Je peux les persuader de reconsidérer leur attitude envers vous en cas de légère inconduite ou d'apaiser une colère modérée. Alors allez déclencher une guerre et attendez-vous à ce que je tire vos marrons du feu !\nEn plus de cela, je ne peux apaiser qu'une nation à la fois : la France ou l'Angleterre. Je ne peux pas me déchirer en deux pour faire deux choses à la fois. Bien sûr, des pièces seront également nécessaires pour faire des pots-de-vin. N'hésitez pas à venir me voir pour de l'aide si vous trouvez mes conditions acceptables.";
			link.l1 = "Merci, Fadey. Je m'en souviendrai.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Bien sûr. J'ai bien entendu parler de vos aventures - ou mésaventures. Je peux m'occuper de votre petit problème, rien qu'une bonne quantité d'or graissant les bonnes mains ne puisse résoudre. Trois cents doublons d'or et je vous sortirai du pétrin.";
				if (PCharDublonsTotal() >= 300) // belamour legendary edition
				{
					link.l1 = "Super ! Voici l'or.";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "Alors c'est juste le bon moment pour aller chercher les pièces.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Bien sûr. J'ai bien entendu parler de tes aventures - ou mésaventures. Je peux m'occuper de ton petit problème, rien qu'une bonne somme d'or glissée aux bonnes mains ne puisse résoudre. Six cents doublons d'or et je te sortirai de la marmite.";
					if (PCharDublonsTotal() >= 600) // belamour legendary edition
					{
						link.l1 = "Génial ! Voici l'or.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Alors c'est le moment idéal pour aller chercher les pièces.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Oui, tu es dans de beaux draps ! Je ne peux pas complètement démêler cette situation. Cependant, je peux adoucir le coup de foudre qui va s'abattre sur ta tête pécheresse. Et plus tard, à tout moment, nous pouvons présenter à nouveau un pot-de-vin si tu as l'argent et le désir. Sept cents doublons d'or et je peux commencer à aplanir tes ennuis.";
					if (PCharDublonsTotal() >= 700) // belamour legendary edition
					{
						link.l1 = "Je suis fatigué des chasseurs de pirates qui me poursuivent. Voici l'or.";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "Alors c'est le moment idéal pour moi d'aller chercher les pièces.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "D'accord, donne-moi environ dix à quinze jours. Pendant ce temps, je prendrai rendez-vous et m'occuperai de ceci et cela. Tout sera réglé dans environ deux semaines. ";
			link.l1 = "Merci, Fadey ! Je vais attendre...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "Pourquoi es-tu allé les énerver, mon brave? Les contrebandiers ne sont pas les pires gens dans cette partie du monde et ils peuvent te rapporter un bon profit. Soit, je vais t'aider, je sais comment les amadouer... Ça fera sept cents doublons, pas de marchandage.";
			if (PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				Link.l1 = "Très bien, Fadey, je suis d'accord. Prends ton or.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Je n'ai pas autant d'or sur moi maintenant. Je reviendrai plus tard !";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Bien, je vais arranger la querelle, ne t'inquiète pas. Ils feront à nouveau affaire avec toi, comme au bon vieux temps.";
			Link.l1 = "Merci !";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, je vois que vos affaires ne sont pas vaines, et que votre appétit grandit ! C'est vrai, nos marchandises sont bonnes, et les prix ne sont pas mordants. Notez cependant que des investissements sont nécessaires ! Une telle affaire exige une approche sérieuse pour que tout soit parfait.";
			link.l1 = "Viendrais-je vous voir avec une telle proposition sans avoir quelques centaines de doublons en réserve ?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Je sais que vous avez des pièces dans votre coffre, et pas qu'une paire, sûrement une cinquantaine y tiendrait ! Mais notre affaire n'est pas ordinaire - il ne s'agit pas simplement de transporter des marchandises, mais de trouver une voie... disons, discrète. Pour une telle ampleur, il faudra non seulement payer, mais investir lourdement, pour que ce soit rentable ! Et pour que votre argent ne parte pas en fumée. Si vous êtes prêt"+GetSexPhrase("","e")+" à vous séparer de trois mille doublons d'or, alors prenez ma parole que tout sera fait correctement pour vous, en tant que bon ami, et nous ne vous ferons pas tort sur le prix.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Trois mille doublons ! Eh bien, j'avoue qu'une offre aussi généreuse est rarement entendue même par les négociants les plus prospères, même dans les histoires les plus fantastiques ! Peu sont prêts à investir si généreusement dans une telle entreprise. Mais je suis, heureusement, de ce nombre. Voici votre argent, Monsieur Fadeï.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Trois mille doublons d'or ! Je ne suis pas prêt"+GetSexPhrase("","e")+" pour une telle somme, Fadeï. Malheureusement. Je reviendrai plus tard.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Trois mille, dites-vous ? Eh bien... À vrai dire, une telle somme force le respect pour votre ambition. Mais je dois avouer - cette affaire n'est pas pour moi.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Quel revirement ! Vous venez avec une proposition, puis vous vous rétractez immédiatement ! J'avoue ma déception, mais je ne laisserai pas tomber notre amitié. Restons-en à l'ancienne formule : notre accord précédent tient - cinquante bobines à dix doublons chacune, chaque mois, le 20.";
			link.l1 = "C'est bien que vous me compreniez, Fadeï. Je serais ravi"+GetSexPhrase("","e")+" de changer d'avis, mais de telles dépenses sont au-delà de mes moyens. Hélas, mes possibilités sont limitées dans cette affaire.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Eh bien, si c'est votre décision, il n'y a plus rien à discuter. Ce tournant n'annulera pas notre amitié. Venez nous voir, "+GetSexPhrase("cher monsieur","chère demoiselle")+".";
			link.l1 = "Au revoir.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "Voilà qui est sensé ! Vous n'êtes pas de ceux qui ne font que parler, mais qui savent aussi agir. Pour les gens d'affaires comme vous, il y a toujours une remise à trouver ! Quinze pour cent sur toutes les livraisons futures ! Voici notre accord : 250 bobines de corde de chanvre que je tiendrai prêtes pour vous chaque mois. Vous pourrez les récupérer, comme avant, le 20, en payant 2125 doublons pour tout, sans reste.";
			link.l1 = "Parfait, Fadeï ! Il est étonnamment facile de faire des affaires avec vous. Je suis sûr"+GetSexPhrase("","e")+" que le succès nous attend. À bientôt !";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}