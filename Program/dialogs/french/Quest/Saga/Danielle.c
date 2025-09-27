// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Attends, beau gosse ! Je pense que nous devrions parler.";
			link.l1 = "Est-ce que je vous connais ? Quoi qu'il en soit, j'ai toujours quelques heures de plus pour une dame.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Ne fais pas encore de plans, Capitaine. Trouve-toi une jeune fille d'apparence idiote pour quelques heures de plus. J'ai des affaires pour toi. Je suis mariée en fait. Mon mari s'appelle Nathaniel Hawk.";
			link.l1 = "N'est-ce pas quelque chose ! Alors tu dois être ce gars... eh, Dannie Hawk, monsieur Svenson t'a mentionné.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "En chair et en os. Oui, je sais que le Démon de la Forêt n'a pas grande estime pour moi, le sentiment est réciproque, mais il a dû te prévenir que je ne porte pas mon sabre uniquement parce qu'il est joli. Alors, allons droit au but, fiston !\nJe suivais Svenson et ses visiteurs pendant un certain temps parce que c'est lui qui a envoyé mon mari dans la jungle pour y mourir. Je pensais qu'il travaillait avec Jackman, mais maintenant je vois que ce n'est pas le cas. Je me cachais sous la fenêtre pendant votre conversation. Je n'ai pas pu tout écouter, mais j'ai appris beaucoup d'informations utiles.\nEs-tu vraiment prêt à retrouver mon mari et botter le cul de Jackman ? Ou est-ce que tu faisais seulement du vent ?";
			link.l1 = "L'espionnage est mauvais, Madame Hawk. Mais je vous pardonnerai si vous me parlez d'une manière plus respectueuse. Que je cherche Hawk ou non, cela ne concerne que moi. Parlez si vous avez quelque chose d'utile à dire ou laissez-moi tranquille si ce n'est pas le cas. Je ne demanderai pas deux fois.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "« A-ha, quel fougueux ! Allez, Capitaine... Mon tempérament ne vous met pas vraiment à l'aise, c'est certain. Je vois que vous n'êtes pas un lâche et vous connaissez votre valeur. Alors... faisons connaissance. Je vous promets que je serai prudent avec ce que je vous dirai. J'ai besoin de vous et vous avez besoin de moi. Nous partageons des objectifs. Prenez-moi dans votre équipage et vous ne le regretterez pas. Je vous servirai avec bonne foi et fidélité jusqu'à ce que nous trouvions Nathan, vous avez ma parole. »";
			link.l1 = "Considérez-vous accepté... Dannie. Svenson m'a dit que vous avez déjà commencé à chercher votre mari. Avez-vous trouvé quelque chose d'intéressant ?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Pas grand-chose, mais assez pour accuser Jackman de mensonge. Le salaud a dit que les gardes de la mine, ceux que mon Nathan a affrontés, ne prenaient pas de prisonniers. Et bien qu'il soit vrai que personne n'a vu le cadavre de mon mari à la baie, comment auraient-ils pu, puisqu'il a en fait été emmené aux mines comme prisonnier. Oeil-de-Serpent, un chaman du peuple Miskito, l'y a trouvé.\nIl a aussi arrangé son évasion. Mais où se trouve mon mari maintenant, cela reste inconnu. Le chaman marmonnait quelque chose à propos d'un certain Kukulcan qui l'aurait dévoré, mais je n'ai rien compris. En plus, le peau-rouge a bien fait comprendre que les femmes blanches ne sont pour lui qu'une plaisanterie. Vous devriez lui parler, peut-être sera-t-il plus loquace.";
			link.l1 = "C'est déjà ça ! De telles nouvelles me rendent plus joyeux. Où puis-je trouver cet Indien ?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Il y a un village au cœur de la jungle. Nous devons débarquer à la baie d'Amatique et aller vers l'ouest à travers la jungle. Je te montrerai le chemin si tu ne le trouves pas toi-même. Un idole de pierre se trouve non loin du village et les sauvages le vénèrent comme leur dieu. J'y suis allé plusieurs fois. Rien de spécial en vérité. Juste une simple pierre couverte de mousse.";
			link.l1 = "Intéressant. Très bien, allons-y. Nous parlerons au chaman et nous verrons quoi faire ensuite. Prêt ?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Bien sûr ! Bien entendu, je suis prêt. J'ai voyagé tout le temps depuis que j'ai quitté Maroon Town. De plus, je ne veux pas être simplement un de vos passagers.";
			link.l1 = "D'accord. Allons à mon navire.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Ouais-oui, Capitaine !";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = "Bonjour, ami."+pchar.name+"Viens donc ! Je vais te montrer l'idole de pierre dont parlait le chaman indien. Juste un pilier de pierre ordinaire. Allons-y !";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Eh! Regarde, ce n'est qu'une statue de pierre. Rien de spécial...";
			link.l1 = "Je vois... Bien que la silhouette en haut soit un peu sinistre, n'est-ce pas ?";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Tous les statues indiennes sont effrayantes et ont l'air maléfique. J'ai déjà vu quelque chose de similaire. Elles sont toutes pareilles. Quoi qu'il en soit, allons-y, le village est à proximité !";
			link.l1 = "Allons-y !";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Alors, que dis-tu, "+pchar.name+" ? Qu'est-ce que ce ventriloque peau-rouge t'a raconté ? As-tu tiré quelque chose de ses paroles philosophiques ?";
			link.l1 = "Étais-tu encore en train d'espionner, Dannie ?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Eh bien... un peu. Vous savez, nous les femmes, nous sommes juste comme ça. Mais vous devez comprendre - je m'inquiète simplement pour mon mari. Je l'aime vraiment. Et alors si j'écoute aux portes ? Quoi qu'il en soit, avez-vous obtenu quelque chose d'utile ?";
			link.l1 = "J'essaie de réfléchir... ce n'était pas facile de comprendre Oeil de Serpent. Cependant, il semble que l'idole que nous avons vue en entrant dans le village soit une sorte de portail magique qui peut téléporter les gens.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Ne me regarde pas comme ça. Ce n'est pas mon idée et jusqu'à présent je n'ai pas de problèmes avec ma tête. Tu m'as demandé ce que le chaman m'a dit, alors je te le dis.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Je vous prie de m'excuser. Je ne vous regarderai plus ainsi. Continuez.";
			link.l1 = "Il a dit que lorsque Nathan fut presque attrapé par ses poursuivants, l'Indien lui montra la statue comme moyen de secours, l'appelant Kukulcan et disant qu'elle avait dévoré Nathan vivant et l'avait recraché ailleurs. Pour faire simple, il semble que Nathan ait été téléporté par la statue.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Dieu, qu'est-ce que... Nathan et moi avons déjà été dans un tel pétrin auparavant et maintenant ça recommence. Nous avons eu assez d'aventures avec ce temple indien rempli de magie maya...";
			link.l1 = "Qu'as-tu dit à l'instant ?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ah, ce n'est rien, "+pchar.name+", cela n'importe guère. Juste des souvenirs de ma jeunesse fougueuse. Mais comment Nathan a-t-il pu faire cela ? Je veux dire, se téléporter ? Nous étions juste à côté de cet idole, je tournais autour et le touchais... ce n'est qu'une pierre !";
			link.l1 = "Le Serpent-Oeil m'a dit que l'idole prend vie à minuit. C'est seulement alors qu'elle commence à briller d'une couleur dorée, lorsque l'esprit de Kukulcan y pénètre. C'est le moment où tu ne devrais pas la toucher. Ou inversement, tu devrais...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Effrayant... Et maintenant ? Attendons minuit et allons dans la jungle ensuite ?";
			link.l1 = "Non. Le chaman a dit que l'idole ne se contente pas de téléporter les gens, mais qu'elle dévore aussi leurs vies. D'après ce que j'ai compris, il voulait dire qu'elle draine leur santé. Oeil de Serpent est passé à travers ces statues trois fois et s'est soigné avec une potion unique après chaque téléportation.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Lui as-tu demandé cette potion ?";
			link.l1 = "Bien sûr. Mais d'abord, il ne reste que trois flasques et, ensuite, il a exigé trois amulettes en échange.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Que dirais-tu de faire ça sans la potion ? Allons à la statue la nuit et touchons-la...";
			link.l1 = "Trop risqué. J'admets que l'Indien est un peu dérangé et nous joue des tours, mais il n'a pas l'air d'un psychopathe, donc je crois qu'il dit la vérité. Je me souviens que tu me parlais de magie indienne... Doutes-tu de son existence ?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Oui, je l'étais. Je n'en doute pas car je l'ai vu de mes propres yeux. Donc, je suppose que tu as raison, il n'y a pas de raison de prendre ce risque.";
			link.l1 = "Exactement. C'est pourquoi nous trouverons d'abord les amulettes, puis nous obtiendrons cette merveilleuse potion du chaman et nous irons à la statue. J'irai. Seul.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Pourquoi cela? Et moi alors?";
			link.l1 = "Tu resteras sur mon navire et tu seras en charge pendant mon absence. N'essaie même pas de discuter, Dannie. Il n'y a que trois flacons de la potion. On ne sait pas où mène le portail, dans le cas où le chaman a raison et que cette chose fonctionne réellement. Peut-être que je ne pourrai même pas y trouver Nathan.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Tu es exactement comme Nathan. Tous les hommes sont pareils... D'accord, j'accepte.";
			link.l1 = "Il est bon que nous nous comprenions. Allons-y maintenant, nous devons trouver les amulettes.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "Alors, quoi ? As-tu récupéré les potions ?";
			link.l1 = "Oui. J'ai les potions et quelques instructions. La seule chose qui reste à faire est d'aller à l'idole à minuit et de la toucher.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "As-tu peur ?";
			link.l1 = "Oui. J'ai peur que le chaman ne soit qu'un fou et qu'aucune téléportation n'ait lieu.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Eh bien, eh bien... N'as-tu vraiment pas peur? Même pas un tout petit peu?";
			link.l1 = "Dannie, ne me pousse pas... Si tu veux vraiment savoir, alors certes, je ne me sens pas très confiant, je dois l'avouer.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Je vais t'accompagner.";
			link.l1 = "Vas-tu encore commencer à te disputer ? Je croyais que nous avions un accord...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Tu m'as mal compris. Je resterai seulement près de toi. Je devrai m'assurer que la statue fonctionne... ou qu'elle ne fonctionne pas.";
			link.l1 = "Je n'ai aucune objection. Mais n'ose même pas me suivre si la statue m'«avale». Tu m'entends?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Je le fais. Je promets de ne pas vous suivre... Capitaine.";
			link.l1 = "Bien. Et, Dannie, il semble que tu n'es pas aussi garce qu'on le dit.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Tu ne me connais pas très bien, "+pchar.name+"Mais ne parlons pas de cela maintenant.";
			link.l1 = "Ne tardons pas... Eh bien, nous devrions nous préparer pour notre expédition nocturne !";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Regarde, "+pchar.name+" ! Je jure par tout ce qui est sacré, il y a une lumière étrange au-dessus de la statue !";
			link.l1 = "Il semble que le chaman ne mentait pas. Et, si l'obscurité ne me trompe pas, le sommet de la statue n'a plus l'air si pierreux.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Exactement... On dirait qu'il est fait d'or pur ! Incroyable !";
			link.l1 = "Le moment est venu, Dannie. Souhaite-moi bonne chance et croise les doigts pour moi. Ne t'approche pas de l'idole ! Reste ici.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Bonne chance, "+pchar.name+". Espérons que cela fonctionnera... As-tu préparé la potion du chaman?";
			link.l1 = "Oui, je l'ai ici. Tout ira bien, Dannie. Eh bien, j'y vais! (Appuyez sur T pour activer l'idole)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Merde! Quelle sorte de monstre es-tu, nom de dieu?! Va te faire foutre! J'ai vu pire créature dans ma vie, y compris Van der Decken lui-même! Maintenant je vais te donner ce que tu demandes!";
			link.l1 = " (faiblement) Dannie, attends ! Arrête ça ! Maintenant !";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(faiblement) Van der Decken ? Uh-ha-ha-ha ! Ce ver me sert déjà ! Maintenant, c'est ton tour ! Incline-toi devant moi, fidèle serviteur ! Tu mèneras mon armée des morts !";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Allez-vous-en ! Cela ne peut pas se passer maintenant !";
			link.l1 = "(faiblement) Dannie, attends ! Arrête ça ! Maintenant !";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ah?! Qu'as-tu dit?! Dannie?";
			link.l1 = "(faiblement) Arrêtez ça immédiatement ! Rengainez votre sabre ! Laissez-moi enlever cette chose !";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Bon sang, tu sonnes comme un monstre... "+pchar.name+"?! ";
			link.l1 = "(faiblement) Oh-oh... Tu ne dis pas !";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Nom de Dieu, tu m'as presque fait mourir de peur ! J'étais à deux doigts de t'abattre avec mon sabre !";
			link.l1 = "J'ai vu ça... et pourquoi es-tu si fougueux, hein ?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "C'est bien qui je suis... Oh, mon cœur bat encore à tout rompre...";
			link.l1 = "Dannie, où sommes-nous maintenant ? Pas loin du village Miskito, n'est-ce pas ?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Où d'autre pourrions-nous être ! C'est la statue qui t'a fait disparaître. C'était spectaculaire ! Je m'en souviendrai pour le reste de ma vie.";
			link.l1 = "Je vois, tu m'attends ici depuis tout ce temps ?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Dis-moi, qu'aurais-je pu faire d'autre? Après que la statue t'ait englouti, je ne pouvais qu'espérer qu'un jour elle te recracherait. De plus, Œil-de-Serpent a dit que c'est probablement ce qui arriverait.\nJ'ai vécu avec les Miskito et surveillé l'idole tous les jours. Pourquoi parlons-nous même de ces balivernes? Dis-moi! Que s'est-il passé là-bas? Où étais-tu passé?";
			link.l1 = "Dannie, cette histoire est bien trop longue, j'ai vu tant de choses... Mais pour te soulager, je te dirai que j'ai trouvé Nathaniel !";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "As-tu trouvé Nathan ? Où est-il ? Et comment va-t-il ?!";
			link.l1 = "Je ne vais pas mentir - il est vivant, mais il se sent vraiment très mal. Il n'avait pas de potion des Comanches et l'idole a drainé toute sa santé. Il est allongé dans une cabine d'un vieux navire brisé sur l'étrange Île des Navires Abandonnés. J'y ai été téléporté aussi, donc Œil de Serpent avait raison !";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Pauvre Nathan... Où est cette maudite île ? Comment y arriver ? Uniquement par l'idole ? Je vais essayer d'acheter toutes les potions de santé possibles aux Miskitos et y aller cette nuit ! Je m'y rendrai d'une manière ou d'une autre...";
			link.l1 = "Arrêtez ! Attendez ! Nathan est malade, mais sa vie n'est pas menacée. Un gars s'occupe de lui et le nourrit. Si vous passez par l'idole, vous ruinerez votre santé et l'île est vraiment dangereuse. C'est trop risqué !";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Alors, que suggérez-vous ? Ne rien faire pendant que Nathan souffre ou meurt peut-être ?";
			link.l1 = "Arrête d'être hystérique. Premièrement, je t'ai dit que Nathan est malade mais pas mourant. J'ai parlé avec lui. Deuxièmement, je vais naviguer vers l'île et tu viendras avec moi.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Sais-tu où se trouve cette île ?";
			link.l1 = "Bien sûr, je le fais ! J'y ai trouvé non seulement Nathan mais aussi Shark Dodson. J'ai obtenu les coordonnées approximatives de l'île et les instructions de navigation pour contourner les récifs qui l'entourent. Et maintenant, nous retournons à mon navire pour voguer vers Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Dans quel but ? Pourquoi ne pouvons-nous pas voguer directement vers l'île maintenant ?";
			link.l1 = "Dannie, je dois organiser une expédition. Il y a un énorme manque de provisions sur l'île, donc j'achèterai autant de nourriture que possible. Ensuite, je devrai choisir un navire pour m'y rendre, car tous les navires ne pourront pas contourner les récifs de l'île. Et je veux aussi parler à Svenson d'abord...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Ça ne prendra pas très longtemps à préparer. L'île n'est pas loin d'ici, elle est au nord-ouest de La Havane, à l'est du golfe du Mexique.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "D'accord... faisons cela alors. Vous avez trouvé Nathan et c'est le plus important. Merci ! Se sent-il mal là-bas ?";
			link.l1 = "Eh bien... il est malade. Et en plus de cela, il est aussi déprimé et désespéré. Tu lui manques. Et oui, Nathan m'a demandé de te dire qu'il t'aime beaucoup.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(essuie une larme) Vieux fou ! Il ne m'a jamais écouté... "+pchar.name+", allons vers votre navire ! Je veux y naviguer aussi vite que possible !";
			link.l1 = "Bien sûr, Dannie. Et je te raconterai mes aventures. Allons-y !";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Je n'ai jamais vu un endroit comme celui-ci auparavant. Toute l'île est faite de navires !";
			link.l1 = "Je t'en ai parlé, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Mais maintenant je peux le voir de mes propres yeux. Quoi qu'il en soit, dis-moi où trouver Nathaniel ?";
			link.l1 = "Il est à l'intérieur de l'un des navires. Mais vous devez nager jusqu'à là.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Je m'en moque. Dis-moi comment rejoindre ce navire.";
			link.l1 = "Dannie, calme-toi. Toi et Nathan avez attendu longtemps alors ayez juste un peu plus de patience ! Je vais te mener à lui, tu ne le trouveras jamais par toi-même. Je ne veux pas que tu tombes sur les Narvals ou les Rivados, tu commenceras à te disputer avec eux et ça ne finira pas bien.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Très bien, allons-y alors. Je te suivrai.";
			link.l1 = "N'oublie pas que nous devrons beaucoup nager.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "C'est bon, je peux m'en occuper.";
			link.l1 = "Ravi de l'entendre... Vous verrez bientôt votre mari !";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan ! Bon sang ! Mon amour...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Jesus, regarde-toi... Pourquoi t'es-tu fait ça à toi-même ?!.. (pleurant) Tu ne m'écoutes jamais, jamais ! Je t'ai dit de ne pas aller dans cette selva ! Mais tu y es allé quand même ! Pourquoi Nathan ?!";
			link.l1 = "Dannie... Je suis désolé. Je n'avais pas le choix, tu le sais...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Je le sais ! Oh, mon Dieu, chérie... qu'est-ce qui t'est arrivé ! (en larmes) Ça va aller, ma chérie, tout va bien se passer... Je suis là. Nous allons t'amener chez les Miskitos, chez Œil-de-Serpent."+sld.name+"  m'a dit que le chaman pourra te guérir. Nous avons un navire... Tout ira bien !";
			link.l1 = "Dannie, ma chère... mon amour ! Ta présence ne m'a guéri qu'à moitié. Nous irons où tu dis. Si c'est à Serpent, alors à lui.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Emballe tes affaires. Oh, je suis si bête... Il n'y a rien à emballer à part des bouteilles vides. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = "Bonjour, mon ami."+pchar.name+" ... pardonne-moi ainsi que Nathan pour la scène.";
			link.l1 = "Dannie ! Te pardonner de quoi ? Tout va bien. As-tu honte de tes sentiments ?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Non, je ne suis pas... C'est juste...";
			link.l1 = "Personne ne saura jamais rien de cette scène. Je le promets. Et personne ne saura ce qui est arrivé à Nathan. Les pirates de Maroon Town verront un Nathaniel Hawk fort et redoutable !";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Merci, "+pchar.name+"! Je vous dois une fière chandelle... Je vais emmener mon mari au navire. Ne vous inquiétez pas, je m'arrangerai pour l'y amener, je me souviens du chemin. Je le mettrai dans un lit et je resterai avec lui. Nous mettrons le cap sur l'Œil du Serpent une fois que vous aurez terminé tout ce que vous devez faire ici. Je crois en sa capacité à guérir Nathan.";
			link.l1 = "D'accord, Dannie. Nous ne resterons pas ici longtemps de toute façon. Es-tu sûr que tu n'as pas besoin d'aide ?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Je suis sûre. Nous atteindrons le navire. Ne t'en fais pas, je ne laisserai pas mon mari mourir !";
			link.l1 = "Dannie, tu es... merveilleuse !";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(essuyant une larme) Va... juste va, "+pchar.name+" ... et s'il te plaît, ne perds pas de temps ici ! ";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "Alors quoi ? Va-t-il guérir mon mari ? Dites-moi qu'il va le guérir !";
			link.l1 = "Dannie, Nathan devra rester ici. Seul. Le chaman a demandé à ne pas déranger ses rites. Cela te concerne aussi. Il a promis de guérir Nathaniel en un mois.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Tu sais, "+pchar.name+", maintenant je peux enfin respirer librement à nouveau. Je crois fermement que le chaman ramènera mon mari à son état normal. Je laisserai Nathan ici sans hésitation car si Oeil de Serpent ne peut pas le guérir - personne ne le pourra.";
			link.l1 = "Tout ira bien, Dannie. Oeil de Serpent ne m'a jamais menti. Je lui fais confiance.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Moi aussi. Je vais rester avec toi pour un moment, "+pchar.name+", es-tu d'accord avec ça ? Nous devons encore trouver ce salaud de Jackman, après tout, il est responsable de tous nos ennuis. Il a organisé l'embuscade ! Il a pris la place de Nathan à Maroon Town ! Il a volé notre frégate 'Centurion' !";
			link.l1 = "D'accord. Nous devons nous occuper de Jackman. Aucun d'entre nous n'est en sécurité tant que Jackman n'est pas mort. Cependant, il ne sera pas facile de le tuer.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Tu as des projets, "+pchar.name+"?";
			link.l1 = "Pas encore. Je dois aller voir Jan Svenson et lui demander conseil. Faisons les choses une par une, nous devons promouvoir "+sTemp+" d'abord chef de la Confrérie de la Côte. Donc, nous devons obtenir un vote de chaque baron pirate pour cela.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "D'accord, Allons chez Svenson. Écoutons ce que ce vieux schnock a à dire...";
			link.l1 = "Tu sais, tu ne devrais pas être si négatif envers Jan. En fait, ce serait bien mieux si tu faisais la paix avec lui... après tout, nous partageons tous le même objectif !";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Mais seulement parce que je vous respecte... D'accord, "+pchar.name+", je suis désolé. Je ne voulais pas insulter Svenson, je suis juste nerveux. Cela ne se reproduira plus.";
			link.l1 = "Bien. Dannie, tout ira bien. Je te le promets !";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Je vous fais absolument confiance, "+pchar.name+"Allons chez Svenson ?";
			link.l1 = "Allons-y, Dannie !";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Oui ? Je vous écoute. Comment puis-je vous aider ?";
			link.l1 = "As-tu des idées sur où Jackman pourrait se cacher ? Tu connais mieux que moi ce salaud. Peut-être a-t-il un endroit, une base...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Que diable si je le sais ! Jacob a toujours été très secret. Je n'ai jamais entendu parler d'une cachette à lui. Il vaut probablement mieux essayer de réfléchir logiquement... Relisons la lettre que vous avez reçue de Knive. Nous pourrions y trouver un indice.";
			link.l1 = "Essayons...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Eh bien... ça mentionne Isla Tesoro et un certain testament... Cela te dit-il quelque chose ?";
			link.l1 = "Moi et Jan pensons que Blaze Sharp a été tué par Jackman sur Isla Tesoro et Shark en a été accusé. Et un testament... une garce... cela doit concerner Helen... Bon sang, comment ai-je pu ne pas le comprendre plus tôt ! Cet enfoiré doit naviguer près d'Isla Tesoro !";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Ne perdons pas notre temps alors, "+pchar.name+"?";
			link.l1 = "Oui. Allons à Isla Tesoro. Le vieux 'Marlin' nous aidera dans cette attaque.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Ce salaud est enfin mort... Je n'arrive pas à y croire - je me tiens à nouveau sur le pont du 'Centurion' ! Je connais chaque clou ici et il semble que le navire m'ait reconnu aussi.";
			link.l1 = "Elle est de nouveau à toi, Dannie. À toi et à Nathaniel.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "Tu ne peux même pas imaginer à quel point je suis ravi. Nathaniel parlait souvent de notre navire, il sera heureux de savoir qu'il est de nouveau à nous.";
			link.l1 = "Que vas-tu faire maintenant, Dannie ?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Moi ? Je vais prendre le navire jusqu'à Sharp town, engager au moins l'équipage minimum et naviguer vers Blueweld. Je demanderai à Jan Svenson de veiller sur le 'Centurion', d'aller chez les Miskito et d'attendre là-bas jusqu'à ce que Snake Eye ait guéri mon mari.";
			link.l1 = "Tu vas vraiment rendre visite à Jan Svenson ? Je suis surpris...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = "Bonjour, mon ami."+pchar.name+", c'est tout votre mérite. J'ai réfléchi à vos paroles : 'nous partageons tous le même objectif'. Vous vous souvenez ? Je veux faire la paix avec Svenson, après tout, il m'a aidé à ramener Nathan. Il est temps de cesser de se disputer.";
			link.l1 = "Sages paroles, Dannie ! Nathaniel pourra reprendre sa position à Maroon Town dès qu'il se sentira mieux.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Peut-être... mais vois-tu, baron pirate est une fonction élective. Que se passera-t-il si les autres décident contre ?";
			link.l1 = "Laisse Svenson s'en occuper. Il peut convaincre n'importe qui. L'élimination de Jackman jouera aussi son rôle.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Très bien. Je dois de toute façon me lier d'amitié avec Svenson... "+pchar.name+" ! Je veux te remercier pour tout ce que tu as fait pour moi et Nathan. Tu as sauvé mon mari et nous as rendu tout ce que nous avions perdu. Je te dois une fière chandelle.";
			link.l1 = "Allez, Dannie. Nous sommes amis.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Je veux que tu saches que nous serons toujours heureux de te voir à Maroon Town. Trouve-nous là-bas quand tu auras un peu de temps. Nathaniel et moi trouverons un moyen de te récompenser.";
			link.l1 = "Bon sang, Dannie ! J'accepte ton invitation avec plaisir. On s'assiéra, on boira et on discutera de comment toi et Nathan avez coulé Van der Decken...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Il l'a dit ? Oh, ne m'en parle pas...";
			link.l1 = "Très bien, Dannie. Tu as beaucoup de travail devant toi et je dois rendre visite à nos amis jurés - Marcus et Barbazon. J'espère que tu me permettras de retourner cette cabine, je suis sûr qu'il y a beaucoup de choses intéressantes dans les coffres de Jackman.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Bien sûr, penses-tu vraiment que je m'y opposerais ?";
			link.l1 = "Chouette. En fait, c'est dommage de te quitter, Dannie... À bientôt à Maroon Town !";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", Je suis très heureux de vous voir ! Nous sommes de retour à Maroon Town et Nathan est à sa place légitime à nouveau. En fait, tout le monde dans le village en est ravi. Maintenant, tout ira aussi bien qu'avant ! Je vous suis très reconnaissant pour votre aide désintéressée !\nJe veux vous offrir un cadeau. Tenez, prenez-le. Ce talisman peut vous rendre le combat bien plus facile. Et cette formule vous permettra d'en fabriquer d'autres pour vous-même.";
			link.l1 = "Merci, Dannie !";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ce n'est pas tout. J'ai aussi trouvé deux coffres remplis d'or ici. Ils appartenaient sans doute à Jackman. Prenez-les en signe de ma gratitude. Et n'osez pas refuser! Je sais combien d'argent vous avez dépensé pour m'aider, moi et Nathan.";
			link.l1 = "D'accord, d'accord, Dannie, je les accepte !";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent ! "+pchar.name+", je veux que tu saches que tu es notre meilleur ami à partir de maintenant. Nathan et moi serons toujours ravis de te voir à Maroon Town ! Viens nous voir plus souvent !";
			link.l1 = "Merci ! Je serai ravi de te revoir, alors attends-moi !";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "Que pouvons-nous faire pour vous, "+pchar.name+"?";
				link.l1 = "Hélas, je m'en vais... Adieu, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "Et voici "+GetFullName(pchar)+"Je vois à ton visage que tu n'as pas perdu de temps !";
					link.l1 = "Je dois admettre, tu sais t'amuser ! Merci, j'ai passé un bon moment.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Je suis heureux de te voir, "+pchar.name+"! Rhum, vin ? Ou une fille ?";
			link.l1 = "Merci, Dannie ! Je voulais juste te voir...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "La fille? Silence, Danny! Tu ne veux pas me trouver découpé en morceaux et soigneusement plié sur le pas de ta porte, n'est-ce pas? Ha-ha. Ma fidèle dame, qui se tient juste derrière la porte, ne me pardonnera pas de tels tours de passe-passe.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Une fille ? Cela semble intéressant, Danny. Je languis de... le battement de cœur d'une femme... Je pense que je devrais jeter un œil - tu ne me recommanderais pas n'importe qui, n'est-ce pas ?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Vraiment ? Pourquoi es-tu si pâle ? Ha-ha, je plaisantais juste. Prends soin d'elle, tu entends ?";
			link.l1 = "Bien sûr. Elle est plus précieuse pour moi que tous les trésors de ces contrées !";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "C'est mieux, ha-ha. Allez, file déjà, ta chère doit être en train de s'inquiéter.";
			link.l1 = "Adieu, Danny. Et merci pour ton inquiétude, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Je vous assure, cette jeune beauté sait assurément comment vous faire passer un moment inoubliable, "+pchar.name+"Amuse-toi bien ! Elle t'attendra dans la chambre de la taverne.";
			link.l1 = "Merci, Danny. Je suis en route. Je ne veux pas perdre une minute!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", vous êtes toujours le bienvenu à Maroon Town. Les meilleures filles sont à vous!";
			link.l1 = "Oh, Danny. Je jure que c'est ma seconde maison.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "Et voici mon capitaine. Aujourd'hui, tu es seulement à moi ! Viens à moi, je t'ai attendu si longtemps...";
			link.l1 = "Oh, vraiment ? Tu ne peux plus attendre ? Eh bien, ne perdons pas de temps !";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Mon capitaine... tu sais vraiment comment conquérir les dames ! Je n'ai jamais vécu quelque chose de pareil ! Peut-être que tu resteras quelques heures de plus ?","Tu pars déjà, mon cher ?");
			link.l1 = RandPhraseSimple("Je savais que tu ne voudrais pas me laisser partir si facilement. Adieu, chérie. De grandes choses m'attendent...","Hélas, le travail s'interpose. Mais peut-être nous reverrons-nous...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Enfin, Nathan et moi pouvons respirer librement à nouveau ! Ce foutu salaud de Jackman est mort ! Je suis désolé pour le 'Centurion' mais j'avais déjà accepté sa perte quand ce salaud me l'avait volé. Donc je ne m'en fais pas trop.";
			link.l1 = "Mais je le fais. Je suis un idiot ! Toutes les preuves ont sombré au fond de la mer avec le navire. Cela aurait pu nous aider lors du vote pour le nouveau chef de la Confrérie de la Côte. Maintenant... tout est perdu.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Ne te fâche pas trop ! Ça arrive. La prochaine fois, tu auras plus de chance... Quoi qu'il en soit. Je veux te remercier pour ce que tu as fait pour moi et Nathan. Tu as sauvé la vie de mon mari. Je te dois beaucoup.\nJe veux que tu saches que Maroon Town sera toujours ravi de te voir. Viens nous voir, moi et Nate, quand tu auras le temps. Nous trouverons un moyen de te rembourser.";
			link.l1 = "Très bien, Dannie. Je te rendrai visite, c'est certain. Tu pars déjà ?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Oui, j'irai au Miskito, j'espère que Serpent d'Oeil a déjà guéri Nathan. Ensuite, nous retournerons à la ville des Marrons.";
			link.l1 = "Héhé, je me suis déjà tellement habitué à toi, c'est dommage que je doive me séparer de toi... Bonne chance, Dannie !";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Oh, ne fais pas l'innocente, ma douce. Charles, cette amoureuse tournait autour de cet idole jour et nuit, et n'arrêtait pas de harceler le pauvre Oeil de Serpent avec des questions. Et puis elle est rentrée chez elle pour lui apporter quelque chose, n'est-ce pas ?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Oh, merci pour le spectacle, Charles. Toute la ville des Marrons en jasera, ha-ha !";
			link.l1 = "Je n'ai aucun doute que c'est ta nouvelle priorité - t'assurer que cela se produise.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "En fait, tout en bas de ma liste. Ne sois pas fâché contre la fille - c'est sa première fois. Quand Nathan et moi avions nos aventures, tout l'archipel se moquait de nous aussi.";
			link.l1 = "Changeons de sujet et d'humeur. J'en ai fini avec cette idole, allons-y.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "D'accord, allons-y, héros.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Que voulez-vous, Capitaine ?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Je veux te demander conseil, Dannie!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Ecoutez mon ordre !";
            Link.l1.go = "stay_follow";
			link.l2 = "Ce n'est rien. Rompez !";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Ordres ?";
            Link.l1 = "Reste ici !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne traîne pas !";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Changez le type de munitions pour vos armes à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisir le type de munition :";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Il y a un changement de disposition !";
            Link.l1 = "Congédié.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Il y a un changement de disposition !";
            Link.l1 = "Congédié.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
