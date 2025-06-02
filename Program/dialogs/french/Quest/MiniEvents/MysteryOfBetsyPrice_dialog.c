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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hé, beauté, que diriez-vous d’un ornement exquis pour votre collection féminine ? Un véritable trésor ! Pour vous – des regards admiratifs, et pour moi – quelques pièces pour du pain et une gorgée de rhum.";
			}
			else
			{
				dialog.text = "Hé, Capitaine, que diriez-vous d’un cadeau raffiné pour votre dame ? Un véritable trésor ! Pour vous – sa chaleureuse gratitude, et pour moi – quelques pièces pour du pain et une gorgée de rhum.";
			}
			link.l1 = "Et que des soldats viennent m’arrêter dans une heure pour vol ? Où as-tu trouvé ça, vagabond ?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Un cadeau raffiné ? Et d’où viendrait-il à un sans-abri comme toi ?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Capitaine, j’ai","J’ai")+" trouvé ce magnifique pendentif avec une camée, parole d’honneur ! Que je sois maudit si je mens ! Il traînait là, sans que personne n’en veuille. Je n’allais quand même pas laisser une telle beauté dans la boue, non ?";
			link.l1 = "Bon. Montre-moi ce que tu as.";
			link.l1.go = "Poorman_3";
			link.l2 = "Qui croirait un homme aussi 'respectable' que toi sur parole ? Trouve-toi quelqu’un de plus crédule.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Capitaine, j’ai","J’ai")+" trouvé ce magnifique pendentif avec une camée, parole d’honneur ! Que je sois maudit si je mens ! Il traînait là, sans que personne n’en veuille. Je n’allais quand même pas laisser une telle beauté dans la boue, non ?";
			link.l1 = "Bon. Montre-moi ce que tu as.";
			link.l1.go = "Poorman_3";
			link.l2 = "Qui croirait un homme aussi 'respectable' que toi sur parole ? Trouve-toi quelqu’un de plus crédule.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;

		case "Poorman_3":
			dialog.text = "Regardez... c'est un bel objet ! Je l'ai trouvé dans un parterre de fleurs, près de la maison avec la lanterne, à côté de la taverne. Mais il n'y a plus âme qui vive là-bas depuis longtemps, donc il n'y a personne à qui le rendre.";
			link.l1 = "Un objet curieux. Et combien en veux-tu ?";
			link.l1.go = "Poorman_4";
		break;
		
		case "Poorman_4":
			dialog.text = "Cent pesos seulement"+GetSexPhrase(", Capitaine","")+"... une bagatelle pour quelqu’un comme vous ! Et pour moi – une semaine entière sans me soucier de trouver un morceau de pain. Regardez-moi cette beauté !";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "D’accord, tiens tes cent pesos.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Je vais m’en passer. Tente ta chance auprès de quelqu’un d’autre.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Merci, "+GetAddress_Form(NPChar)+" ! La chance vous sourira à coup sûr ! Vous êtes quelqu’un de bien, ça se voit tout de suite.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;

		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Oh-oh-oh, qui voilà ? Il semble que tu ne t’es pas trompée de porte, chérie... entre, entre ! Déshabille-toi, fais comme chez toi.";
				link.l1 = "Eh bien... qui avons-nous là ? Ne seraient-ce pas ces salopards qui ont laissé un ‘tendre’ message de menace pour Betsy ?";
			}
			else
			{
				dialog.text = "Qu’est-ce que c’est que cette créature ? T’as pas frappé à la mauvaise porte, espèce de caboche de chèvre ? Tire-toi d’ici avant que je t’éventre !";
				link.l1 = "Eh bien... qui avons-nous là ? Ce ne seraient pas ces crétins qui ont laissé un gentil petit message de menace pour Betsy ?";
			}
			link.l1.go = "Pirate_2";
			//PlaySound("Voice/Spanish/citizen/Pirati v Gorode-12.wav");
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy ? Au diable cette Betsy ! Ce qui m’intéresse, c’est de savoir ce que tu fais là, ma jolie... Puisque tu es entrée – ne te presse pas de repartir, on trouvera bien de quoi t’occuper...";
			}
			else
			{
				dialog.text = "Betsy, vraiment ? Tente pas le diable, abruti. Si tu peux encore partir sur tes deux jambes – fais-le. Sinon, il faudra te ramasser à la pelle !";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "Aidez-moi ! Aidez-moi, je vous en supplie !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "Et la voilà. Tu es dans le pétrin jusqu’au cou, mon pote, et si tu ne veux pas que ce soit ta dernière erreur, je te conseille de la relâcher. Immédiatement.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha ! T’as entendu, Reggie ? "+GetSexPhrase("Il","Elle")+" nous menace en plus. "+GetSexPhrase("Quel petit arrogant","Quelle sale prétentieuse")+". Allez, montrons "+GetSexPhrase("à ce crétin la couleur de ses tripes","à cette insolente ce qu’est la vraie douleur")+".";
			link.l1 = "C’est vous que ça regarde.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Maintenant, libère la fille. Ou tu vas finir à côté de ton copain.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Sales chiens ! Vous pensiez que j’allais me taire ?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "BetsiPrice_2_1":
			dialog.text = "Et toi... Tu ne sembles pas être avec eux. Qui es-tu ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+", à votre service.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Donc, je te dois la vie ?";
			link.l1 = "On dirait bien. Mais ce qui est plus important maintenant, c’est : qui sont ces gens, et dans quoi t’es-tu embarquée ?";
			link.l1.go = "BetsiPrice_3";
		break;

		case "BetsiPrice_3":
			dialog.text = "Ces gens... Ils ont été envoyés par un haut fonctionnaire anglais. Il fut un temps où il m'était très proche... et maintenant, comme tu le vois, il veut ma mort.";
			link.l1 = "Je crois que je commence à comprendre ton histoire. Tu étais sa maîtresse, mais à un moment tu as décidé de te servir de cela pour ton intérêt. Tu voulais le faire chanter... tout raconter à sa famille ?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Tu es étonnamment proche de la vérité, "+GetSexPhrase("beau gosse","jolie fille")+"... et en même temps très loin. Si c'était le cas, je serais déjà morte. Oui, j’étais sa maîtresse, mais jamais je n’ai pensé à déclencher un drame familial\nC'était bien plus compliqué : un jour, j’ai appris qu’il s’était trouvé un nouveau jouet et voulait se débarrasser de moi, me laissant sans rien. Me jeter comme une chose inutile. Mais moi, je n’ai jamais eu l’habitude de partir les mains vides\nAlors j’ai pris ce qui avait vraiment de la valeur – des documents capables de ruiner sa vie – et j’ai fui vers le Nouveau Monde. Ensuite, je lui ai proposé un marché : ses secrets contre ma sécurité et une compensation généreuse\nC’est pour cela que je suis encore en vie – ils ont besoin des documents. Et moi, je n’étais pas pressée de révéler où ils sont cachés.";
			link.l1 = "Eh bien, tu n’es pas seulement belle, tu es aussi sacrément rusée. Tu as joué gros, mais soyons honnêtes – cette partie t’échappe déjà. Peut-être qu’il est temps de penser à une autre option, tant qu’il est encore possible de quitter la table ? Si ils t'ont retrouvée ici, tu ne pourras pas te cacher ailleurs. Tôt ou tard, ta chance va tourner.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "Et que proposes-tu ? Lui remettre les documents et rester les mains vides ? Après tout ce que j’ai traversé ?";
			link.l1 = "Tu sais très bien qu’à leurs yeux, tu n’es qu’un problème à éliminer. Ils ne s’arrêteront pas tant qu’ils n’auront pas ce qu’ils veulent. Mais tu as encore le choix. Donne les documents à ce crétin là-bas. Qu’il les remette à son maître, et qu’il lui dise que tu as renoncé à tes projets – que tu veux juste que tout cela se termine.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Si c’est ma seule chance... D’accord, je suis prête à prendre le risque. J’ai toujours gardé les documents sur moi. Je les ai cousus dans mon corset pour ne jamais m’en séparer. Attends une seconde...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Tiens, prends-les. Ce sont tous les documents que j'avais. Tu veux dire deux mots à ce sale type ? Tu sais comment être convaincant"+GetSexPhrase("","e")+" ?";
			link.l1 = "Je pense qu’il a déjà retenu la leçon principale. Il ne reste plus qu’à s’assurer qu’il comprenne bien ce qu’il doit faire.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Écoute-moi bien, enfoiré. Voilà les documents que vous cherchiez. Apporte-les à ton maître et dis-lui : s’il continue à envoyer des tueurs après la tête de Betsy, ils connaîtront le même sort que tes copains. Dis-lui qu’elle sort de sa vie à jamais – et qu’il n’a plus aucune raison de la poursuivre. Qu’il considère cela comme un geste de réconciliation volontaire de sa part. J’espère qu’il sera assez intelligent pour en rester là. Tu as compris, ou je dois te l’enfoncer dans le crâne ?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "J’ai compris, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Alors fous le camp. Et ne traîne pas – tu n’auras pas de seconde chance.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Eh bien, "+GetSexPhrase("mon héros","ma furie")+", il me semble que j’ai oublié de te remercier... C’est l’émotion. Ce n’est pas tous les jours qu’on est prise en otage puis libérée par un"+GetSexPhrase("","e")+" "+GetSexPhrase("courageux sauveur","courageuse sauveuse")+". Dis-moi, c’est une habitude chez toi de venir en aide aux demoiselles en détresse, ou ai-je juste eu une chance incroyable ?";
			link.l1 = "Que puis-je dire, Betsy ? J’ai un faible pour les entrées dramatiques et "+GetSexPhrase("les belles dames","toutes sortes d’aventures")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Je m’appelle Miranda. Miranda Bell. J’ai pris le nom de Betsy quand j’ai dû disparaître – nouvelle vie, nouveau nom, tu comprends. J’ai fui l’Europe si précipitamment que je n’ai emporté que quelques pièces et deux-trois bijoux\nLe reste, sans doute, est tombé entre les mains de ces salauds qui me poursuivaient. Maintenant, au lieu de réceptions luxueuses et de robes chères – une cabane misérable en bordure de ville et un emploi de serveuse dans une taverne. Je n’aurais jamais pensé qu’un jour je servirais du rhum au lieu de savourer du vin en bonne compagnie...";
			link.l1 = "Même ainsi, tu donnes l’impression d’avoir ta vie bien en main. Peut-être est-ce là ton vrai talent.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Flatteur. Mais tu sais, ça te va bien","Tu me flattes")+"... Après tout ça, j’ai une drôle d’impression. Et si quelqu’un m’attendait déjà au coin de la rue ? Raccompagne-moi chez moi, sois encore "+GetSexPhrase("mon sauveur","ma sauveuse")+" un petit moment.";
			link.l1 = "Je ne suis pas du genre à laisser une mission inachevée. Donc, madame, je suis à votre service. Allons-y.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Nous y voilà. Tu sais, je ne t’ai même pas demandé ce qui t’a conduit dans cette maison ?";
			link.l1 = "Je n’"+GetSexPhrase("étais","étais")+" pas là par hasard. Le tavernier semblait vraiment inquiet de ta disparition et m’a demandé d’enquêter. Et moi, refuser ? Abandonner une dame en détresse ? Ce serait indigne d’un capitaine.";
			link.l1.go = "BetsiPrice_12";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "Je n’"+GetSexPhrase("étais","étais")+" pas là par hasard. Ce pendentif m’a conduit là-bas. Prends-le.​ Le tavernier semblait vraiment inquiet de ta disparition et m’a demandé d’enquêter. Et moi, refuser ? Abandonner une dame en détresse ? Ce serait indigne d’un capitaine.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "Ah, c’est si noble, capitaine "+pchar.name+" ! Quant au tavernier, je suis sûre qu’il s’inquiétait plus pour ses recettes que pour moi. Hélas, je ne peux pas t’inviter ce soir – il me faut du repos. Le temps passé à la cave n’a certainement pas embelli mon visage. Mais si nous ne nous revoyons pas – je ne te le pardonnerai pas. Alors viens demain à la taverne, j’aurai un... cadeau pour toi.";
			link.l1 = "Eh bien, voilà une raison de plus d’y passer. À demain, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ah, c’est si noble, capitaine "+pchar.name+" ! Quant au tavernier, je suis sûre qu’il s’inquiétait plus pour ses recettes que pour moi. Hélas, je ne peux pas t’inviter ce soir – il me faut du repos. Le temps passé à la cave n’a certainement pas embelli mon visage. Mais si nous ne nous revoyons pas – je ne te le pardonnerai pas. Alors viens demain à la taverne, j’aurai un... cadeau pour toi.";
			link.l1 = "Eh bien, voilà une raison de plus d’y passer. À demain, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Eh bien... Quel adieu touchant. Qui est cette pauvre dame ? On dirait qu’elle a passé une semaine dans une cave, et malgré ça, tu la dévorais des yeux, hein, "+pchar.name+" ?";
			link.l1 = "Ce n’est pas ce que tu crois. Cette fille était dans une sale situation, et je l’ai simplement aidée à s’en sortir. Rien de plus.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "Et bien sûr, tu as décidé d’être son chevalier en armure brillante ?";
			link.l1 = "Tu sais bien que je ne peux pas rester sans rien faire quand quelqu’un est en danger.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Très bien. Mais la prochaine fois, "+pchar.name+", sois plus prudent... et ne me donne pas de raisons d’être jalouse.";
			link.l1 = "Bien sûr, ma chérie. Allons-y, on a encore beaucoup à faire.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Eh bien... Quel adieu touchant. Tant d’attention, de douces promesses... Tu l’appelles même tendrement par son prénom, ouais, hein ?. Peut-être que moi aussi je devrais disparaître quelques jours, pour que tu me cherches avec autant de ferveur ?";
			link.l1 = "Mary, tu sais que tu es mon étoile polaire, et elle... ce n’était qu’une fille en détresse.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ah, bien sûr ! Une pauvre fille qui avait besoin d’un chevalier ! Et ce regard – c’était juste par politesse ? Tu l’as presque déshabillée du regard !";
			link.l1 = "Mary, tu exagères ! Regarde comment je te regarde, toi. Tu vois la différence ? Ou dois-je te le rappeler... de plus près ?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Très bien, "+pchar.name+", tu t’en tires cette fois, ouais, hein. Mais si je revois une scène comme celle-là...";
			link.l1 = "Alors je devrai te rappeler encore une fois qui occupe la première et unique place dans mon cœur. Allons-y, ma chère, nous avons encore du travail.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... Tu n’imagines pas les pensées qui me traversent l’esprit quand je suis si près de toi... Et à quel point j’ai envie de les réaliser.";
					link.l1 = "Alors arrête d’y penser seulement... et montre-moi chacune d’elles.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, mon"+GetSexPhrase(" cher","e chère")+"... Tu n’imagines pas comme il m’est difficile de me contrôler quand tu es là...";
					link.l1 = "Alors assez de cette douce torture... Viens vers moi...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ah, "+GetSexPhrase("mon doux capitaine","ma douce "+pchar.name)+"... Je suis encore toute entière dans cette douce folie.";
					link.l1 = "Peut-être que cette folie vaut la peine d’être gravée dans la mémoire... ou même répétée un jour.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Oh, "+pchar.name+"... Si je dis que c’était incroyable, tu ne vas pas devenir trop suffisant"+GetSexPhrase("","e")+"?";
					link.l1 = "Seulement si tu promets de me le redire... à voix basse.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}