// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Oh! Bonjour, monsieur. Comment êtes-vous arrivé ici?";
				link.l1 = "Bonjour, Gino. Faisons connaissance. Je suis le Capitaine "+GetFullName(pchar)+" et je suis ici avec la permission de John. Je vais être clair - j'ai besoin de votre aide, mais je peux aussi vous aider.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh ! Bonne journée, monsieur. Comment êtes-vous arrivé ici ? Et où est John ?";
				link.l1 = "Eh bien, eh bien... Et c'est donc celui qui se cachait toujours derrière cette porte fermée ! Intéressant... À propos de John... Il est parti. Et cette maison est à moi maintenant. Mais ne vous inquiétez pas. Faisons connaissance, qui êtes-vous et que faites-vous ici ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Bonjour, "+pchar.name+". Ton visage me dit que tu as trouvé quelque chose d'important. As-tu trouvé tous les composants du Gardien de la Vérité ?";
					link.l1 = "Exactement ! J'ai tous les trois objets avec moi : le poignard, la carte et la boussole !";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Bonjour, "+pchar.name+"Qu'est-ce qui s'est passé ? Vous avez un air étrange sur le visage...";
					link.l1 = "J'ai quelque chose à te dire, Gino. C'est du lourd.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"Oui, je me souviens, deux jours se sont écoulés et tu veux en savoir plus sur le Gardien de la Vérité, ai-je raison ?";
					link.l1 = "Oui, tu l'es ! As-tu pu dénicher quelque chose ?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "As-tu apporté 5 000 pesos, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Bien sûr. Tiens, prends l'argent et achète tout ce dont tu as besoin.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Malheureusement, je n'ai pas l'argent sur moi en ce moment.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Hélas, "+pchar.name+", Je suis vraiment désolé - le patient est mort. Il s'est soudainement aggravé et il est parti très vite.";
					link.l1 = "Dommage... Que Dieu ait pitié de son âme !";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Bonjour, "+pchar.name+"A-t-il    quelque chose qui s'est passé ? Tu as l'air très inquiet...";
					link.l1 = "Gino, j'ai une demande inhabituelle pour toi ! Il y a un homme avec une forte fièvre sur mon navire. Il délire et est inconscient... peux-tu l'aider ?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", j'attends le patient. Dépêche-toi, plus vite tu l'amènes ici, plus j'aurai de chances de le sauver.";
					link.l1 = "Oui, oui, il sera livré ici sur-le-champ.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "Tu l'as amené juste à temps, "+pchar.name+". Il est dans un état critique, mais il y a encore une chance.\nCapitaine, je suis à court d'ingrédients et nous n'avons pas le temps de les rassembler dans les jungles. Je dois les acheter tous chez les herboristes locaux pour 5 000 pesos. Pouvez-vous fournir la somme?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Bien sûr. Tenez, prenez l'argent et achetez tout ce dont vous avez besoin.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Malheureusement, je n'ai pas l'argent en ce moment.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Je n'ai rien à dire pour le moment, "+pchar.name+"Je me bats pour la vie du patient. Il y a encore de l'espoir. Revenez me voir plus tard, je suppose que je pourrai vous dire quelque chose de plus précis bientôt.";
					link.l1 = "D'accord, Gino, je reviendrai plus tard.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "J'ai des nouvelles,"+pchar.name+"Je ne dirai pas que votre homme va bien, mais il est en vie. La maladie recule et il y a des progrès à voir. Pour être honnête, je ne m'attendais pas à ce que mes potions l'aident aussi bien.";
					link.l1 = "C'est une excellente nouvelle, Gino, mais dis-moi quand pourrai-je le prendre ? Nous avons un long voyage à faire et le temps presse.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Bonne journée, Capitaine. Heureux de vous voir.";
					link.l1 = "Comment va notre patient, Gino ?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Bonjour, Capitaine. Comment allez-vous? Besoin de mon aide?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Oui. Gino, je suppose que vous êtes un homme érudit et peut-être même connaissez-vous le latin...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "J'ai quelque chose de différent. Un petit cadeau pour vous. Tenez, jetez un œil à ce livre.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Oui, Gino. Je veux te montrer ce pistolet. As-tu déjà vu quelque chose de pareil ?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Je vous ai apporté un exemple de la charge pour mon pistolet.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "Et pour ce qui est des accusations concernant le pistolet? As-tu déjà des indices?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, j'ai trouvé le mot inconnu 'gord' dans le journal d'un capitaine. Sais-tu ce que cela signifie?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Bonne journée, Gino. Je vais bien, pas besoin d'aide. Je voulais juste prendre de tes nouvelles et discuter un peu.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "Je m'appelle Gino. Gino Gvineili. Je suis un scientifique. Mon travail consiste à préparer des poudres, des mélanges et d'autres remèdes pour monsieur Murdock. Mais depuis qu'il est parti...";
			link.l1 = "Eh bien, je suis "+GetFullName(pchar)+"Capitaine de mon propre navire. Alors, vous êtes un alchimiste, n'est-ce pas ?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Non seulement alchimiste, mais aussi médecin. Je possède une grande connaissance de la médecine. Je sais beaucoup de choses sur les herbes médicinales et je suis capable de préparer des mixtures et des potions à partir d'elles. Mais la chimie est ma vocation, je fais beaucoup d'expérimentations et certaines de mes inventions pourraient aider des personnes comme vous.\nJe connais le latin, le français, l'anglais et l'italien. Mon aide sera indispensable si vous prévoyez d'ouvrir une pharmacie comme Monsieur Murdock l'a fait...";
			link.l1 = "Oho ! Ce n'est pas tous les jours que l'on rencontre un homme si érudit. La pharmacie va bien, c'est certain, mais je suis un marin... hm, cela sonne étrange même pour moi... quoi qu'il en soit, je suis sûr que nous deviendrons amis, Gino. Tu peux continuer à vivre ici et faire tes trucs de science...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Bonjour, monami.";
			link.l1 = "Et si jamais j'ai besoin d'aide d'un alchimiste, d'un guérisseur ou d'un scientifique - je saurai à qui demander... Dis-moi, pourquoi vis-tu toujours à l'intérieur ? Ne sors-tu jamais ?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Je sors quand j'ai besoin d'acheter des ingrédients ou des herbes pour mes expériences. J'aime vivre seul, c'est ma façon d'être. J'ai consacré ma vie à la science et je ne trouve aucun intérêt dans la vie ordinaire. Livres, écrits, tubes à essai, cornues...\nMonsieur Murdock m'a donné cette opportunité en échange de mon aide pour fabriquer des drogues.";
			link.l1 = "Maintenant, tu auras encore plus de temps, Gino. Mais tu devras céder un peu du temps de tes expériences au cas où j'aurais besoin de ton aide, d'accord ?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Bien sûr, Capitaine. Je vous appellerai Capitaine, "+GetAddress_Form(NPChar)+", si cela ne vous dérange pas ? Je laisserai toutes mes recherches au cas où vous auriez besoin de mes compétences pratiques ou de mes connaissances théoriques.";
			link.l1 = "Splendide. Je suis ravi que nous nous soyons compris si rapidement. Ne vous inquiétez pas pour vos dépenses, moi ou mon intendant vous laisserons des sommes raisonnables de temps à autre.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Merci, Capitaine. Je n'ai pas besoin de grand-chose... Capitaine, j'ai une idée... pourquoi ne pas apprendre quelques compétences en alchimie ? Cela pourrait vous être vraiment utile.";
			link.l1 = "Hm. Comme mon frère m'a dit une fois - ne sois pas trop délicat pour apprendre à faire les choses de tes propres mains. Alors d'accord, pourquoi pas. Que peux-tu me montrer ?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Eh bien, certainement, tu ne pourras pas transformer le fer en or, c'est impossible... pour l'instant, mais tu peux apprendre à mélanger des ingrédients selon les instructions pour obtenir des potions ou d'autres objets utiles en résultat. Tiens, prends ce sac. Il contient tout ce dont l'alchimiste débutant aura besoin. Des tubes à essai, des flacons, des alambics, des alambics, des spatules, des tubes en verre, un brûleur et ainsi de suite...";
			link.l1 = "Fascinant !";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous devez connaître une recette pour préparer une potion ou un objet. Les recettes peuvent être achetées chez les marchands ou trouvées n'importe où. Une fois que vous avez étudié une recette, vous devez rassembler tous les ingrédients nécessaires et faire exactement ce qui est écrit.\n Utilisez vos outils d'alchimie, trouvez ou achetez un mortier et un pilon, cherchez un creuset, hélas, je n'en ai pas un supplémentaire à vous donner. Herbes, alcools, potions, minéraux, déchets - tout fera l'affaire, à condition que vous ayez la bonne recette et les bons outils.";
			link.l1 = "Je vois. J'essaierai de préparer quelque chose pendant mon temps libre. Merci, Gino ! Peux-tu me donner une recette simple ? Quelque chose pour commencer ?";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Je n'ai pas de simples... mais tiens, prends cette recette d'un antidote. Je suppose que tu es capable de mener à bien cette tâche. Prends-la.";
			link.l1 = "Gratitude! Je l'apprendrai. Adieu maintenant, Gino ! Garde ma maison, je crains de ne pas visiter cet endroit très souvent, alors tu es le bienvenu pour utiliser non seulement ta chambre, mais aussi le reste du bâtiment.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Oui, Capitaine, je connais la langue des anciens Romains. Tout scientifique, surtout un guérisseur ou un alchimiste, doit connaître le latin. Avez-vous besoin de mes connaissances en latin?";
			link.l1 = "Oui. Gino, ne me prends pas pour un imbécile mais... eh bien, comment expliquer...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Parle comme il se doit, Capitaine. N'aie pas peur.";
			link.l1 = "D'accord. Peux-tu me faire une liste d'aphorismes latins érudits ? Tu vois, il y a... un homme qui aime se vanter de son 'érudition' et il utilise parfois ces phrases latines pour me montrer mon ignorance par rapport à lui. Quelque chose comme... 'si vis pacem, para bellum'...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', tu veux dire ?";
			link.l1 = "Oui, oui. Je veux les apprendre à battre mon arrogant fr... mon ami.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "Il n'y a rien d'étrange ou de honteux dans votre demande, Capitaine. Connaître les aphorismes des anciens qui sont entrés dans l'histoire fait de vous un homme instruit. Tenez, prenez ce texte. C'est ce que vous avez demandé.";
			link.l1 = "Merci, Gino ! J'apprécie ! Je le lirai dans mon temps libre...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Montrez-moi... (lit) Impossible ! Un 'petit cadeau' dites-vous ? Ce livre est inestimable ! Où l'avez-vous obtenu ?! C'est... un véritable trésor !";
			link.l1 = "Je suis heureux que cela vous plaise.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Lisant) Incroyable ! Je n'en ai jamais entendu parler... et ça ? Je n'y comprends rien... mais je vais comprendre, nom de Dieu ! Ah, bientôt le travail bouillonnera dans mon labo !"+pchar.name+", tu ne réalises même pas CE que tu m'as donné...";
			link.l1 = "Pourquoi ne le ferais-je pas ? Je le fais. Un livre scientifique pour un scientifique...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "Mais qui est l'auteur de ce miracle ? Antoine-Laurent de Lavoisier, France... Jamais entendu parler de lui. Mais attendez ! Comment est-ce possible ! L'année d'impression est 1789 ? Mais comment...";
			link.l1 = "Je ne sais pas non plus pourquoi cette année est écrite là-dessus. Eh bien, peut-être que je le sais. Mais je te conseille de ne pas trop y réfléchir. Le livre est utile et c'est tout ce qui compte.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "C'est prometteur au-delà de toute mesure et cette année doit être une erreur d'impression de quelque sorte... Peu importe. Merci beaucoup, Capitaine !";
			link.l1 = "Tu es le bienvenu, Gino. C'est tout à toi.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "Ce n'est pas tout, Gino. Je veux te montrer ce pistolet. As-tu déjà vu quelque chose de semblable ?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Je ne suis pas armurier, mais je vais y jeter un oeil... non, je n'ai jamais rien vu de tel. Pourquoi demandez-vous ?";
			link.l1 = "Ce pistolet est puissant et destructeur, mais il nécessite des charges spéciales pour fonctionner. Rien d'autre ne marcherait. Et je n'ai aucune idée de comment fabriquer plus de munitions pour cela. Alors je suis venu ici pour vos conseils.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "As-tu au moins une cartouche pour me montrer à titre d'exemple ? Sinon, je crains de ne pouvoir t'aider.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "Je le fais. La charge est composée de deux parties : la cartouche elle-même avec une balle et cette chose qui fait exploser la poudre.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Quel échec! Quelle honte! Bon, peut-être que je trouverai plus et vous les apporterai.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "Intéressant ! Cela semble simple, il y a de la poudre à l'intérieur, une balle entre par le haut, mais cela paraît un peu étrange. Et cette 'chose'... hm. La poudre n'explose pas sans elle, n'est-ce pas ? Curieux... Regardez, Capitaine, laissez-moi m'occuper de tout cela : le pistolet et les charges. Revenez me voir dans un mois, j'ai besoin de temps pour comprendre.";
			link.l1 = "Superbe ! Essaye de comprendre comment ça fonctionne, je veux vraiment tirer avec ce pistolet.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "La question principale est de découvrir de quoi est faite cette substance qui fait exploser la poudre. Ce livre sera utile. Je vais essayer de percer ce mystère.";
			link.l1 = "Très bien. Adieu, Gino !";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Oui, j'ai compris de quoi sont composées les charges pour le pistolet. Je dois rendre hommage au livre que vous m'avez offert. Cela n'aurait pas fonctionné sans lui. Mais je dois vous avertir, Capitaine, il ne sera pas facile de créer des balles et des capsules pour cette arme.";
			link.l1 = "Capsules?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "La capsule est ce 'truc' qui, comme tu l'as dit, fait exploser la poudre. Mais commençons par le début. Es-tu prêt ?";
			link.l1 = "Oui ! Je t'écoute très attentivement.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Alors, d'abord, tu dois fabriquer une balle spéciale. Les balles ordinaires ne feront pas l'affaire. Elle doit avoir une forme conique particulière. Tu devras trouver un moule pour ces balles, le moule à balles comme je l'ai appelé. Prends des balles en plomb ordinaires, fais-les fondre dans un creuset et verse le plomb fondu dans le moule à balles. Refroidis ce moule et retire la balle finie.";
			link.l1 = "Et où puis-je trouver un tel moule à balles ?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Je ne sais pas, Capitaine. Je suis un alchimiste, pas un forgeron. Prenez cette balle par exemple, peut-être découvrirez-vous quoi en faire.";
			link.l1 = "D'accord. Continue...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Ensuite, tu dois fabriquer un contenant pour la poudre. Tu y injectes la balle. J'ai rédigé une belle instruction pour toi. Lis-la attentivement et essaie.";
			link.l1 = "Bon...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Maintenant, nous devons récupérer les capsules. Vous aurez besoin d'une feuille de cuivre très fine - fabriquez-la vous-même à partir d'une pépite de cuivre. Sculptez des cercles de la même taille que les balles. Ensuite, mettez de l'argent fulminant à l'intérieur en utilisant de la cire.";
			link.l1 = "Argent fulminant ? Qu'est-ce que c'est ?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Je ne le savais pas moi-même, j'ai découvert le secret dans votre livre. C'est une poudre blanche qui peut être faite d'argent, d'esprit et d'acide nitrique. Elle explose facilement par frottement ou secousse, c'est pourquoi elle est bien utile pour allumer la poudre à canon dans les charges de votre pistolet. Une chose désagréable, elle a explosé deux fois lors de mes essais jusqu'à ce que je trouve la recette.";
			link.l1 = "J'ai eu la chance d'avoir ce livre avec moi !";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Fais très attention, ce truc est explosif comme l'enfer ! Je pourrais en fabriquer moi-même, mais stocker de l'argent fulminant est trop dangereux, il est vital que tu le mettes dans les capsules juste après sa création. Je ne peux pas fabriquer des capsules en cuivre, je ne suis pas forgeron comme je te l'ai déjà dit.";
			link.l1 = "Très bien. Donne-moi la recette, je l'apprendrai moi-même.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "Tu es le bienvenu. Suis la recette avec précision et fais attention à l'ordre du processus, sinon tu exploseras avec tes fioles.";
			link.l1 = "Je serai prudent.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Aussi, prends ces deux flacons. Celui-ci contient de l'acide nitrique et celui-là de l'esprit-de-vin. Tu pourras fabriquer assez de fulminate d'argent pour remplir environ 20 capsules.";
			link.l1 = "Merci, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Prenez aussi votre pistolet et l'exemple de charge. Bonne chance, capitaine, dans votre fabrication de charges. J'espère que vous resterez en vie et en un seul morceau.";
			link.l1 = "Je ferai ce que je peux pour me protéger. Et, Gino, t'ai-je déjà dit que tu es un génie ?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Tu me fais rougir, Capitaine, je suis sérieux...";
			link.l1 = "D'accord. Adieu, Gino ! Tu es mon meilleur alchimiste !";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Pourriez-vous m'en dire plus sur le capitaine ? D'où vient-il ?";
			link.l1 = "Aucune idée, bien qu'il soit né quelque part dans le Nord, ils l'appelaient parfois un Viking.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Un Viking ! Oui-oui, je me souviens, j'ai lu cela dans un livre d'histoire. Gord est une colonie fortifiée d'un jarl libre.";
			link.l1 = "Un jarl libre ? Qui cela pourrait-il être ?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "C'est un prince des Hommes du Nord. Des jarls libres avec leurs bandes de guerre faisaient des raids et pillaient l'Europe il y a des siècles sur leurs navires, les Drakkars. Vous pourriez les appeler des pirates, je suppose. Les gords étaient leurs bases et leurs foyers, des lieux où ils pouvaient se reposer, cultiver et festoyer.";
			link.l1 = "Je vois. Cette gourde doit être son repaire de pirate alors... Merci, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "La fièvre et les délires, dites-vous, c'est intrigant. Amenez-le ici immédiatement ! Je verrai ce que je peux faire. Mais je ne peux rien vous promettre si son état est trop mauvais... Est-ce votre officier ?";
			link.l1 = "Non, Dieu merci, il ne l'est pas. Gino, écoute, ne demande pas qui il est, fais juste ce que tu peux, c'est vraiment important pour moi !";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "D'accord, emmenez-le dans la maison, dans votre chambre. Je vais préparer quelques mélanges... peut-être que cette racine va...";
			link.l1 = "Je vais le livrer ici immédiatement !";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Alors essaie de le trouver le plus vite possible, je ne pourrai pas le soigner sans médicaments et il pourrait être trop tard si tu ne te dépêches pas.";
			link.l1 = "Très bien, je trouverai l'argent.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Splendide, Capitaine. Maintenant je vais m'occuper de préparer quelques mélanges et je vous recommande de laisser mon patient. Revenez ici demain.";
			link.l1 = "D'accord, Gino. J'ai confiance en tes mélanges et en ton génie.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Eh bien, je pense qu'il ira bien dans deux semaines. Je ne peux pas promettre qu'il pourra danser, mais au moins il se tiendra sur ses pieds tout seul, c'est sûr.";
			link.l1 = "Merde, je n'ai pas ces deux semaines ! J'ai besoin... de prendre la mer dès que possible !";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Capitaine, je ne suis pas un mage et je peux vous assurer que cet homme est trop faible pour le moment. Je ne suis pas sûr qu'il survivra quelques jours en mer, vous ne pouvez pas le déplacer !";
			link.l1 = "D'accord-d'accord, mais deux semaines, non, même une semaine c'est trop !";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Trois jours... oui, je suppose que dans trois jours vous pourrez essayer de prendre la mer, mais il aura besoin de soins et de médicaments et vous devrez faire des escales.";
			link.l1 = "J'ai un médecin, il s'occupera de lui. Je reviendrai dans trois jours et nous le prendrons, c'est le plus que je puisse me permettre. Nous devons bouger, même avec des arrêts... oui, et une chose de plus - Gino, tu es un génie !";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Merci, Capitaine. Revenez pour votre ami dans trois jours, mais ne le dérangez pas d'ici là. Il a besoin de repos complet.";
			link.l1 = "Très bien, j'ai compris. Je l'emmènerai dans trois jours.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Il se porte bien, mais les progrès sont lents. On ne peut pas encore le prendre.";
			link.l1 = "Oui - oui, Gino, je me souviens. Trois jours...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Pas de détérioration, mais il ne s'est pas vraiment amélioré non plus. Il est toujours inconscient, il ne comprend pas où il est et pourquoi il est ici, bien que cela ne semble pas trop le préoccuper. Il a encore de la fièvre donc je ne suis pas sûr que le prendre à bord maintenant soit une bonne idée.";
			link.l1 = "Je ne peux plus attendre, nous sommes ici depuis trop longtemps déjà. Emballe tes mixtures qui l'aideront pendant le voyage et nous partons. J'espère que ce salaud est assez fort pour survivre assez longtemps pour affronter sa condamnation à mort...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Attends, Capitaine ! Ai-je traité les condamnés ? Que diable ? Un travail énorme a été fait ici, as-tu la moindre idée de la difficulté à fabriquer de la poudre sèche...";
			link.l1 = "Gino, tu n'avais pas besoin de savoir cela. Ne t'inquiète pas trop, c'est un pirate et l'un des plus terribles de son espèce. Je dois l'emmener à Curaçao pour un rendez-vous avec les autorités de la Compagnie dès que possible. Point.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "D'accord, tu sais mieux. Pirate alors... Curaçao. Qu'importe, mais écoute-moi, il dormira la plupart du temps, mais le roulis du navire et la chaleur étouffante peuvent tout faire reculer. Je recommande de faire une halte après quelques jours de navigation et de laisser ton... prisonnier se reposer à terre. Sinon, il y a un risque qu'ils aient à pendre un cadavre à Curaçao...";
			link.l1 = "Très bien, je vais le faire. La Martinique fera l'affaire, c'est presque à mi-chemin de Curaçao. J'espère que le vent sera favorable. Je vais le prendre maintenant et nous partirons. Merci encore, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "Vous êtes le bienvenu, Capitaine. Rappelez-vous que vous avez quatre jours, eh bien, cinq, mais pas plus. Et une dernière chose... vous savez, je soigne généralement les gens non pas parce que je veux qu'ils soient pendus après mon traitement. Le médecin est responsable de ses patients, peu importe qui ils sont. Et je me sens vraiment mal...";
			link.l1 = "Je suis désolé de t'avoir entraîné dans tout cela, mais nous n'avions aucune chance sans toi. Nous devons lever l'ancre maintenant, sinon les gars des Portugais réussiront à se rassembler à notre porte pour rencontrer leur patron.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Intrigant... Et comment peux-tu m'aider ? Je n'ai pas besoin d'aide et je ne l'ai pas demandée...";
			link.l1 = "Mais tu en auras besoin. Ecoute-moi d'abord, puis tire tes conclusions.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Je suis tout ouïe.";
			link.l1 = "Je suis allé à Santiago récemment... rendre visite au père Vincento. Il cherchait son secrétaire disparu nommé... Jésus, pourquoi es-tu devenu si pâle, Gino ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Vous... avez vu l'inquisiteur ? Est-il...";
			link.l1 = "Ne t'inquiète pas, Gino. Il n'y a aucune chance que je te livre à lui, bien que ce soit son ordre : te trouver et t'amener à lui. J'ai besoin d'obtenir des informations concernant un Indien du peuple Itza. Parle-moi de Tayasal, de ses trésors et du 'mal' qui l'entoure.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Je vois que vous êtes bien informé. Est-ce le père Vincento qui vous l'a dit ?";
			link.l1 = "J'ai obtenu des informations de lui et d'autres personnes. Mais j'aimerais vous écouter. Vous avez été son secrétaire, donc vous avez dû rédiger un protocole de l'interrogatoire, n'est-ce pas ?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Tu ne peux pas imaginer ce qu'il faisait à ce pauvre Indien !.. Ça me donne la chair de poule chaque fois que je me remémore cet interrogatoire.";
			link.l1 = "Cependant, parlons-en. Qui était cet Indien ? Comment est-il tombé entre les mains du père Vincento ?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Il était parmi les Indiens du peuple Itza qui voyagèrent depuis Tayasal à la recherche du Masque de Kukulcan - un artefact de l'ancien dieu maya - Kukulcan. Ces Indiens ont affronté un groupe d'aventuriers blancs dirigé par Archibald Calhoun - un chasseur de trésors écossais. Un seul Indien a survécu, son nom était Ksatl Cha. Il avait trois objets intéressants sur lui, je vous en parlerai plus tard. Calhoun avait essayé de forcer le prisonnier à lui parler des trésors, mais il est resté silencieux. Alors l'Écossais l'a livré à Santiago, au père Vincento, en échange de la permission de visiter les villes espagnoles pendant un an. Il savait que l'inquisiteur était très intéressé par toutes sortes de mystères et de légendes locales. Vincento a fait parler l'Indien. Il a commencé à parler beaucoup, il nous a tout dit ce qu'il savait et les informations que nous avons obtenues de lui ont choqué l'inquisiteur lui-même.";
			link.l1 = "Vraiment ? Et qu'est-ce qui pourrait faire trembler Sa Grâce ?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Je vais tout te raconter dans l'ordre. Il existe une ancienne cité maya appelée Tayasal au cœur des jungles du Yucatan. Elle est habitée par les descendants des Mayas - le peuple Itza. Ils essaient de vivre selon les règles et traditions de leurs ancêtres. Assurément, ils n'apprécient pas l'état du monde moderne - je veux dire la domination de l'homme blanc.\nIls rêvent du bon vieux temps. Et voici la partie la plus intéressante. Un groupe d'aventuriers blancs s'est approché accidentellement de Tayasal et a enlevé la fille du chef suprême du peuple Itza. Cela s'est produit il y a presque un quart de siècle.\nCe fut la goutte d'eau et Kanek, le chef, était enragé. Il a décidé de mener le rituel le plus dangereux et secret des Mayas - invoquer un dieu indien pour effacer toute la descendance des conquérants blancs...";
			link.l1 = "Hm... Cela doit être le démon dont parlait le père Vincento. Mais comment ce dieu indien devrait-il traiter les colons blancs ? Se montrer sous la forme d'un dragon et les brûler tous ?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+", laisse ces contes de monstres de feu aux vieilles mémés ! En fait, tu n'as pas tout à fait tort, mais notre cas est plus difficile et sérieux. Même le Déluge ne pourra pas empêcher l'Europe de s'étendre dans le Nouveau Monde. Dix autres viendront remplacer un mort. Kanek devait détruire la possibilité même de la colonisation européenne.";
			link.l1 = "Eh bien, cela s'est déjà produit.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Vous pensez dans la bonne direction, Capitaine... Le but du rite de Kanek n'était pas seulement d'invoquer l'être supérieur, mais aussi de créer un trou spatio-temporel.";
			link.l1 = "Quoi ?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Les anciens Mayas possédaient un savoir considérable, Capitaine. Kanek a trouvé la description d'un rite qui permet de contrôler le temps.";
			link.l1 = "Ouah ! Incroyable !";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Ecoute. Le but ultime du rituel est de modifier le passé pour rendre impossible l'apparition de l'homme blanc dans le Nouveau Monde. Pour réaliser cela, ils vont envoyer quelqu'un dans le passé, quelqu'un qui détient l'autorité, le pouvoir et la capacité de changer le destin des gens. Mais surtout, une telle personne doit posséder des connaissances modernes.\nRéfléchis-y, "+pchar.name+", qu'aurait-il pu arriver à Colomb si ses caravelles avaient été accueillies par une flotte indienne de frégates et de galions armés de canons modernes ? Et que se serait-il passé si les arquebuses des soldats blancs n'avaient pas affronté des arcs et des lances, mais des mortiers et des mousquets ?";
			link.l1 = "Je suppose que les Amériques n'auraient pas été découvertes du tout....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Exactement ! Et peut-être qu'un 'Colomb' indien aurait découvert l'Europe...";
			link.l1 = "Intéressant, et qui Kanek va-t-il envoyer dans le passé ? Un de ses guerriers nus ? Je doute qu'il puisse enseigner à ses ancêtres...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Ne riez pas, Capitaine. Kanek n'a pas gaspillé des années dans les temples mayas à lire leurs écrits. Un dieu indien doit être envoyé dans le passé sous forme humaine...";
			link.l1 = "Gino, quelles sottises racontes-tu ? Es-tu....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Même le Fils de notre Seigneur, Jésus-Christ, est venu sur notre terre sous forme humaine et est né d'une femme humaine, la Sainte Vierge Marie...";
			link.l1 = "Jésus, Gino... es-tu sérieux ?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Bien sûr que je le suis. Ksatl Cha était très persuasif...";
			link.l1 = "Mais quel Dieu Kanek a-t-il choisi pour une mission si 'noble' ?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Le rite était destiné à invoquer un seul Être Suprême. Le serpent à plumes, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! J'ai déjà eu l'imprudence de rencontrer son 'esprit' qui vit dans des statues. Maintenant je vois... continuez!";
			else link.l1 = "Hm. Intéressant. J'ai déjà entendu ce nom de père Vincento... continue !";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek a décidé d'invoquer Kukulcan, puisque les Itza possédaient déjà un artefact ancien de ce dieu - le Masque de Kukulcan. Celui qui possède le masque est capable de traverser le portail et lui seul sera accepté par les anciens Mayas comme un dieu vivant.\nLe prêtre a effectué le rituel, invoquant Kukulcan pour s'incarner dans le corps d'un mortel. Il a également créé une faille temporelle qui a extrait plusieurs personnes aléatoires du futur dans notre époque.\nLe but de cette extraction était de présenter l'incarnation de Kukulcan non seulement avec les connaissances de notre temps, mais aussi de l'avenir. Mais quelque chose s'est mal passé et toutes ces personnes sont arrivées ailleurs et non à Tayasal. Je n'en ai jamais rencontré aucun.\nPlusieurs portails ont été créés dans l'archipel, ils étaient censés transporter les détenteurs de connaissances futures et les agents Itza à travers toute la région et vers Tayasal. Mais ces portails ont échoué dans leur but, personne n'a été livré à Tayasal au cours des 25 dernières années...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Bien sûr... Parce que ces portails ne transfèrent les personnes capturées qu'entre eux. Incroyable !";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Intéressant...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Avez-vous vu ces portails? Dites-moi!";
			link.l1 = "Peut-être plus tard, Gino... Pour l'instant, ton histoire m'intéresse davantage. Continue !";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Père Vincento est au courant de tout ce que je vous ai dit. Cela l'a inquiété, bien sûr. Si Kukulcan, incarné sous forme humaine, atteint le portail avec le Masque et tout le savoir qu'il a rassemblé... Fin des temps. Apocalypse.\nSi le passé change - l'avenir fait de même. Notre réalité changera, elle disparaîtra, se dissoudra. Vous et moi ne naîtrons peut-être jamais. Ou nous serons différents. Une fois que Kukulcan atteindra le passé - nous cesserons d'exister.";
			link.l1 = "Et qui est l'incarnation de Kukulcan?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Qui sait. Il pourrait être en quiconque est né il y a un quart de siècle, lorsque le rituel a été effectué. En toi, par exemple... je plaisante. Mais nous avons encore une chance. Premièrement, l'incarnation de Kukulcan n'est qu'une personne mortelle, il peut se noyer, être poignardé, être abattu ou mourir de fièvre. Et dans ce cas, aucun apocalypse ne se produira jamais.\nDeuxièmement, il est impossible d'atteindre le passé sans le masque, Kanek l'a très bien caché, peut-être même trop bien. Il se pourrait que même Kukulcan incarné ne parvienne pas à le trouver.";
			link.l1 = "Dis-m'en plus.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Quelque temps après le rituel, un groupe de conquistadors espagnols a presque atteint Tayasal et a failli arriver au trésor. Les Itza ont réussi à les tuer tous, sauf un - un géant robuste de sept pieds de haut.\nKanek était inquiet que le Masque puisse être volé par n'importe quel étranger, alors il a décidé de protéger la relique. Il avait inventé son propre rituel, utilisant les connaissances anciennes des Mayas. Il a pris trois objets qui, selon lui, détenaient le pouvoir de l'homme blanc. Un poignard, qui appartenait autrefois à Cortez lui-même, et une boussole. Il a également utilisé ce poignard pour découper un morceau de peau du dos du géant espagnol capturé comme troisième objet. L'homme lui-même a été sacrifié sur l'autel de Kukulcan. Trois objets ont été utilisés dans le rituel.\nEt de ce rituel est née une nouvelle île, en pleine mer, non loin du Yucatan. Personne ne connaît son emplacement, mais le Masque y est caché. Pour le trouver, il faut utiliser le poignard, la boussole et le morceau de peau. De plus, tous les objets du trésor sont maudits, aucun d'eux ne peut quitter l'archipel.\nUne tentative de le faire provoquera une tempête qui mènera le navire directement sur les rochers de l'île où le masque est caché. Elle s'appelle Ksocheatem. Astucieux, n'est-ce pas?";
			link.l1 = "Peut-être trop astucieux. Pas de doute là-dessus. Mais comment diable Ksatl Cha était-il aussi bien informé? Je doute que Kanek partageait de telles connaissances avec de simples guerriers...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Le fait est que l'actuel chef des Itza, Urakan, le fils de Kanek, avait tout raconté à ce guerrier. Il a envoyé Ksatl Cha avec un groupe de guerriers pour trouver l'île secrète et le Masque de Kukulcan. Il lui avait donné le Gardien de la Vérité pour cela, c'est le nom des trois objets ensemble - le poignard, la boussole et la carte faite de peau humaine.";
			link.l1 = "La carte ? Et pourquoi Urakan avait-il besoin du Masque ? Il a décidé de modifier le passé lui-même ?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "La peau a les contours de l'archipel dessus, donc ils l'appellent la carte. Urakan voulait le Masque pour une raison très simple - il ne veut pas détruire la réalité existante et sacrifier sa vie et celle de son peuple pour la gloire des anciens. C'est pourquoi il comptait détruire le Masque à tout prix. Mais Ksatl Cha a été capturé par Calhoun et... eh bien, vous connaissez le reste de l'histoire. Il n'a jamais atteint Ksocheatem.";
			link.l1 = "Donc, il est possible d'empêcher la fin des temps en trouvant et détruisant le Masque ? Et où se trouve ce... Gardien de la Vérité maintenant ?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Le poignard 'Griffe du Chef' et la boussole 'Flèche du Chemin' ont été laissés à Calhoun et la carte de peau 'Des deux apparences' est encore quelque part chez l'inquisition. Calhoun l'a utilisée comme bâillon pour fermer la bouche du prisonnier. Il n'avait aucune idée de l'utilité de ces objets.";
			link.l1 = "Qu'as-tu dit? 'Griffe du Chef'? Nom d'un chien, j'ai cette dague sur moi en ce moment! Fadey me l'a donnée en remboursement de sa dette envers mon frère! Regarde!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Incroyable... C'est vraiment le cas. Je m'en souviens.";
			link.l1 = "Gino, dis-moi, que sait exactement le père Vincento de ton histoire ?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Tout, sauf les informations concernant le Gardien de la Vérité et comment le faire montrer l'emplacement de l'île secrète où le Masque de Kukulcan est caché. Ksatl Cha m'en a parlé quand nous étions seuls juste avant que je ne lui donne un mélange de poison pour mettre fin à sa souffrance. Il est mort avec un sourire sur le visage.\nAssurément, je ne pouvais pas rester à Santiago après ce que j'ai fait. J'avais de sérieux soupçons que je devenais un témoin important et dangereux pour l'inquisiteur. Le Père Vincento obtient toujours ce qu'il veut, peu importe le coût. Ksatl Cha lui a parlé du trésor de Tayasal.";
			link.l1 = "Ces trésors ont déjà été découverts par un aventurier nommé Miguel Dichoso. En as-tu entendu parler ?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "Non. Et où est-il maintenant avec ses trésors ?";
			link.l1 = "Moi aussi, je veux le savoir. C'est pourquoi je suis venu te voir, je cherche cet or indien. Dichoso a emporté les trésors en Europe et a disparu avec eux.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Je te dirai où se trouvent les trésors et Dichoso lui-même.";
			link.l1 = "Gino, tu me surprends. Comment saurais-tu cela?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Vous pouvez comprendre cela vous-même à partir de mon histoire, Capitaine. Les trésors de Tayasal étaient maudits - pas un seul objet ne peut être emporté de l'archipel. Aucun navire...";
			link.l1 = "... sera pris par la tempête et jeté sur l'île où le Masque de Kukulcan est caché ! J'étais aveugle, mais maintenant je vois. Il semble que je sais assez pour trouver Ksocheatem, les trésors et le Masque lui-même !";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Voulez-vous sauver le monde, Capitaine ?";
			link.l1 = "Je veux retrouver mon frère prodigue... Gino, comment puis-je faire en sorte que le Gardien de la Vérité révèle l'emplacement de l'île ? Tu as dit que tu savais comment faire !";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "Je connais la méthode, mais j'ignore les détails. Je ne pourrai pas t'aider tant que je n'aurai pas tous les composants du Gardien.";
			link.l1 = "Hm. Nous avons déjà le poignard. Il ne reste que la boussole et la carte. Calhoun a la boussole et le père Vincento a la carte...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Tu vas retourner chez l'inquisiteur ? Mais comment vas-tu faire ton rapport sur...";
			link.l1 = "Je dois convaincre le père Vincento que tu es mort, Gino. Ce n'est qu'à ce moment-là qu'il cessera ses recherches. Disons que tu as eu une attaque soudaine en me voyant. Tu devrais me donner un objet que je pourrai utiliser comme preuve de ta mort.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento ne croira pas à la version de la crise cardiaque, mais il te croira si tu lui dis que je me suis suicidé en buvant un poison à l'odeur d'amande. Donne-lui mon almanach, il sait que je ne m'en sépare jamais.";
			link.l1 = "D'accord. Parce que j'ai besoin de ce lien avec l'inquisiteur. Il en sait probablement beaucoup sur notre affaire.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Sois prudent avec le père Vincento. Il est aussi dangereux qu'un tigre et il mène son propre jeu. Il ne partagera ni trésors ni gloire avec toi.";
			link.l1 = "Je comprends cela. Bien, Gino, donne-moi ton almanach et essaie de te souvenir de ce que l'Indien t'a dit sur le Gardien de la Vérité, car je veux le rassembler. Je dois trouver Ksocheatem, je suis sûr que j'y trouverai non seulement le masque et les trésors, mais aussi mon cher frère.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Prenez-le. Bonne chance, Capitaine !";
			link.l1 = "Je ne dis pas adieu, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Était-ce difficile, Capitaine ?";
			link.l1 = "N'en parlons pas... Trop de gens sont morts pour obtenir ces objets. Beaucoup trop. Il semble que je ne sois pas le seul à être impatient de trouver le mystérieux Ksocheatem. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "Je peux imaginer... Au fait, comment va le père Vincento ? Communiques-tu régulièrement avec lui ?";
			link.l1 = "Jusqu'à présent, oui, mais je pense qu'il n'est plus nécessaire de le faire. J'ai tous les composants du Gardien de la Vérité, ce qui signifie que je possède la clé de l'emplacement de Ksocheatem. Pour une raison quelconque, je ne suis pas pressé de rapporter mon succès à Sa Grâce.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Sois prudent, "+pchar.name+"«. Le Père Vincento a des centaines d'yeux et de mains. Des mains très longues...»";
			link.l1 = "J'ai traversé bien des épreuves ces derniers mois et à ce stade, je n'ai certainement pas peur, ni du père Vincento, ni de ses yeux et de ses mains. Peu importe. Il est temps pour nous de trouver Ksocheatem en utilisant les composants du Gardien. Sais-tu comment procéder ? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Pas vraiment. Ksatl Cha était assez vague. Je pense que l'Indien ne savait pas vraiment comment faire fonctionner le Gardien. Laisse-moi les composants et je vais essayer de comprendre cela. Reviens me voir dans deux jours et peut-être que j'aurai résolu cette énigme.";
			link.l1 = "Très bien, Gino. Je compte sur toi. Tiens, prends-les.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Tu peux être sûr qu'ils resteront sains et saufs avec moi.";
			link.l1 = "Je n'en doute pas. Eh bien, je ne te dérangerai pas pour l'instant, Gino. Bonne chance avec tes recherches !";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "En partie. Je veux dire, j'ai quelque chose, mais je ne sais pas comment faire pour que tout fonctionne vraiment. Essayons de résoudre ce casse-tête ensemble.";
			link.l1 = "Essayons ! Donnez-moi vos idées.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha a dit quelque chose comme ça : 'La Griffe du Chef fera apparaître la carte. La Flèche du Chemin montrera la direction des apparitions.";
			link.l1 = "Et qu'as-tu réussi à faire ?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "J'ai deviné comment faire en sorte que la carte se 'révèle' d'elle-même. As-tu jeté un œil à la carte des Deux Apparences ?";
			link.l1 = "Hm. Et y avait-il quelque chose de spécial ? Des contours obscurcis de l'archipel...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Prends-le et regarde encore. Sois attentif.";
			link.l1 = "Eh bien, faisons cela si tu insistes.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Tu n'as pas jeté un œil à la carte, "+pchar.name+"...";
			link.l1 = "Oui-oui, je vais le faire maintenant...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "J'ai vu. Je n'ai rien aperçu de nouveau. Juste quelques formes obscurcies d'îles et le continent. Que suis-je censé y voir ?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Attends une seconde. Maintenant, tu dois faire en sorte que cette carte se révèle. Prends le poignard et touche délicatement la carte avec son tranchant. Ne pousse pas, il faut éviter tout dommage. Prends le poignard. Et observe bien !";
			link.l1 = "Intéressant ! Voyons voir...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Eh bien, voyez-vous des différences maintenant ?";
			link.l1 = "Oui. Quand vous touchez la carte avec le poignard, deux marques de crânes apparaissent et elles sont toujours aux mêmes endroits...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Aux DEUX mêmes endroits, "+pchar.name+"C'est pourquoi on l'appelait la carte des Deux Apparences !";
			link.l1 = "Et qu'est-ce que cela signifie ?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Beaucoup, je pense... Mais d'autres énigmes arrivent ensuite. Je suppose que ces crânes sont les apparitions dont parlait Ksatl Cha. Donc la boussole doit indiquer la bonne direction vers Ksocheatem à partir d'eux. As-tu vu la boussole, "+pchar.name+"?";
			link.l1 = "Oui. Cela ressemble à une boussole navale ordinaire, mais elle se comporte étrangement, son aiguille tremble dans différentes directions ou commence à tourner à une vitesse folle.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Je pensais qu'en plantant la boussole sur les crânes, cela arrêterait son aiguille et indiquerait une direction claire sur la carte. Pour ce faire, je l'ai plantée sur un crâne, puis sur l'autre tout en touchant la carte avec le poignard.";
			link.l1 = "Et?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Infructueusement. La boussole n'a pas changé de comportement. La flèche continue de tourner follement. Il semble que je fais quelque chose de mal. Ou bien je n'ai pas compris correctement les paroles de Ksatl Cha.";
			link.l1 = "Donc le poignard et la carte fonctionnent et la boussole non?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "La Flèche de la Voie doit être opérationnelle à coup sûr, nous ne savons juste pas encore comment la faire fonctionner."+pchar.name+",  tu connais mieux que moi la géographie de l'archipel... Dis-moi, quels endroits sont révélés par la carte aux deux apparences ?";
			link.l1 = "Juste une seconde ! (jetant un coup d'œil)... Eh bien, eh bien... L'apparence à gauche est le continent occidental. Celle de droite ressemble à l'île de la Dominique. Quelque chose comme ça.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "Et dis-moi : Y a-t-il... quelque chose de remarquable dans ces endroits ?";
			link.l1 = "Que veux-tu dire?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Je ne suis pas sûr moi-même... Eh bien, quelque chose de spécial ?";
			link.l1 = "Gino, ne parle pas en énigmes. Explique-le simplement.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Je ne peux que supposer que ces crânes nous montrent des lieux réels. La Flèche du Chemin ne fonctionne pas lorsqu'elle est plantée sur les apparences de la carte. Peut-être qu'elle fonctionnera près des apparences géographiques réelles révélées par la carte ?";
			link.l1 = "Gino, tu es un génie ! Le Main occidental, la Dominique ? Les crânes sont trop grands pour montrer les emplacements exacts.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", faisons ce qui suit : Apportez-moi une carte papier de l'archipel, combinez-la avec la carte des Deux Apparences et marquez les apparences avec des croix. Peut-être cela vous donnera-t-il quelques suppositions ?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "J'ai cette vieille carte de l'archipel.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "J'ai cette belle carte de l'archipel.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "J'ai cette excellente carte de l'archipel.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "D'accord. Je te rapporterai une carte et nous continuerons...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Oh, allez, "+pchar.name+"! Ce parchemin de l'époque de Christophe Colomb n'est guère meilleur que la carte en peau. Je suis sûr qu'il y a quelque chose de mieux que ces déchets dans le monde. Apportez-moi une autre carte, une plus récente !";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Splendide ! Maintenant, marquez les lieux des apparitions dessus. Cela facilitera la construction des suppositions.";
			link.l1 = "Juste une seconde, Gino !";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "Pas question de gâcher une carte aussi magnifique avec nos marques. Vous en aurez besoin vous-même, "+pchar.name+". Apportez-moi une autre carte, une un peu plus modeste !";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "As-tu apporté une carte de l'archipel, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "J'ai cette vieille carte de l'archipel.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "J'ai cette belle carte de l'archipel.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "J'ai cette excellente carte de l'archipel.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Pas encore, mais je l'ai déjà commandé. Bientôt je l'aurai et nous continuerons...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = " ";
			link.l1 = "Fait... J'ai créé les marques, mais c'est toujours des informations inexactes. Le premier endroit est quelque part au nord-ouest de Blueweld. Le second est au centre de l'île de la Dominique.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Des idées ?";
			link.l1 = "Non. Mais je pense que nous devrions amener la Flèche du Chemin là-bas et observer son comportement. Bien sûr, c'est comme chercher une aiguille dans une botte de foin, mais nous n'avons pas de meilleures idées de toute façon.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Je suis d'accord avec toi, "+pchar.name+"Me laisseras-tu naviguer avec toi ?";
			link.l1 = "Seriez-vous intéressé à vérifier vos suppositions ? Ce serait un honneur de vous avoir sur le pont de mon navire, Gino. Faites vos bagages !";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "Ça ne prendra pas beaucoup de temps. Je serai prêt dans quelques heures. Tenez, prenez la Flèche du Chemin.";
			link.l1 = "Bienvenue à bord !";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Oui-oui, "+pchar.name+", Je me prépare. Je serai prêt bientôt.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "Et alors, "+pchar.name+" , avons-nous de la chance dans nos recherches ?";
			link.l1 = "Nous avions raison. C'est ça. L'idole indienne est l'une des apparitions.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh ! Cela doit être l'une de ces idoles censées téléporter les gens à Tayasal ! Je te parlais d'elles, tu te souviens ? Alors, où pointe la Flèche du Chemin ?";
			link.l1 = "Il est orienté nord-ouest. J'ai marqué la direction sur une carte. Bien que la ligne tracée traverse presque toute la mer des Caraïbes. Nous devons trouver une autre apparition sur la Dominique pour trouver Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Je suis sûr que nous trouverons un autre idole là-bas... es-tu d'accord avec mon hypothèse, "+pchar.name+"?";
			link.l1 = "Je le fais, Gino. Ne perdons pas de temps et commençons à chercher.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "Et alors, "+pchar.name+", avez-vous trouvé quelque chose d'intéressant ?";
			link.l1 = "Nous avions raison. C'est ça. L'idole indienne est l'une des apparitions.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Oh! Ce doit être l'une de ces idoles censées téléporter les gens à Tayasal! Je vous en parlais, vous vous souvenez? Alors, où pointe la Flèche du Chemin?";
			link.l1 = "Nord-ouest. J'ai marqué la direction sur une carte. Bien que la ligne tracée traverse presque toute la mer des Caraïbes. Nous devons trouver une autre apparition sur le continent pour trouver Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "Alors, quoi, "+pchar.name+", avez-vous trouvé la deuxième idole ?";
			link.l1 = "Oui. J'ai tracé la direction indiquée par la Flèche du Chemin. Maintenant nous connaissons l'emplacement de Ksocheatem, ce n'est pas l'emplacement exact mais nous savons où chercher ! Je vais explorer toute la zone où les lignes se croisent et je trouverai cette maudite île !";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "Je suis ravi d'entendre tant d'enthousiasme dans ta voix. Mais nous devons bien nous préparer pour l'expédition à venir, il est incertain ce que nous y affronterons. Je doute que nous y recevions un accueil chaleureux...";
			link.l1 = "Est-ce que tu t'inquiètes pour quelque chose de précis ou exprimes-tu simplement des préoccupations?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Réfléchissez-y, "+pchar.name+".. Ksocheatem a été créé par la magie maya réalisée par Kanek. Ce n'est pas une formation naturelle et elle possède des pouvoirs maléfiques et destructeurs. On ignore ce qui nous attend là-bas, je doute que nous y trouvions soleil, mers paisibles, putains et vent calme.";
			link.l1 = "D'accord, Gino. Je considérerai tes paroles et je me préparerai pour l'expédition. Je vais préparer mon navire et m'occuper des potions et des munitions...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Une décision très sage. Eh bien, retournons-nous au navire ?";
			link.l1 = "Bien sûr ! Allons-y !";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Nous sommes arrivés, "+pchar.name+"! Euh, le vent hurle !";
			link.l1 = "Oui, Gino, tu avais raison, il n'y a pas de soleil pour nous accueillir... Je ne vois pas non plus de putains. En fait, on ne sait pas du tout ce qui nous attend ici.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Eh bien, vous avez choisi un endroit si mauvais pour accoster, Capitaine ! Juste des rochers et des falaises partout ! Et comment allez-vous pénétrer à l'intérieur de l'île à partir d'ici ?";
			link.l1 = "Je n'ai pas vu d'autre baie convenable pour accoster sur cette île à cause de cette maudite tempête ! Qu'importe, c'est mieux que rien. Je vais réussir à me frayer un chemin parmi ces rochers, j'ai connu pire. Ne panique pas, l'ami !";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Je n'aime pas cette île, "+pchar.name+" ! C'est effrayant. Et cette tempête doit être attachée à l'île. Cet endroit est condamné, c'est certain !";
			link.l1 = "Je n'aime pas vraiment cet endroit non plus, Gino ! Mais cette île existe bel et bien, ce qui signifie que l'histoire de Kukulcan est vraie. Nous serons tous en danger s'il parvient à atteindre Tayasal avec le Masque...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Essayez de trouver le Masque, Capitaine ! Il est plus important que tous les trésors du monde ! Il doit être quelque part par ici ! Une fois que nous l'aurons, nous détruirons les plans de Kukulcan et nous ne le laisserons pas altérer le passé !";
			link.l1 = "Et à quoi ressemble ce masque, le sais-tu ?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Aucune idée ! Mais je pense que tu le reconnaîtras, c'est un ancien artefact indien, difficile à confondre avec autre chose !";
			link.l1 = "Je vois. Je garderai les yeux ouverts ! Bien, Gino, retourne à bord du navire ! Tu n'as pas besoin de te promener sur l'île, ta tête est trop précieuse pour la risquer !";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Je ne vais pas mentir, Capitaine, je suis un piètre combattant et je ne me sens pas à l'aise dans cet endroit. Voulez-vous écouter un conseil ? Chaque composant du Gardien est connecté à la magie de cette île. Ksatl Cha a mentionné que le poignard a du pouvoir sur les habitants locaux, je ne sais pas ce qu'il voulait dire par là.\nJe resterai à bord. Venez me voir là-bas si vous avez besoin de mon aide.";
			link.l1 = "Bien. Et maintenant, souhaite-moi bonne chance, Gino !";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Bonne chance, "+pchar.name+"Que Dieu te favorise et te préserve !";
			link.l1 = "... ";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Comment vas-tu, "+pchar.name+"Besoin d'un conseil ?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Cette île maudite grouille de morts-vivants et ces foutus squelettes sont étonnamment coriaces. Je n'ai aucune idée de comment les combattre.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Si tu prends à gauche au croisement, tu finiras par arriver à la caverne. Mais où devrais-je aller ensuite ? Je crains que la caverne ne soit une impasse...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "J'ai trouvé mon chemin à l'intérieur de la caverne humide, tu peux plonger dans sa partie sous-marine. Mais je ne vois aucune sortie de là...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Si tu prends à gauche au carrefour, tu arriveras à la caverne. Mais où devrais-je aller ensuite ? Je crains que la caverne ne soit une impasse...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "Il y a un endroit dans la grande caverne où tu peux plonger dans la partie inondée. Mais il semble qu'il n'y ait pas d'issue là-bas...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Tout va bien jusqu'à présent, Gino, je vais bien.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = " Ksatl Cha a mentionné la Griffe du Chef. Essayez de l'utiliser contre les squelettes, l'Indien a dit que ce poignard a un pouvoir sur les habitants de Ksocheatem.";
			link.l1 = "Je vais essayer, c'est sûr !";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "Et à quoi ressemble cette grotte ?";
			link.l1 = "Eh bien, il y a une petite grotte dans un rocher, elle est humide et l'eau oscille au fond comme le ressac...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Si l'eau ondule, alors la caverne a une connexion avec la mer et elle ne peut pas être une impasse. Cherchez un passage, il doit être là.";
			link.l1 = "En route...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "S'il existe un passage vers la caverne inondée à partir de la principale et si l'eau ondule comme une houle dans la caverne principale, alors la caverne inondée possède un second passage. Fouillez-la mieux, mais soyez prudent ou vous vous noyerez.";
			link.l1 = "Je vais plonger...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "Et à quoi ressemble cette caverne ?";
			link.l1 = "Eh bien, c'est assez grand avec quelques cavernes, c'est humide et il y a un petit trou avec de l'eau stagnante...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Si l'eau est calme, alors la grotte n'est pas connectée à la mer et cela pourrait être une impasse.";
			link.l1 = "Je pensais la même chose. J'ai cherché là-bas pendant longtemps et il n'y a qu'une seule entrée qui est aussi une sortie...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Si l'eau reste encore dans la caverne, alors, peut-être, tu as raison. Cherche un peu plus, mais ne sois pas triste si tu ne trouves rien. Il est probable que ce soit une impasse.";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Les navires espagnols sont sur nous ! Ce n'est pas le meilleur moment pour parler !";
			link.l1 = "Oui, bien sûr...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Tes yeux heureux me disent que tu as trouvé ce que tu cherchais.";
			link.l1 = "Oui. Les trésors de Miguel Dichoso et le Masque de Kukulcan. Désormais, son incarnation ne pourra jamais changer l'avenir !";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Incroyable ! Tu es un héros, "+pchar.name+"...";
			link.l1 = "Gino, es-tu sûr que cela suffira pour arrêter Kukulcan ?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Selon Ksatl Cha - oui. Et il citait Urakan. Son père Kanek est celui qui a commencé tout ce bazar. Des doutes ?";
			link.l1 = "J'ai été accueilli dans la baie par un invité du passé - Alonso de Maldonado. Il était à Tayasal quand Kanek réalisait le rituel pour créer le Gardien de la Vérité. Il a été entraîné dans le trou spatio-temporel, mais il est resté en vie... Jusqu'à aujourd'hui.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Il a dit que je dois fermer le portail lui-même pour protéger notre monde définitivement. Pour ce faire, je dois détruire le Masque sur un autel à Tayasal.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "Et tu vas aller à Tayasal ? C'est de la folie !"+pchar.name+", tu as le masque et l'incarnation de Kukulcan ne pourra rien faire ! Et Kanek lui-même en est convaincu ! C'est pourquoi Urakan a envoyé Ksatl Cha pour trouver Ksocheatem - pour récupérer le Masque et le détruire.";
			link.l1 = "Et si cet Urakan avait l'intention de détruire le masque à Tayasal ?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", jusqu'à présent, un seul homme a réussi à échapper vivant de Tayasal et c'était Miguel Dichoso. Aussi Maldonado, mais c'était une exception. Même si l'incarnation de Kukulcan retourne dans le passé, il se fera tuer par les anciens Mayas !";
			link.l1 = "Et s'ils ne le tuent pas mais le reconnaissent ?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Alors, tu prévois une expédition à Tayasal ?";
			link.l1 = "Je ne sais pas, Gino. Je ne sais vraiment pas...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Alors réfléchissez-y, pourquoi feriez-vous cela ? Vous avez entendu mon avis. C'est à vous de décider maintenant..."+pchar.name+", me conduiras-tu à St. John's ?";
			link.l1 = "Bien sûr, Gino. Levons l'ancre dès que possible. J'en ai assez de cette île horrible.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Serons-nous bientôt de retour chez nous, "+pchar.name+"?   Mes fioles et mes tubes me manquent terriblement...";
			link.l1 = "Oui-oui, Gino, bientôt nous serons à Antigua.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Je suis ravi que nous soyons enfin de retour ! Je ne peux pas imaginer comment vous, marins, passez autant de temps sur vos navires...";
			link.l1 = "C'est une question d'habitude, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Je m'étendrai sur mon lit debout sur un sol solide avec grand plaisir... J'espère, "+pchar.name+", que vous avez épargné votre tête de l'idée de visiter Tayasal ?";
			link.l1 = "Je ne sais pas encore, Gino. Pour être honnête, je ne suis toujours pas sûr.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Détruisez le masque de Kukulcan et vivez sans soucis, Capitaine. Si vous le souhaitez, nous dissoudrons le masque dans l'acide le plus puissant que j'ai. Je ne garderai pas de rancune pour une telle affaire.";
			link.l1 = "Tu sais, je vais attendre un peu. Nous aurons toujours le temps de le détruire.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "C'est ton choix. Si tu décides d'épargner ce monde de cet artefact - viens me voir. Gratitude pour ce merveilleux voyage, Capitaine !";
			link.l1 = "À tout moment, Gino. À la prochaine !";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vous êtes un "+GetSexPhrase("voleur, Monsieur! Gardes, attrapez-le","voleuse, fille! Gardes, attrapez-la ")+"!!!","Regardez-moi ça ! Dès que je me suis perdu dans mes pensées, vous avez décidé d'inspecter ma malle ! Attrapez le voleur !!!","Gardes ! Vol ! Attrapez le voleur !!!");
			link.l1 = "Sacrebleu !";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
