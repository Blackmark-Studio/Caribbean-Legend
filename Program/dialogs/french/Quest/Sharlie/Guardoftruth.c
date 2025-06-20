// диалоги НПС по квесту 'В поисках Стража Истины'
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
			dialog.text = "Comment puis-je vous aider ?";
			link.l1 = "Désolé, ce n'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "Que veux-tu ? Un autre interrogatoire ? Va au diable !";
			link.l1 = "Sénor, quel est votre nom ?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Que diable te soucie le nom de l'homme que tu vas pendre ou fusiller ? Bastardo ! J'ai été assez imprudent pour tomber entre tes mains après tout...";
			link.l1 = "Sénor, identifiez-vous. Je ne peux pas parler à un homme sans connaître son nom.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+"Alors, êtes-vous satisfait? Maintenant, à qui ai-je le plaisir de parler?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+"Avez-vous déjà entendu parler de moi auparavant ?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Non, carajo ! Ai-je l'air de connaître chaque vagabond errant dans les Indes occidentales qui...";
			link.l1 = "Assez. Faisons cela sans insultes et comportons-nous comme des gentilshommes. Ton sort dépendra de ce que tu pourras me dire. Si tu me dis quelque chose d'intéressant, je solliciterai ta libération sous ma garde. Cela te permettra d'échapper à la balle de mousquet ou à la potence qui t'attend en ce moment.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dios mio, c'est une offre que je ne peux refuser. Que voulez-vous savoir, señor ?";
			link.l1 = "Qui a organisé une attaque si grande sur Saint-Pierre et pourquoi ?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Baron Ramon de Mendosa y Riba, le commandant de garnison de l'île de Providence. Il a envoyé une escadre pour razzier et piller la ville, s'emparant de tous les objets de valeur que nous pourrions trouver.";
			link.l1 = "Quelle était votre tâche immédiate lors de l'attaque? Plus précisément, quels étaient vos ordres?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Je suis le commandant du bataillon de marine. Nos ordres étaient de saisir le fort et de sécuriser ses batteries pour qu'elles ne tirent pas sur nos chaloupes de débarquement en approchant de la ville. Après cela, mes hommes ont participé à l'attaque de St. Pierre lui-même.";
			link.l1 = "Aviez-vous été informé des objets de valeur situés dans la ville ? De la quantité et de la qualité ?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Nous n'avions pas d'informations précises quant à la quantité, mais le baron de Mendosa y Riba nous a dit qu'il y a de l'argent stocké sous le fort et que les entrepôts du port contiennent des matières premières stratégiques vitales pour l'effort de guerre : du bois de fer et de la soie de navire.";
			link.l1 = "As-tu trouvé ces objets de valeur ?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Non. Nous n'avons trouvé ni l'un ni l'autre. Les entrepôts étaient remplis de marchandises coloniales typiques et sous le fort, il y avait de la poudre à canon, des armes, et du plomb. Mais nous n'avions pas assez de temps pour mener une recherche plus approfondie... les renforts français sont arrivés en trombe et nous avons été contraints de livrer bataille.";
			link.l1 = "N'as-tu pas trouvé étrange de ne pas avoir trouvé les objets de valeur ?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Bien sûr que je l'ai fait, mais je ne remets pas souvent les ordres en question.";
			link.l1 = "Ecoutez bien ce que je vais vous dire. Le Fort St. Pierre n'a jamais contenu d'argent, et ces entrepôts n'ont jamais stocké de bois de fer et de soie. Réfléchissez bien, señor, avant de répondre, car si votre réponse ne me plaît pas, je me retournerai et sortirai d'ici, vous laissant à votre sort... un sort bien triste.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Je t'écoute.";
			link.l1 = "Je ne crois pas que le seul but de votre raid était un simple vol. St.Pierre est une colonie modeste et relativement pauvre pour envoyer toute une escadre ici dirigée par un vaisseau de premier rang. Sûrement vous, votre commandant ou quelqu'un d'autre aviez des ordres ou des instructions supplémentaires. Que vous ont-ils dit ? Réfléchissez bien avant de répondre...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Tu vas te taire ? D'accord. Réfléchis-y un instant, j'attendrai.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Sénor, ma vie va-t-elle dépendre de ma réponse ?";
			link.l1 = "Correct.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "J'ai quelque chose... Mais vous devez me jurer que vous me sortirez d'ici et me ramènerez en Espagne contre rançon.";
			link.l1 = "Si tu me dis quelque chose qui mérite mon attention, je jure sur la Sainte Croix que tu seras livré à bord de mon navire pour rançon et tu échapperas à l'exécution.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "D'accord. Don Diego de Montoya a instruit notre bataillon de marines que nous devons, sous le plus grand secret et avec la plus haute importance, trouver et capturer un homme du nom de Miguel Dichoso, qui se trouve quelque part à St. Pierre sous la protection des autorités.";
			link.l1 = "Continue. Qui est Diego de Montoya ?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "L'officier commandant l'escadron. Il a pris la fuite peu après votre... arrivée dramatique.";
			link.l1 = "Qui est-il, ce Don Diego ?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Je sais seulement qu'il est un représentant autorisé du Baron de Mendosa y Riba, son homme de confiance et agent pour les tâches critiques.";
			link.l1 = "Intéressant... Et qui est Miguel Dichoso, l'homme pour lequel apparemment toute cette catastrophe a été organisée pour capturer ? Ce doit être un mauvais bougre, hein ?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Vous souvenez-vous de votre serment, señor ?";
			link.l1 = "Oui. Et j'affirme que si tu continues de raconter ton histoire, tu seras livré comme témoin clé à mon navire et plus tard... eh bien, je trouverai un moyen de te mener à une colonie espagnole. Mais pas avant que tu ne me dises tout ce que tu sais.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso est l'ancien frère d'armes du baron, cependant certains disent que Miguel l'a trahi. Senor de Mendosa y Riba le veut vivant, donc nous avons reçu l'ordre de ne pas tuer Dichoso sous aucun prétexte.";
			link.l1 = "Est-ce que Dichoso est aussi un Espagnol?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Si. Don Diego de Montoya nous a donné une description approximative et a ordonné que tout homme ressemblant à Dichoso devait lui être livré directement. Mais étant donné le peu de temps que nous avions avant votre contre-attaque, nous n'avons jamais eu le temps de chercher.";
			link.l1 = "Connaissiez-vous Dichoso personnellement ?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Non, seulement par réputation. Je n'ai jamais vu cet homme auparavant. Il y avait certains de mes camarades officiers qui le connaissaient personnellement. Ils sont tous morts.";
			link.l1 = "À quel point Dichoso a-t-il trahi votre Don Mendosa pour qu'il décide d'envoyer toute une escadre à ses trousses ?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "Je vais vous raconter. Le baron est arrivé récemment dans les Caraïbes depuis l'Espagne. Ses ordres étaient d'assurer la sécurité des convois de la Flotte du Trésor Espagnole, mais au lieu de cela, il a regardé vers l'intérieur des terres... cherchant de l'or indien. Sa tête a été tournée par des rumeurs de trésors cachés. Il a décidé qu'une ancienne cité maya existe quelque part au fond des jungles du Yucatan - Tayasal, la légendaire cité d'or\nLe baron a envoyé plusieurs expéditions pour trouver la cité, mais toutes ont été totalement anéanties dans la selva sauvage. Nul doute que chacun d'eux a été massacré par les guerriers Itza qui y vivent\nFinalement, l'Inquisiteur Vincento en a eu assez des fantasmes de Don Mendosa et de la mort inutile de bons soldats. L'inquisiteur a informé Madrid de la situation. Le vice-roi a interdit à Don Mendosa de chercher la ville mythique et de se concentrer sur ses devoirs. C'est alors que Miguel Dichoso est apparu\nIl a convaincu le baron d'organiser une autre expédition qui étonnamment a été un succès. Ils ont trouvé les ruines d'une ancienne cité et un tas d'or incrusté de bijoux. Mais à leur retour, ils ont été attaqués par la tribu des Mosquitos\nTous sauf Miguel ont péri, les fléchettes indiennes sont trempées dans un poison local, même une petite égratignure mène à une mort certaine et agonisante en quelques jours. Dichoso est revenu à Providence avec le trésor qu'il pouvait porter\nCarajo ! Le baron était incroyablement heureux, il a envoyé des lettres urgentes à Madrid et au Père Vincento à Santiago, nul doute qu'il voulait frotter son succès au visage du Père Révérend. Puis une frégate a été préparée pour livrer le trésor de retour en Espagne. Dichoso s'est porté volontaire pour l'escorter.";
			link.l1 = "Laisse-moi deviner. Il n'a pas livré l'or ?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Correct, senor! La frégate a disparu sans laisser de trace avec toute la cargaison et l'équipage, y compris Dichoso. Le baron était furieux. Il a encore une fois été humilié devant l'Escorial, à la grande satisfaction du Père Vincento. Maintenant, Don Mendosa est un homme obsédé par la récupération de sa fierté blessée, de son trésor perdu et de Miguel Dichoso.";
			link.l1 = "Est-il possible que la frégate ait simplement été prise dans une tempête et ait sombré ? Ou capturée par des pirates ?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "Le baron a juré sous le coup de l'émotion qu'il était sûr que Dichoso l'avait trahi. Je ne connais pas les détails. Après plusieurs semaines, Don Diego de Montoya est arrivé avec de nouvelles informations, selon lesquelles Miguel Dichoso pourrait être à St. Pierre.";
			link.l1 = "Hm. Intéressant. Ces trésors indiens encore. Tout semble étrangement lié à eux... Alors, tu n'as pas trouvé Dichoso ?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Non. Et honnêtement, je serais surpris s'il avait jamais été ici. Le baron est tellement obsédé par la capture de Dichoso qu'il croirait même aux fantasmes les plus farfelus.";
			link.l1 = "Dis-moi, "+npchar.name+", comment Don Mendosa a-t-il découvert cette... euh... cité de Tayasal ? Il ne l'a pas rêvée, n'est-ce pas ? Y avait-il des faits ou autre chose ?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "C'est le Père Vincento qui a entendu le premier parler de l'existence présumée de Tayasal et de la cité d'or. Où il a découvert cela, je n'en ai aucune idée...";
			link.l1 = "C'est un développement intéressant. Le père Vincento a élaboré la théorie de l'existence de Tayasal par lui-même, a informé l'Espagne de son propre chef, et a commencé à jeter des mouches dans le baume du baron...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "En tant que bon catholique, vous devriez savoir comment ces révérends pères du Saint Tribunal fonctionnent... Il n'a pas informé Madrid sans raison. Il a un certain angle, mais l'arrivée du baron ne faisait apparemment pas partie de ses plans. Quoi qu'il en soit, je n'en sais pas plus à ce sujet. Je n'ai jamais eu le désir de traiter avec l'Inquisition.";
			link.l1 = "D'accord. Vous m'avez donné beaucoup d'informations intéressantes, "+npchar.name+", et fidèle à mon serment, je te fais sortir d'ici. Je reviendrai pour toi plus tard, mais pour l'instant... laisse-moi réfléchir un peu à ce que tu m'as dit...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Señor ? Tiendrez-vous votre promesse ?";
			link.l1 = "Je tiens toujours mes promesses. Aujourd'hui est votre jour de chance, "+npchar.name+". Tu viens avec moi à Santiago sur Cuba. Je te parlerai davantage de mon plan quand nous arriverons. Mais pour l'instant, bienvenue à bord. Tu seras accompagné jusqu'au port et livré à mon navire.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Ma gratitude, capitaine. Je suis heureux que vous soyez un gentilhomme de parole.";
			link.l1 = "Tu pourras exprimer ta gratitude plus tard. Tu seras mon invité, mais sous bonne garde. Ne le prends pas mal, j'ai encore besoin de toi.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Je comprends, señor. Je vous donne ma parole d'honneur, en tant qu'officier espagnol, que je ne tenterai aucune évasion.";
			link.l1 = "Dieu épargne les prudents. À bord, moussaillon.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Capitaine, quels sont vos objectifs ici à Cuba ? Êtes-vous ici pour me déposer ? Je n'ose même pas l'espérer...";
			link.l1 = "C'est tout à fait exact, je suis ici pour ramener vos compatriotes. Maintenant, la raison de mon arrivée ici est un peu plus compliquée que cela. Mais cela ne vous concerne plus. Je vais vous laisser partir dès maintenant sans rançon, mais à la condition que vous me juriez deux choses.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "Que sont-ils ?";
			link.l1 = "Le premier est que je vous donnerai une lettre scellée. Vous remettrez personnellement cette lettre à l'Inquisiteur de Santiago, Père Vincento. S'il vous demande de qui vient la lettre et comment vous l'avez obtenue, dites-lui la vérité...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Le second est que vous ne prêtiez aucun secours ni assistance à toute tentative de me retrouver et d'attaquer mon navire, au moins pendant une semaine. D'accord?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "C'est tout ?";
			link.l1 = "Oui, c'est tout. Remplis mes conditions et tu es libre de partir.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Je vous jure, señor, que je remettrai la lettre au Père Vincento en personne et que je ne prendrai aucune action de quelque nature que ce soit qui puisse provoquer l'agression de la garnison de Santiago contre vous ou votre navire. Soyez assuré, je tiendrai parole. Je suis Espagnol et je respecte les adversaires forts et nobles.";
			link.l1 = "D'accord, Don "+GetFullName(npchar)+", J'accepte votre serment et je vous libère sur-le-champ. Tenez, prenez cette lettre pour l'Inquisiteur. Vous êtes maintenant libre.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Adieu, señor. J'espère que nous ne nous croiserons jamais plus sur le champ de bataille. Cela me chagrinerait terriblement.";
			link.l1 = "Adieu...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, quelle rencontre chanceuse ! Bonjour, monsieur "+GetFullName(pchar)+" ! Je vois que vous êtes devenu un invité de marque à Santiago. Travaillez-vous pour la Sainte Inquisition ?";
			link.l1 = "Salutations, señor "+npchar.name+"Je pensais que nous ne nous reverrions jamais, du moins pas dans des circonstances amicales ! Non, je suis juste passé rendre visite au Père Vincento. Et toi, que fais-tu ? Tu sers à Santiago maintenant ?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "Apres que tu m'as libéré de l'arrestation, j'ai été forcé de rester à Santiago, il n'est pas sûr pour moi de retourner à Providence... mais comme tu peux le voir, j'ai tenu ma parole. Aucun navire espagnol ne te poursuit...";
			link.l1 = "Je suis heureux que nous soyons tous deux des hommes de parole.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Ecoutez, capitaine, cela vous dérangerait-il de lever un verre de rhum, à nos retrouvailles, pour ainsi dire ? Je n'aurais jamais pensé proposer cela à un Français, mais vous, señor, êtes une exception.";
			link.l1 = "Bien sûr! Je ne serais pas contre me rincer la bouche avec un peu de rhum. Allons à la taverne.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ah, santé !";
			link.l1 = "À quoi trinquons-nous, señor officier ?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Buvons à quelque chose de neutre, mais qui nous concerne tous deux. Par exemple, un service galant et fructueux à sa nation ! Nous en avons tous une !";
			link.l1 = "Et buvons aussi à nos monarques qui parviennent à un accord entre eux pour que les Français et les Espagnols cessent de se battre tant chez eux qu'aux Caraïbes.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Bien dit, capitaine ! À la paix ! Je vais vous montrer comment on boit en espagnol ! Arriba, abajo, al centro y pa' dentro !";
			link.l1 = "À la paix... (en buvant)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha ! Le rhum cubain est vraiment le meilleur des Caraïbes...";
			link.l1 = "Je suis d'accord. Dis-moi, ont-ils essayé de te punir pour avoir été capturé à St. Pierre ?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Heureusement, je n'ai reçu qu'une tape sur les doigts. Ce désastre est maintenant derrière moi. Ils ont besoin d'officiers ici dans les colonies, après tout.";
			link.l1 = "Et ton commandant... comment s'appelait-il... Diego, c'est ça ? Comment s'est déroulé le raid infructueux pour lui ? A-t-il été rétrogradé ?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Oh, non ! Notre cher Diego de Montoya est intouchable tant qu'il a Don Ramon de Mendosa y Riba derrière lui. Au fait, Don Diego était à Santiago hier seulement. Il est arrivé de San Jose.";
			link.l1 = "Sans blague ? Intrigant ! Heureusement que nous ne nous sommes pas rencontrés dans la rue. J'ai bien peur que cette affaire aurait pu finir en duel, haha !";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego n'a pas de temps pour vous maintenant, capitaine. Il a bien trop à perdre en ce moment pour risquer sa vie dans un duel. Il a concocté un plan avec le Baron Mendosa dans le Grand Ouest. Il a rassemblé une escadre à La Havane et envisage de retourner en Espagne d'un jour à l'autre.";
			link.l1 = "Es-tu aussi dans son équipage ?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Non. Demain, je pars pour la garnison à San Juan, qui se trouve à Porto Rico. Je ne suis plus le bienvenu à Providence avec Don Mendosa là-bas.";
			link.l1 = "Eh bien, trinquons à votre nouvelle affectation et puisse-t-elle ne vous apporter que des moments heureux et de belles filles qui vous y attendent.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Muchas gracias, monsieur. Tous mes voeux de bonheur à vous aussi. Ah, je pense qu'il est temps pour moi de partir. Je finirai ce verre et puis je vous quitterai.";
			link.l1 = "Vaya con Dios, señor "+npchar.name+"Peut-être que nous nous reverrons en paix.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish took the bait; hook, line, and sinker... Oh, looks like we meet again, monsieur. Unfortunately, not under the peaceful auspices that we wished.";
			link.l1 = "Bonjour, ami."+npchar.name+" ? Eh bien ! Je ne m'attendais pas à cela. Pour une raison quelconque, je pensais que vous étiez un officier honnête et noble. Il s'avère que j'avais tort.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Qu'est-ce qui te fait croire que tu as tort? J'ai tenu ma parole, je n'ai pas juré d'amitié éternelle avec toi. Rien n'a changé, monsieur. Vous êtes toujours un ennemi de l'Espagne et mon ennemi personnel. Ce n'est pas Santiago, il n'y a pas de Père Vincento ici, et son petit sauf-conduit ne va pas vous aider...";
			link.l1 = "Oh, c'est comme ça ? Il se trouve que je pense qu'avoir une conversation amicale autour d'un peu de rhum, tout en essayant de m'attirer dans un piège, est assez perfide, vous ne trouvez pas, señor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Tu oses me traiter de traître, espèce de maricon?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Hé, toi ! Oui, oui, toi !"+GetFullName(pchar)+"?";
			link.l1 = "Oui, l'ami. C'est moi.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "J'ai reçu une lettre d'une personne importante. Tu sais déjà de qui il s'agit.";
			link.l1 = "Je sais, donne-le moi.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Voilà. Que dirais-tu de quelques pièces pour mon dérangement ?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Prends un peu d'argent. Tu l'as gagné honnêtement.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Tu essaies de me rouler, camarade ? Tu as déjà été payé pour la livraison.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Merci, mon gars. Un plaisir de traiter avec un gentilhomme généreux.";
			link.l1 = "D'accord, dégage, et ne souffle mot de ce qui s'est passé ici.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "Le loup de La Havane est ton ami...";
			link.l1 = "Hein ? Tu es encore là...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Bienvenue à bord de l'Admirable, capitaine "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"Surprenant. Me connaissez-vous ?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Qui dans les colonies françaises n'a pas entendu parler du grand capitaine nommé "+GetFullName(pchar)+", celui qui a arraché les dents d'une escadre espagnole menée par un cuirassé attaquant St. Pierre et a tué tout le groupe de raid ennemi ! Vous êtes un héros national !";
			link.l1 = "Oh, allez. 'Un héros'... Je suis juste un soldat remplissant son devoir envers la France.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Ne pense pas qu'une armée de soldats aurait pu faire ce que tu as fait, capitaine... Eh, j'aimerais t'offrir un peu de rhum à la taverne, mais hélas : le capitaine a interdit de laisser les hommes boire ne serait-ce qu'une goutte de rhum et je ne veux pas donner le mauvais exemple...";
			link.l1 = "Hm... Alors, vous n'êtes pas capitaine vous-même ?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "J'ai l'air d'un capitaine ? Hoho ! Non, je suis juste le maître d'équipage. Je m'appelle Serge Degas. Notre capitaine, Gaius Marchais, passe toute la journée à la taverne, pendant ce temps nous attendons un convoi de 'marchands'. Le capitaine doit une solde aux marins, et à nous aussi, tout l'équipage est complètement fauché...";
			link.l1 = "Qu'est-ce qui ne va pas ? La caravane espagnole de vanille ne s'est pas montrée pour se faire plumer ?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Pas moyen ! Notre capitaine a mis fin à la piraterie après avoir capturé ce galion. Vous voyez, il a entendu dire qu'une caravane commerciale naviguant vers l'Europe fera bientôt escale à la Guadeloupe et qu'ils achèteront de la vanille. Alors il a rempli nos cales de vanille à ras bord à Bridgetown ! Il pensait pouvoir la vendre à trois cents pesos la caisse, ouais, tu parles !\nÉvidemment, il n'y a pas de caravane de vanille à notre arrivée, et vendre la vanille aux locaux serait une perte. Alors nous voilà, à attendre les 'marchands', je suis sûr qu'ils se montreront ici un jour ou dans trois ans... le Capitaine reste à la taverne toute la journée, étant une sacrée nuisance et embêtant tout le monde. Il ne retourne au navire que pour s'effondrer. Maintenant, enfin, il est prêt à vendre pour deux cents pesos juste pour rentrer dans ses frais.\nTout notre argent a été mis dans cette cargaison. Un jour, l'équipage va l'attacher et vendre la vanille à bas prix juste pour couvrir nos dettes... Je jure que je peux le voir arriver d'un jour à l'autre.";
			link.l1 = "Oui...qu'est-ce qui tracasse ton capitaine ?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Eh bien, si un travail vaut la peine d'être fait, il vaut la peine d'être bien fait. Il ne fait ni l'un ni l'autre. C'est un terrible négociateur. Cela aurait été différent s'il avait aussi transporté des marchandises, mais il voulait se sentir comme un vrai marchand. J'espère qu'il passera par-dessus bord une nuit...";
			link.l1 = "Je t'ai compris, Serge. Ne t'inquiète pas, je suis sûr qu'un jour ta... caravane apparaîtra.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Oh, je ne crois pas aux miracles, capitaine. Peut-être que nous nous reverrons un jour et que nous boirons un peu de rhum... ce que je ne ferais pas pour un peu de rhum en ce moment...";
			link.l1 = "Bonne chance, l'ami.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, capitaine, j'aimerais bien une gorgée de rhum !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho ! Ne seriez-vous pas du navire marchand ? Non ? Oh, je vous présente mes excuses. Bien sûr que non... Ma faute.","Je ne suis pas d'humeur, monsieur, alors trouvez quelqu'un d'autre à qui parler.","Ah,   vous encore?!","Hem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ne t'en fais pas, l'ami. Ça arrive.","Prenez un peu de rhum, capitaine. Ça apaisera un peu vos soucis...","Ne sois pas nerveux, l'ami. C'est mauvais pour ta santé.","D'accord, d'accord. Je m'en vais.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "A argh... Mm... Qu'est-ce que c'est, diable, qu'est-ce que c'est ?..";
			link.l1 = "Silence, l'ami... Ne fais pas de bruit...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Hein? Quoi? Merde!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah ! Qui êtes-vous ? Que voulez-vous de moi ?";
			link.l1 = "Si tu ne la fermes pas, je vais te casser les dents, compris ? Où sont les vaisseaux sacrés que tu as pris en capturant ce navire ?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Quels navires ? Je ne sais pas de quoi vous parlez ! C'est mon navire !";
			link.l1 = "Votre navire ? Jusqu'à récemment, elle s'appelait 'Santa Margarita' et naviguait sous pavillon espagnol... Je vous demande, où sont ces vases sacrés ? Un ostensoir en or, une croix incrustée de lazurite, et un encensoir en or ? Qu'en avez-vous fait ? Vous ne les avez pas vendus, n'est-ce pas ?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Oh mon Dieu, je n'en crois pas mes oreilles... tu es espagnol ? Oh, non... tu n'es pas espagnol ! Tu es français ! C'est encore pire ! Tu t'es vendu à ces vils Castillans ! Combien paient-ils pour les âmes des Français ces jours-ci ? Je ne te dirai rien, traître ! Tu n'auras pas ces babioles !";
			link.l1 = "Pas un mot hein? Ça me va très bien. Ce n'est de toute façon pas le meilleur endroit pour un interrogatoire... On va te bâillonner pour t'empêcher de couiner et ensuite on va dans ma chaloupe... tu finiras par parler, l'ami. Je n'en doute pas.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Traître espagnol ! Tu ferais mieux de...";
			link.l1 = "Silence, vaurien... Suis-moi de près ou je te renverse et te traîne sur le pont par les pieds.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Comment puis-je vous aider, monsieur ?";
			link.l1 = "Comment ça va, capitaine ? Qu'est-ce qui vous amène à Basse-Terre ? Si je comprends bien, vous êtes un Espagnol naviguant sous pavillon hollandais ?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Quel est le problème, monsieur ? Oui, je suis Espagnol. C'est facile à deviner par le nom et le type de mon navire, mais je suis ici tout à fait légalement. J'ai une licence de la Compagnie néerlandaise des Indes occidentales, donc...";
			link.l1 = "Ne t'agite pas, señor ! Nous sommes vraiment très heureux que tu sois espagnol... Dis-moi, es-tu ici pour l'importation ou l'exportation ?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "J'ai apporté des marchandises de La Havane et les ai vendues sur le marché local. Maintenant, j'attends une cargaison rentable pour éviter de rentrer chez moi avec une cale vide.";
			link.l1 = "Senor, j'ai une proposition d'affaires pour vous ! Vous pourriez gagner de l'argent si vous m'aidez. En discutons-nous ? Quel est votre nom, d'ailleurs ?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Capitaine Carlos Guevara. Quelle est votre offre?";
			link.l1 = "Je dois acheter un lot de vanille et l'envoyer à Cuba, à un homme nommé "+pchar.questTemp.Guardoftruth.LMname+", le gardien du phare de Santiago. Cependant, j'ai un sérieux problème. Tout d'abord, aucun magasin n'a la quantité de vanille dont j'ai besoin...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = " ";
			link.l1 = "Deuxièmement, je dois immédiatement partir pour Saint-Christophe et je ne sais pas combien de temps je serai absent. Je perds de l'argent chaque jour, tu comprends ? C'est une sacrée honte !";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Je comprends. Quelle honte, señor. Vous ne pouvez pas gagner tout l'argent du monde, après tout. Alors, que voulez-vous de moi ?";
			link.l1 = "Regarde là-bas. Tu vois ce galion ? Il est bourré de vanille dont j'ai grand besoin. Le problème, c'est que le capitaine du galion s'est mis en tête des idées saugrenues sur une caravane d'épices qui arriverait bientôt ici et achèterait sa cargaison à profit, à presque trois cents pesos la caisse !";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Oui, il y a beaucoup d'hommes naifs dans le coin ces jours-ci, un imbécile et son argent ne font pas long feu...";
			link.l1 = "Naïf est une chose, mais il est carrément stupide ! J'ai proposé d'acheter sa vanille à deux cent dix pesos, il n'en obtiendra même pas deux cents dans une boutique ici. Et tu peux le croire, il m'a dit d'aller me faire voir ! Il a dit qu'il ne vendrait qu'à deux cent cinquante !";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha ! Quel idiot !";
			link.l1 = "Oui ! C'est exactement ce que je lui ai dit. Bien sûr, il s'est mis en colère contre moi... mais j'ai vraiment besoin de cette vanille ! Voici ma proposition, señor. Je ne suis pas marchand, mais je pense que vous êtes un véritable maître dans l'art de la négociation. Et vous avez une cale spacieuse...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Convaincs ce foutu imbécile de te vendre la cargaison. Il ne va pas me la vendre maintenant après que je l'ai insulté en face. Je suis prêt à payer deux cent dix pesos par boîte. Si tu fais baisser le prix, garde la différence pour toi. Et pour cela, je vais affréter ton bateau pour livrer la vanille à Santiago.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Combien êtes-vous prêt à me payer pour la cargaison ?";
			link.l1 = "Combien veux-tu ?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago est assez loin...trente mille pesos.";
			link.l1 = "C'est trop, amigo. Faisons moitié-moitié, ici.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "D'accord, c'est sur mon chemin de toute façon... Vingt-cinq mille et pas un peso de moins.";
			link.l1 = "C'est bien. Le capitaine du galion s'appelle Gaius Marchais. Il passe toute la journée à bouder à la taverne. J'espère que tu pourras le convaincre de se séparer de ses épices.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "J'ai déjà fait affaire avec des imbéciles encore plus grands. Je lui dirai tous les détails sur qui répand les rumeurs sur la caravane qui était censée acheter la marchandise à des prix exorbitants. Une fois que je l'aurai convaincu que tout cela n'est qu'une invention de son imagination, il vendra, j'en suis sûr.";
			link.l1 = "Alors, avons-nous un accord ?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Nous avons un accord si tu as l'argent pour payer la vanille et le transport. Comme le dit le charmant proverbe irlandais : 'Montre-moi l'argent.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Voilà, jette un œil. Tout est là.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "J'ai l'argent sur mon navire. Je vais le chercher et reviens tout de suite !";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "As-tu apporté l'argent ?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Voilà, jetez un coup d'œil. Tout est là.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Je m'en occupe tout de suite !";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Estupendo ! J'aime faire affaire avec des partenaires sensés. Reviens "+sTemp+"  à dix heures du matin. Je pense qu'à ce moment-là, notre ami commun Gaius aura retrouvé ses esprits.";
				link.l1 = "Génial ! À plus tard !";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Estupendo! J'aime faire affaire avec des partenaires sensés. Je pars vers le rivage. Revenez dans trois heures. Je pense qu'à ce moment-là, notre ami commun Gaius aura retrouvé ses esprits..";
				link.l1 = "Super ! À plus tard !";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Señor, je me souviens bien de mon rôle. Ne vous inquiétez pas, il est coriace, mais je vais le faire craquer.";
			link.l1 = "Merci.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "C'est fait, señor. Le pauvre homme était ravi que je veuille acheter sa vanille. Ses mains tremblaient de bonheur pendant que je comptais une avance - ou peut-être que c'était juste à cause du rhum. Nous chargerons la cargaison à la plage de Capster demain à midi afin d'éviter toute attention indésirable des agents de douane au port. \nJe mettrai immédiatement le cap sur Santiago dès que j'aurai la cargaison à bord. Je contacterai votre partenaire au phare et lui remettrai la vanille après livraison là-bas. Un message à lui transmettre ?";
			link.l1 = "Oui. Voici une lettre. Vous dites que l'affaire se fera à la plage de Capster demain à midi ? Très bien, je jetterai l'ancre juste au large du promontoire, inaccessible depuis l'île au cas où quelque chose se passe.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous pouvez me faire confiance, señor. Je suis un homme honnête. D'ailleurs, je n'ai aucun désir de me quereller avec vous, et un marchand n'est rien sans sa réputation. Mais si vous souhaitez regarder et vérifier, cela ne me pose aucun problème.";
			link.l1 = "Je suis reconnaissant, señor. Je veillerai sur l'accord demain et dès que vous lèverez l'ancre, j'irai vaquer à mes affaires à Saint-Christophe.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Capitaine, je vous assure : je ne vous décevrai pas et je remplirai les conditions de notre accord en totalité.";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hic ! Hourra ! Bon vieux cap'taine nous a enfin donné notre paye ! Trois hourras pour le cap'taine ! Hic !","Ça vient en pintes ?! J'en prends une !","Que nos bourses soient bien pleines et nos donzelles encore plus! Hourra!","Et là ils gisent, tous de bons morts, hic! Comme un lever du jour dans une taverne. Yo ho ho et une bouteille de rhum !","Yo ho ho et une bouteille de rhum !");
			link.l1 = LinkRandPhrase("Aye, compagnon.","Ne penses-tu pas que tu as déjà assez bu de rhum?","Boire et le diable ont fait le reste...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Halte ! Qui va là ? Alarme ! Repoussez les abordages !";
			link.l1 = "... ";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Har har ! T'es venu aussi pour le trésor de Rollie le Cap, hein ? On a cherché et cherché et cherché, et on n'a tout simplement pas pu le trouver. J'aimerais qu'au moins un de ces imbéciles ait l'idée de nager derrière la cascade jusqu'à la corniche !";
			link.l1 = "Vous êtes l'un des hommes du Colonel Fox, n'est-ce pas ?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Je pourrais avoir des liens avec les Renards de Mer. Tu n'as pas besoin de savoir, ça ne sert à rien. Tu n'as pas besoin de savoir quoi que ce soit pour le moment. Tu as trouvé mon trésor, pour lequel nous te devons maintenant un immense merci...";
			link.l1 = "Je vois. Tu n'es pas un Renard de Mer, plutôt un chien de mer... ou un chacal. Qu'est-ce qui te convient mieux ?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "On dirait qu'on a un philosophe naturel parmi nous, les gars. Un vrai expert du règne animal !";
			link.l1 = "Veux-tu inspecter l'acuité de mon sabre, chacal ?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", señor. Comment puis-je vous aider ?";
			link.l1 = "Bonjour. Êtes-vous Donna Belinda de Ribero ?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Oui, c'est moi. A qui ai-je l'honneur de parler ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+", madame. Je vous en prie, ne vous laissez pas rebuter par mon nom de famille français, en ce moment j'accomplis une mission de la part du Très Révérend Inquisiteur de Santiago, le Père Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Que c'est intéressant ! J'ai entendu dire que le Saint Tribunal et la Société de Jésus sont remplis d'une grande multitude de gens, de toutes classes et nationalités, mais je n'avais jamais personnellement rencontré un étranger travaillant pour eux avant maintenant. Que puis-je faire pour vous, señor ?";
			link.l1 = "Vous possédez un objet qui intéresse grandement le Révérend Père. Un ostensoir en or, une monstrance que vous avez récemment acquise auprès du banquier à Willemstad.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Vous êtes bien informé, señor. Eh bien, sachant pour qui vous travaillez, cela ne devrait pas me surprendre. Oui, j'ai acheté l'ostensoir, il ne devrait certainement pas être laissé dans une boutique de marchand à côté de babioles volées et de biens mis en gage comme une vulgaire broutille.";
			link.l1 = "Avez-vous la monstrance, madame ?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Oui. Je comptais l'offrir à notre église paroissiale, mais tant de choses m'ont accablé ici... Je n'ai pas pu... oh, je suis désolé...";
			link.l1 = "Pleurez-vous, madame ? Mes paroles vous ont-elles apporté du chagrin ? Si c'est le cas, je vous prie de me pardonner.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Oh, je vous en prie, señor... Reprenons notre conversation. Si j'ai bien compris, le Père Vincento a besoin de cet ostensoir ? Vous aimeriez que je vous le donne ?";
			link.l1 = "Ce précieux vaisseau était destiné à la cathédrale de Santiago, mais il a été capturé par un pirate ordinaire et vendu à un usurier avec plusieurs autres objets sacrés. Ma tâche est de rendre ce qui a été volé à sa place légitime. Bien sûr, je vous indemniserai pleinement pour vos dépenses.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Oh, vous ne devez pas ! Pensez-vous vraiment que cet argent a tant d'importance pour moi ? J'ai acheté cet ostensoir pour la Sainte Mère Église et je n'hésiterai pas à le remettre à son véritable propriétaire, sans même parler d'un membre de la Compagnie de Jésus servant le Père Vincento. Mais, une autre chose me trouble profondément. Pourriez-vous, s'il vous plaît, aider une fidèle fille de l'Église dans son besoin ?";
			link.l1 = "Vous êtes une noble dame, madame. Quels soucis vous tracassent ? Comment puis-je vous aider ?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Oh, mais señor... Je n'oserais pas demander de l'aide à un frère jésuite lui-même. Vous êtes toujours si occupé...";
			link.l1 = "Tu l'as déjà fait. Quel est le problème?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Peux-tu me promettre, en tant que représentant de la Sainte Église, que personne ne découvrira jamais ce que je te demande ?";
			link.l1 = "Je vous donne ma parole solennelle, señora. Ce n'est pas le sceau de la confession, mais je ne soufflerai mot de ceci à qui que ce soit.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Très bien. Je te fais confiance. Mon très cher ami Esteban Sosa a des ennuis. Il a été capturé par des bandits lors d'un voyage et ils exigent une rançon de cent mille pesos. Je ne possède pas autant d'argent et j'ai seulement réussi à réunir environ la moitié de la somme de ma pension. Je ne peux demander l'aide de personne dans une telle affaire car ils ont juré de le tuer si je le faisais\nDe plus, je m'inquiète pour mon cher... ami et crains le pire. Ils pourraient le tuer dès qu'ils auront l'argent pour s'assurer qu'il ne parlera pas aux gardes à leur sujet. Peut-être que toi, un capitaine courageux, un chrétien, et un frère de la Société pourrais persuader les bandits d'accepter l'argent que j'ai et de ne pas lui faire de mal...";
			link.l1 = "Quand et où aura lieu l'échange ?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Leur chef de file est un certain homme nommé Bartie le Knacker. Il a dit qu'il attendrait la rançon d'Esteban chaque nuit de onze heures à minuit à l'entrée de la grotte dans la jungle...";
			link.l1 = "Ce sont des conditions inhabituellement spécifiques...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Apparemment, ils voulaient que je réunisse toute la rançon rapidement et ne voulaient pas que je demande de l'aide à qui que ce soit... mais je ne peux pas trouver une telle somme, je n'y arriverai jamais !";
			link.l1 = "Ne pleurez pas, madame. J'essaierai de vous aider. Un frère de la Société de Jésus ne laisserait jamais une femme chrétienne vertueuse en péril.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Je dois mettre ma foi en vous... Mais capitaine, Bartie le Dépeceur a aussi dit que si le porteur de la rançon ne vient pas seul ou si je vais voir les gardes, il tuera immédiatement le pauvre Estaban !";
			link.l1 = "Je garderai cela à l'esprit.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Tiens, prends ça. Ce sont les cinquante mille pesos que j'ai pu réunir. Convainc ces brigands d'accepter au moins cela. Dis-leur que je n'ai pas un seul peso de plus ! Ramène Esteban ! Une fois que tu l'auras fait, je te donnerai volontiers l'ostensoir pour le Père Vincento.";
			link.l1 = "Je ferai tout mon possible, madame. Espérons le meilleur.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Que Dieu vous aide, courageux capitaine ! Je prierai pour vous !";
			link.l1 = "... ";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = " Avez-vous des nouvelles, capitaine ? ";
			link.l1 = "Pas encore. Attendez, señora. Je ne vous décevrai pas.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "As-tu des nouvelles, capitaine ?";
			link.l1 = "Oui, señora. Ce ne sont pas de bonnes nouvelles, j'en ai bien peur.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Dis-moi, ne me fais pas attendre ! As-tu rencontré les bandits ?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Tiens, reprends tes cinquante mille. Je n'en avais pas besoin. Prends aussi cette bague. Je crois que tu la trouveras familière.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Tiens, prends cette bague. Je crois que tu la trouveras familière.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Ça... oui, c'est familier. Qu'est-il arrivé à Esteban ?";
			link.l1 = "J'ai trouvé les brigands à la grotte, comme vous me l'avez dit. 'Bartie le Knacker' et Esteban Sosa sont le même homme. Il a simulé l'enlèvement afin de vous extorquer. Il m'a parlé de votre... relation. Il a aussi dit qu'il ne veut plus vous voir. J'ai pris la bague que vous lui avez donnée comme preuve.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Ça... oui, oui je le sais. Qu'est-il arrivé à Esteban ?";
			link.l1 = "J'ai trouvé les brigands à la grotte, comme vous me l'avez dit. Ils m'ont attaqué, ligoté, et pris votre argent. 'Bartie le Dépeceur' et Esteban Sosa sont le même homme. Il a mis en scène l'enlèvement pour vous extorquer. Il m'a parlé de votre... relation. Esteban m'a laissé partir et m'a donné cette bague comme preuve. Il a dit que vous ne le reverriez jamais.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Dieu me damne ! Je n'en crois pas mes oreilles ! Pourquoi tout cela m'arrive-t-il, pourquoi ?! Qu'ai-je fait pour qu'il...";
			link.l1 = "Señora, je vous en supplie, ne vous tourmentez pas pour cela. Ce vaurien ne vaut pas une seule de vos larmes. "+sTemp+" ";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Oh... Je vais essayer de me calmer. Senor, je dois vous remercier pour votre aide. Tenez, prenez votre ostensoir. "+sTemp+"Va avec Dieu.";
			link.l1 = "Gracias, senora. Ne vous inquiétez pas, personne ne découvrira ce qui s'est passé dans la grotte. Nous, jésuites, tenons toujours notre parole. Maintenant, si vous le permettez, je dois partir.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Arrête-toi là, camarade !";
			link.l1 = "Je suis juste ici.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "As-tu apporté l'argent ?";
			link.l1 = "Quelle question idiote. Non, je suis là pour cueillir des Manga Rosas... Pourquoi d'autre penses-tu que je serais venu ici ?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho ! Un comédien ! File dans la grotte, Bartie t'attendait.";
			link.l1 = "Vous êtes clairement un garde expérimenté...avec cette attitude, vous seriez digne de garder le roi Philippe lui-même. Je vais entrer par moi-même.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Tu m'as fait attendre... As-tu l'argent avec toi ?";
			link.l1 = "Êtes-vous Bartie le Découpeur ? Vous ne ressemblez pas à un bandit ordinaire à mes yeux.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Pourquoi te soucies-tu de mon apparence? As-tu cet argent maudit ou non?";
			link.l1 = "Où est l'otage ?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Tu auras ton otage. Allez, donne-moi la pièce. Ne me mets pas en colère, garçon.";
			link.l1 = "Bartie, ai-je l'air d'un imbécile ? Tant que je ne verrai pas Esteban Sosa vivant et bien portant, tu ne verras pas un seul peso. Où est-il ?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Ah, tu fais de la résistance, hein ? Très bien, nous allons te donner une bonne leçon... Les gars, ouvrons un nouveau trou à ce bouffeur de merde !";
			link.l1 = "Bâtard !";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = " ";
			link.l1 = "Ça suffit la danse pour toi ? Où est Esteban Sosa ? Allez, dis-moi ou je te maintiens la tête sous l'eau jusqu'à ce que les bulles s'arrêtent !";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Non... Ne me faites pas de mal, s'il vous plaît ! Je suis Esteban Sosa.";
			link.l1 = "Quoi?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Oui, oui. Je ne suis pas Bartie le Bourreau. Je suis juste...";
			link.l1 = "Canaille ! Alors tu as décidé de soutirer cent mille pesos à la Señora de Ribero en te 'kidnappant' toi-même ?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Tu dois me comprendre, d'homme à homme. Belinda... Elle m'a vraiment refroidi avec son amour obsessionnel. Elle est tout le temps sur moi, jour et nuit, l'ami ! Même son mari a commencé à se méfier de nous et il est à moitié aveugle !";
			link.l1 = "Eh bien, comment ça! Alors vous êtes amants?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Pas   plus maintenant. Je viens   de   m'enfuir d'elle.";
			link.l1 = "Et tu as décidé de prendre quelques pièces pour la route, hein ? Eh bien, que devrais-je faire de toi maintenant ? Cacher ton corps dans la jungle comme tu as essayé de le faire avec moi ?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Non ! Je ne voulais pas de sang, je le jure !";
			link.l1 = "Est-ce pour cela que tu as lâché tes chiens sur moi ?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Nous allions juste vider tes poches, c'est tout !";
			link.l1 = "Et me laisser nu dans la selva ? Je devrais te pendre au grand mât de mon navire, fripon ! Mais je ne le ferai pas, uniquement par respect pour la brave femme qui a eu le malheur de s'embarquer avec toi. Tu sais quoi ? Je devrais te ramener à elle et la laisser décider de ton sort.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Non, tout sauf ça ! Je ne retourne pas à Cumana !";
			link.l1 = "Tu préfères rester dans cette grotte pour toujours ?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Épargnez-moi, señor ! Laissez-moi partir et je m'en irai d'ici pour ne jamais revenir à Cumana ! Je ne vais pas attendre que le mari de Belinda me découpe en duel ou m'envoie un assassin !";
			link.l1 = "Très bien. Pour l'amour de Senora de Ribero, je ne vais pas t'amener à elle. Mais ne pense pas une seconde que tout cela va être balayé sous le tapis. Elle va découvrir quel minable morceau de merde elle a décidé de flirter avec. Quels jetons as-tu qu'elle pourrait reconnaître ?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Tiens. Cette bague en turquoise ici. Elle me l'a donnée elle-même.";
			link.l1 = "Parfait. Donne-le-moi et disparais de ma vue !";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Parfait. Et tu sais, Sosa, j'ai changé d'avis - maintenant je sers la Société de Jésus. Comme disent les Écritures, 'Tu dois purifier le méchant parmi vous.' Et tu es un narcissique maléfique, un criminel, et une ordure inutile. Je pense que je vais te noyer dans cette grotte. Requiesce in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "Tu as ce qu'il nous faut, matelot...";
			link.l1 = "Vraiment ? Et que serait-ce ?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Je n'ai pas demandé, jeune homme riche. On m'a juste ordonné de prendre vos affaires, absolument tout ce que vous avez sur vous. Allons-nous le faire de la manière facile ou difficile ? Le choix vous appartient.";
			link.l1 = "Tu te crois guerrier, hein ? Tu n'as pas la moindre idée de qui tu as affaire. Je bouffe des raclures comme toi au petit-déjeuner.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Tu es un vrai bouffon, n'est-ce pas, grenouille? Eh bien, voyons à quoi ressemble ton sang sur le sol!";
			link.l1 = "Ça ressemblera à la tienne, imbécile. Laisse-moi t'offrir un cours d'anatomie !";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, d'accord mon gars... Vide tes poches sur-le-champ ! Si tu es un bon petit gars et que tu écoutes, tu resteras entier, compris ?";
			link.l1 = "Bon sang, vous revoilà? Vous êtes venus jusqu'ici aussi? Qui diable vous a engagés?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Aucune de tes affaires. Maintenant, rends-toi et vis, ou bats-toi et nous prendrons simplement ton butin sur ton cadavre. Qu'en dis-tu comme marché ?";
			link.l1 = "J'ai une contre-offre. Que dirais-tu si je prenais ton butin sur ton cadavre?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "En attente de vos ordres, capitaine !";
			link.l1 = "Avancez à travers la jungle vers le cap San Antonio. Prenez le sentier à gauche et continuez tout droit. Gardez la tête baissée et préparez-vous à une embuscade sur le rivage. Soyez prêts. J'y arriverai par la mer et vous retrouverai là-bas. Combien de temps vous faudra-t-il pour y arriver ?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Nous serons là dans six heures, capitaine !";
			link.l1 = "Bien. Bouge !";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Enfoiré tenace ! Il est encore en vie... Je savais qu'on aurait dû utiliser plus de poudre ! Très bien, je vais t'achever, fils de pute...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
