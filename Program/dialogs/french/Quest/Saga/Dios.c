// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Veux-tu quelque chose ?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"Dis-moi, es-tu Jose Dios, le cartographe?";
				link.l3.go = "island";
			}
			link.l1 = "Non, rien.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Oui, c'est moi. Je ne vous connais pas, señor. Que voulez-vous de moi ?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+" et j'ai été envoyé par Jan Svenson. Vous vous souvenez de lui ?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ah, señor Svenson ! Bien sûr, je me souviens de lui ! Venez, mettez-vous à l'aise... Comment va le respecté Jan ?";
			link.l1 = "Merci, il se porte bien. Señor Dios, j'ai besoin de votre aide. Je souhaite vous consulter sur une affaire dont vous devez être familier en raison de votre profession. Jan vous a recommandé comme expert en géographie de la région des Caraïbes...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "Je vous écoute, Señor. Que voulez-vous savoir sur la géographie de l'archipel ?";
			link.l1 = "Ils disent qu'il y a une île ou une autre sorte de formation au nord-ouest de La Havane, entre Cuba et le golfe du Mexique. Cette île n'a jamais été tracée sur aucune carte. J'aimerais connaître la véracité de ces rumeurs.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... Vous avez posé une question qui me tourmente depuis de nombreuses années. Cet endroit que vous avez mentionné attire depuis longtemps les esprits curieux des géographes, mais personne n'a jamais été assez courageux pour explorer cette région.";
			link.l1 = "Pourquoi ?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "La chose est que l'endroit est une sorte d'anomalie naturelle. La probabilité de tempêtes dans cette région est bien plus élevée qu'ailleurs. Peut-être que la raison réside dans le courant marin froid, mais ce n'est que mon hypothèse. Beaucoup de navires y ont disparu et cela a suffi pour que les marins évitent cet endroit, toutes les principales routes maritimes passent de toute façon loin de cette région.";
			link.l1 = "Je suppose que vous ne connaissez pas non plus la vérité...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Exactement, Senor. Mais j'ai quelques documents historiques et des preuves matérielles, donc j'ai tous les droits de soupçonner une forte probabilité de l'existence de cet endroit.";
			link.l1 = "Peux-tu m'en dire plus ?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Bien sûr. La preuve la plus importante est le document historique avec des extraits du journal du capitaine Alvarado qui a visité l'île en 1620. Une histoire plutôt intéressante, je vous le dis !";
			link.l1 = "Capitaine Alvarado ? C'est la deuxième fois que j'entends ce nom...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "Je ne suis pas surpris. L'histoire du capitaine Alvarado fait partie du folklore depuis des années. Elle a changé, s'est remplie de rumeurs, de mensonges et de rêves, alors la voici - la légende de l'Île des Navires Abandonnés.\nLes commérages peuvent changer, mais le papier et l'encre ne le peuvent pas, ils restent intacts pendant des centaines d'années. Ici, lis cette histoire - peut-être t'aidera-t-elle à dévoiler ce que tu cherches.";
			link.l1 = "Merci ! Tu as autre chose ?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "Il y a une théorie selon laquelle le fond de la mer dans cette région s'élève suffisamment pour former un vaste banc de sable. Et j'ai déjà mentionné le courant. Il y a aussi une grande accumulation de mouettes et d'autres oiseaux de mer selon les dires des marins.\nAlvorado a mentionné les noms de navires qui faisaient partie de l'escadre de l'amiral Francisco Betancourt, une escadre qui a disparu il y a plus de cinquante ans. Je doute que ce soit juste une coïncidence...";
			link.l1 = "Je retournerai à mon navire et lirai attentivement les notes d'Alvarado. Merci pour votre aide, Señor Dios !";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "De rien. En fait, je ne vous ai pas du tout aidé, vous n'avez pas les coordonnées de l'endroit et moi non plus. Je ne peux même pas prouver qu'il y a une île habitée là-bas. Mais d'après ce que je comprends, vous avez l'intention d'explorer cette région?\nSi c'est le cas, sachez que je vous serai vraiment reconnaissant pour toute information, surtout si elle est accompagnée de preuves matérielles. Il semble que vous soyez un homme riche, mais je trouverai un moyen de vous rembourser.";
			link.l1 = "Bien. Alors, nous avons un accord, Señor Dios. Peut-être que mes notes seront aussi lues par quelqu'un dans le futur... Et quelqu'un pourrait même écrire une légende...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Pourquoi pas ? Señor "+pchar.name+", je vois que vous êtes un homme aventureux qui voyage beaucoup, donc je veux vous demander de faire quelque chose.";
			link.l1 = "Oui? Je t'écoute.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "Tu sais que je suis cartographe. Ainsi, j'ai dessiné des cartes de l'archipel des Caraïbes pendant deux ans, compilant l'atlas de l'amiral pour le concours du Vice-Roi de Nueva Granada. Mais toutes mes vingt-quatre cartes ont été volées de ma maison de la manière la plus insolente pendant que j'étais capturé par des pirates, ceux dont le señor Svenson m'a sauvé. Je suis sûr que l'attaque a été organisée par un de mes concurrents afin d'acquérir mes cartes. Cela fait longtemps, mais je n'ai pas revu une seule carte de mon ensemble.";
			link.l1 = "Je vois. Vous voulez que je vous rende vos cartes.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Exactement. Peut-être les trouverez-vous lors de vos futures aventures. Il est facile de les reconnaître - mon signe est sur chacun d'eux. Je vous récompenserai généreusement si, par miracle, vous parvenez à rassembler les vingt-quatre cartes.";
			link.l1 = "D'accord. Je vais désormais examiner attentivement chaque carte que je trouverai dans l'archipel. Eh bien, je dois y aller maintenant. Merci pour cette conversation intéressante et pour le document.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, c'est vous, señor "+GetFullName(pchar)+"Tu as quelque chose d'intéressant à me raconter ?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"¡Seigneur Dieu, s'il vous plaît, jetez un œil à la carte que j'ai trouvée. Cela doit être l'une de vos cartes selon le signe.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"¡Señor Dios, j'ai de bonnes nouvelles pour vous. J'ai pu réunir la collection complète de vos cartes uniques, tout comme vous le souhaitiez. Voici les vingt-quatre cartes.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"Oui, je l'ai fait. J'étais à cet endroit mystique dont nous parlions.";
				link.l4.go = "LSC";
			}
			link.l9 = "Rien jusqu'à présent, Señor. Je voulais juste voir comment vous vous portez.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Montrez-moi... (en regardant) Bien sûr ! C'est l'une de mes cartes pour l'atlas de l'amiral ! Capitaine, je vous demande vraiment de les trouver toutes ! Je comprends que c'est presque impossible mais quand même... Je ne veux pas perdre espoir.";
			link.l1 = "Ne le perds pas, Senor. J'ai trouvé cette carte, donc il y a une chance que je trouve aussi le reste. Ils sont toujours dans les Caraïbes.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Ton optimisme me réchauffe le cœur, Señor capitaine. Peut-être aurai-je encore l'occasion de montrer à don Juan de Cordova qui est le meilleur cartographe de l'archipel !";
			link.l1 = "Vous pourrez battre tous vos concurrents malveillants. Les cartes sont vraiment merveilleuses... Adieu, Senor !";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "Je n'en crois pas mes yeux ! Les as-tu vraiment trouvés ? Tous ?";
			link.l1 = "Oui. Ce n'était pas facile, mais la chance m'a tout de même souri dans cette entreprise. Prenez vos cartes. Elles sont magnifiques, chacune surpasse de loin toutes celles que j'ai vues jusqu'à présent.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "Incroyable! C'est tout simplement incroyable! Pour être honnête, je n'ai jamais cru que ce moment arriverait.";
			link.l1 = "Pendant que je respire, j'espère, Seigneur Dios. Vous pouvez affronter don Cordova maintenant. Je suis sûr qu'il appréciera grandement vos talents.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "Vous avez mes remerciements, Capitaine ! Vous ne réalisez même pas quel grand service vous m'avez rendu. Et comme je l'ai promis - je vous récompenserai. J'ai aussi un cadeau pour vous. Je pense qu'en tant que marin, vous le trouverez très utile.";
			link.l1 = "Vous m'avez intrigué, Señor !";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "Voici ! C'est une longue-vue de ma conception. Elle est unique et vous n'en trouverez pas d'autre comme celle-ci ailleurs. Les lentilles ont été fabriquées en Europe par le maître le plus habile d'Espagne. Son boîtier a été réalisé par un armurier ami. Un trépied spécial vous aidera à pointer l'appareil malgré le roulis. Vous pouvez voir tout ce dont vous avez besoin, que ce soit un navire ou un fort.";
			link.l1 = "Quel cadeau merveilleux ! Merci, Señor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Utilise-le, Capitaine Señor. J'espère que ma longue-vue te sera utile.";
			link.l1 = "Sans doute ! J'ai hâte de l'installer sur le pont de mon navire et de regarder à travers.";
			link.l1.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "De plus, puisque les choses ont pris cette tournure, j'ai encore une petite proposition à vous faire.";
			link.l1 = "Laquelle ? Je vous écoute très attentivement.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "Il m'est venu à l'esprit que ces cartes sont excellentes pour un explorateur, mais qu'elles ne fournissent pas tout ce dont un capitaine de marine a besoin. Voyez-vous : toutes les baies, caps et lagunes y sont représentés avec précision, mais elles ne permettent pas de tracer une route entre les îles.";
			link.l1 = "C’est vrai, on ne peut pas y déterminer une route.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "Mais je peux aussi te faire une carte de l'archipel ! Et pas du genre que tu peux acheter à la Compagnie néerlandaise des Indes occidentales, mais une carte unique et excellente.";
			link.l1 = "Merci, senor Dios, mais je n'ai pas besoin d'une telle carte. Cependant, merci beaucoup pour l'offre !";
			link.l1.go = "best_map_02";
			link.l2 = "Tu plaisantes, n'est-ce pas ? Seigneur Dieu, comment pourrais-je refuser ? Dis-moi juste ce dont tu as besoin - je n'épargnerai ni argent ni outils !";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Eh bien, je devais proposer. En tout cas, ce fut un plaisir de faire affaire avec vous, señor "+pchar.lastname+" !";
			link.l1 = "De même ! Bonne chance à vous !";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "J'ai déjà les outils, merci. Il me faudra une carte standard de l'archipel, ainsi qu'une boussole et un chronomètre étalonné : la carte doit être précise, sinon ce serait du sabotage. Et comme paiement – un coffre rempli de doublons.";
			if(CheckAMapItems())
			{
				link.l1 = "J'ai déjà tout ce que vous avez demandé. Tenez.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "Une carte standard de l'archipel, une boussole, un chronomètre étalonné, et un coffre de doublons. C'est noté ! Je vous les apporte au plus vite, attendez-moi !";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Salutations, mon cher ami ! Avez-vous apporté la carte standard de l'archipel, la boussole, le chronomètre étalonné et le coffre de doublons ?";
			link.l1 = "Pas encore, Señor Dios. Mais je l'apporterai certainement !";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Oui, Señor Dios. Tenez, tout est là.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Eh bien, alors je vais m'atteler à la tâche. Reviens me voir dans une semaine, et je te promets que tu ne le regretteras pas !";
			link.l1 = "Je n'ai aucun doute, Señor. À la semaine prochaine !";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ah, vous voilà, Señor "+pchar.lastname+" ! J’ai le plaisir de vous annoncer que j’ai terminé la carte de l’archipel ! Et permettez-moi de vous assurer qu’elle est bien meilleure que celle que vous m’avez remise.";
				link.l1 = "Mon ami... Cette carte est stupéfiante ! C’est, osons le dire, un chef-d’œuvre ! Comment pourrais-je vous remercier pour tout ce que vous avez fait pour moi ?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Bienvenue, Señor ! Je vous prie de m’excuser, mais la carte n’est pas encore prête.";
				link.l1 = "Oui, je me souviens que vous avez besoin d’une semaine. Je voulais simplement prendre de vos nouvelles.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Allons donc, mon ami. Ce fut un plaisir pour moi de créer de telles cartes pour un noble capitaine qui les apprécie véritablement. Ah oui, vous pouvez récupérer votre copie de la carte ordinaire. Bonne chance sur les hautes mers !";
			link.l1 = "Un immense merci à vous ! Vous avez raison, cette carte est tout simplement inestimable pour moi. Au revoir, Señor Dios !";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Vraiment ?! L'avez-vous trouvé ? Installez-vous confortablement, je pense que la conversation à venir prendra un certain temps, n'est-ce pas ?";
			link.l1 = "J'ai vraiment beaucoup à vous raconter sur l'île. Mais d'abord, je veux que vous me promettiez quelque chose. Je vois que vous êtes un homme d'honneur, donc je suis sûr que vous tiendrez parole...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "De quoi parlez-vous, Capitaine ?";
			link.l1 = "Il y a des gens qui y vivent... et ils ne seront pas contents si quelqu'un se mêle de leur vie. Je ne pense pas que l'arrivée possible d'une escadrille de 'recherche' sera bien accueillie.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "Alors, je veux que vous me donniez votre parole d'honneur que vous ne publierez aucune information pouvant être utilisée pour trouver l'île dans les dix années suivant notre conversation. Vous êtes libre de publier toute information sur les habitants, leur vie, etc., mais ne révélez pas l'emplacement de l'île.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "Je suis d'accord, Capitaine. Je vous donne ma parole de gentilhomme que je ne révélerai à personne ni l'emplacement de l'île ni aucune information qui pourrait nuire à ses habitants durant les dix prochaines années.";
			link.l1 = "Ecoutez donc mon histoire. Ecrivez-la si vous voulez. Alors, l'île est faite de nombreux navires échoués dont les coques reposent sur un large banc de sable...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Incroyable ! Vous m'avez donné des informations très précieuses, Capitaine ! Les descendants de l'amiral de Betancourt vivent sur l'île ! Maintenant, nous savons ce qui est arrivé à son escadron. Et il y a désormais une tache blanche de moins sur la carte de l'archipel des Caraïbes... Merci beaucoup pour votre récit, "+pchar.name+" !";
			link.l1 = "Voyez-vous maintenant pourquoi je vous ai demandé d'être vraiment prudent en racontant mes informations ?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "Je vois. Vous pouvez être sûr que je tiendrai parole. Dites-moi... avez-vous des attributs matériels de l'île ?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "J'ai des instructions de navigation pour l'Île des Navires Abandonnés. Tiens, regarde. Elles te permettent de faire passer un petit navire à travers les récifs et les débris et d'accoster en toute sécurité sur l'Île. Il est impossible d'atteindre l'Île sans ces instructions.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Malheureusement, je n'en ai pas.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(en regardant) Quel excellent document ! Il a été dessiné par un homme expert en cartographie. Même moi, je n'aurais pas pu faire mieux. Incroyable ! Capitaine, pourquoi ne me donnez-vous pas ces instructions de navigation ? Une histoire est une histoire, mais ce papier doit être montré aux géographes les plus célèbres du Vieux Monde !";
			link.l1 = "Señor Dios, malheureusement, j'ai besoin de ce document pour moi-même. Comme je l'ai déjà dit, il est impossible de traverser les récifs entourant l'île sans lui. Mais vous pouvez en faire une copie des instructions si vous le souhaitez, et je serai heureux si vous les avez également en votre possession.";
			link.l1.go = "LSC_10";
			//link.l2 = "Seigneur Dieu, malheureusement, j'ai besoin de cet objet pour moi-même. Comme je l'ai dit, il est impossible de contourner les récifs autour de l'île sans lui. Je le sacrifierais au nom de la science, mais... je suis sûr que vous comprenez.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Absolument. C'est votre droit, bien que ce soit dommage... Quoi qu'il en soit, merci pour votre histoire ! Vous avez rendu un grand service aux géographes, cartographes et autres curieux.";
			link.l1 = "De rien, Señor. Eh bien, je dois y aller maintenant. Adieu.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "Quel dommage... Quoi qu'il en soit, merci pour votre histoire ! Vous avez rendu un grand service aux geographes, cartographes et autres curieux.";
			link.l1 = "Je vous en prie, Señor. Eh bien, je dois y aller maintenant. Adieu.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Bien sûr, "+pchar.name+"Vous avez consacré beaucoup de votre temps pour moi. Transmettez mes salutations à Señor Svenson !";
			link.l1 = "Adieu, Señor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Merci beaucoup ! C'est très aimable de votre part. Accordez-moi un peu de temps...";
			link.l1 = "{\n    \";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Merci beaucoup ! C'était fort aimable de votre part. Maintenant, nous avons non seulement des preuves orales mais aussi matérielles... Je ne vous laisserai pas sans récompense, Capitaine. J'ai un petit cadeau pour vous.";
			link.l1 = "Quel genre de cadeau ?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Je suis passionné non seulement par la cartographie et la géographie, mais aussi par les mathématiques et l'astronomie. Il m'a fallu un an pour essayer de créer un outil universel pour prendre la latitude et la longitude. Et j'ai fait quelques progrès. Regardez :\nCeci est mon sextant. Je l'ai conçu moi-même. Le problème, c'est qu'il ne fonctionne pas. Il nécessite un chronomètre extrêmement précis. Même ceux qui ont été fabriqués par les meilleurs artisans donnent des erreurs inacceptables avec le temps. Par conséquent, mon outil est inutile pour l'instant.\nMais puisque vous voyagez beaucoup, peut-être trouverez-vous un chronomètre suffisamment précis pour que le sextant fonctionne. Une fois que vous aurez trouvé une telle horloge, vous n'aurez plus besoin de boussole, de compas, d'astrolabe, de sabliers et autres chronomètres médiocres - mon outil les remplacera tous.";
			link.l1 = "Merci, Senor Dios. Espérons que je trouverai un chronomètre qui fera fonctionner votre invention. J'aimerais avoir un tel dispositif... en état de marche. Eh bien, je dois y aller maintenant. Adieu.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vous êtes "+GetSexPhrase("un voleur, je vois ! Gardes, saisissez-le","un voleur, je vois ! Gardes, saisissez-la")+"!!!","Je n'en reviens pas ! J'ai détourné le regard une seconde - et tu te plonges dans mes affaires ! Arrêtez le voleur !!!","Gardes ! Au voleur ! Arrêtez le voleur !!!");
			link.l1 = "Aaaah, diable!!!";
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
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}