// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu as essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"... ","Tout au long de cette journée, c'est la troisième fois que tu parles d'une question...","Plus de questions, je suppose ?","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, où est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "On dit que quelqu'un vous a privé de votre précieux gin. Ou bien les rumeurs sont-elles fausses ?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Bonnes nouvelles, "+npchar.name+" ! J'ai retrouv"+GetSexPhrase("é","ée")+" votre tonneau !";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Hélas, c'est vrai. Qu'avez-vous entendu d'autre ? Vous savez quelque chose ? Je vous en supplie, dites-moi que vous savez où le trouver. Si je ne le retrouve pas... je devrai quitter la ville. Soit je pars moi-même, soit on m'emportera dans un cercueil.";
			link.l1 = "Hmm... On dirait que vos affaires vont vraiment mal, l'ami. Non, je n’ai entendu parler de votre malheur qu’en passant"+GetSexPhrase("","e")+". Comment avez-vous pu perdre une chose qui vous tenait tant à cœur ?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "Ah... Que dire... Volé juste sous mon nez ! Le matin, le tonneau était bien là. On me l’a livré avant-hier, et pour mieux dormir, je l’ai emporté chez moi pour la nuit. Le lendemain, je l’ai ramené et placé sous le comptoir. Et le soir, disparu ! Comme s’il s’était envolé ! Personne n’a rien vu, personne n’a rien entendu.";
			link.l1 = "Eh bien, ça alors...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "Si j’avais le moindre indice, je serais déjà parti à sa recherche. Mais non, rien – comme si ce tonneau était trop précieux pour ce monde et que les cieux l’avaient emporté. Je suis prêt à payer cent cinquante doublons à quiconque me le ramènera. Mieux encore, je mettrai une plaque à son nom dans la taverne pour que tout le monde connaisse son exploit !";
			link.l1 = "Je vais essayer de vous aider. Et pour la plaque, on en reparlera. Dites-moi plutôt : qui savait pour le tonneau ? Et qui, à part vous, aurait pu accéder au comptoir ?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Cent cinquante doublons pour un tonneau ? Amusant. Mais ce n’est pas mon affaire. Débrouillez-vous.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "Eh bien, personne, en vérité ! Sauf peut-être ma serveuse, mais c’est impossible. Ce jour-là, la taverne était en pleine fête – l’équipage du 'Sea Wolf' est revenu de chasse avec une belle prise. Elle n’a pas eu une minute pour souffler, encore moins pour traîner derrière le comptoir.";
			link.l1 = "Vous en êtes sûr ?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Absolument ! Elle n’a pas supporté ce rythme infernal, et le soir, elle était à cran. Un des marins a commencé à la draguer, et elle a hurlé si fort que tout le monde en a eu les oreilles bouchées. J’ai dû quitter le comptoir pour calmer tout ce monde. Et pourtant, d’habitude elle réagit bien plus calmement à ce genre d’imbécilités.";
			link.l1 = "Et c’est tout ? Rien d’autre de notable ce jour-là ?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "Pendant que je gérais cette première crise, une bagarre a éclaté – deux marins se sont empoignés dans le coin de la taverne. Mais la rixe n’a pas duré : ils étaient visiblement du même équipage et ont été vite séparés. Après ça, tout s’est calmé pour de bon, rien de plus à signaler.";
			link.l1 = "Très bien, je vais commencer les recherches. Attendez. Je pense que ce tonneau sera bientôt de retour sous votre, hum... surveillance vigilante.";
			link.l1.go = "OS_Tavern1_7";
		break;
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Vous l'avez trouvé ?! Est-ce vraiment possible ? Capitaine, vous avez littéralement sauvé ma vie ! Qui était derrière tout ça ? Je dois connaître le nom de ce scélérat !";
			link.l1 = "C'était une machination méticuleusement planifiée par un certain Jack Veils, de connivence avec le capitaine du 'Sea Wolf'. Ils ont mobilisé leurs marins et monté une véritable mise en scène pour vous distraire. Quand vous avez quitté votre poste, le tonneau est resté sans surveillance, et ils l'ont volé sans difficulté.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Incroyable ! Jack Veils ! Alors il est revenu... Et il semble qu'il ait voulu récupérer la taverne par de tels moyens sournois. Ce renard ne renonce jamais !";
			link.l1 = "Donc il a été autrefois le propriétaire de cette taverne ? Soyez rassuré, il ne complotera plus. Je l'ai envoyé rejoindre son créateur"+GetSexPhrase("","e")+".";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Capitaine ! C'est extraordinaire ! Vous... vous m'avez libéré de la crainte constante qui assombrissait mes jours ! J'ai toujours su qu'il reviendrait tôt ou tard... Il y a quelques années, nous étions rivaux pour la propriété de cette taverne, et il avait réussi à me surpasser\nMais la joie de la victoire a causé sa perte – dans son excès de célébration, il a sans le savoir joué l'établissement aux cartes et l'a perdu en ma faveur. Bien sûr, le matin venu, il est arrivé en courant, suppliant de récupérer la taverne, promettant tout et n'importe quoi\nMais je ne suis pas assez idiot pour accepter de telles conditions. Puis il a disparu... Je savais qu'il ne laisserait pas l'affaire en repos. Je sentais qu'il reviendrait un jour. Et maintenant, ce jour est arrivé.";
			link.l1 = "Il faut lui reconnaître ce mérite – il a exécuté son stratagème avec ruse.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Attendez un instant ! Comment a-t-il même appris l'existence du tonneau ? Il semble... il semble que je commence à comprendre ! La serveuse ! C'est pour cela qu'elle s'est enfuie comme un chat échaudé, sans même dire au revoir. Elle a dû apprendre que vous aviez réglé son compte à Jack. Maintenant tout s'explique. Capitaine, je vous suis redevable au-delà de toute mesure, vous...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
