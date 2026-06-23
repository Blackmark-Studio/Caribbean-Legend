// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que veux-tu ?","Que voulez-vous savoir ?"),"Que voulez-vous, "+GetAddress_Form(NPChar)+"?","C'est la troisième fois que tu essaies de me demander...","J'en ai assez de toi, va-t'en !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Désolé, j'ai changé d'avis.","Ce n'est rien, mes excuses."),"J'ai oublié, mes excuses...","La troisieme fois est la bonne, hein? Excusez-moi...","Désolé, désolé ! Je vais m'en aller alors...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Ecoute, une frégate sous le commandement de Miguel Dichoso était dans les parages en avril 1654, puis elle a disparu. Peux-tu m'en dire plus sur son navire ? Peut-être as-tu vu ce qui lui est arrivé ou où il est allé ? Te souviens-tu de quelque chose ?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Aye, Señor, c'était un spectacle à couper le souffle! On n'oublie pas des choses pareilles, ha!";
			link.l1 = "Peux-tu me dire ce qui s'est passé ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "La frégate du Senior Dichoso jeta l'ancre dans le port de San Jose. J'avais une bonne vue pour tout voir, aye. Je te dis, c'était une excellente frégate, un chef-d'œuvre, je le jure sur mon cœur saignant ! L'équipage se vantait de la vitesse, elle pouvait filer jusqu'à seize nœuds !\nIls ont passé une journée ici, puis ont mis les voiles directement vers l'île de Tobago. Ensuite, tu ne croirais pas, des choses étranges ont commencé à se produire avec le temps dès qu'ils ont disparu derrière l'horizon. Le temps était beau depuis des jours alors, pas un seul nuage !\nEt pourtant cette terrible tempête est sortie de nulle part. On aurait dit que Neptune lui-même nous avait rendu visite, c'est sûr ! Je suis monté en haut de mon phare pour l'allumer, mais alors je l'ai vue... Santa Quiteria ! Elle se précipitait sur d'énormes vagues accompagnée d'une tornade géante !\nLa frégate a volé près de mon phare comme une étincelle puis a été emportée par la tempête vers le Nord-Ouest ! Personne n'a vu Santa Quiteria depuis ce jour. Juste une heure plus tard, le vent, la pluie et les nuages avaient disparu et le soleil brillait, pas un seul signe de la tempête ! Jamais rien vu de tel ! Bien que j'ai ramassé tant d'ambre dans ma baie ce jour-là...";
			link.l1 = "La tempête a donc ramené la frégate dans la mer des Caraïbes ? ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Il l'a fait ! Bien loin par là-bas vers la Martinique. Je doute que Dichoso ait pu survivre à cette tempête, mais il faisait de son mieux ! La frégate ne coulait pas, mais la Santa Quiteria doit être au fond de la mer parmi les coraux à présent... En fait, vous n'êtes pas la première personne à me demander des nouvelles de Dichoso et de sa frégate.";
			link.l1 = "Vraiment ? Qui d'autre s'intéressait à Miguel ?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Un capitaine audacieux de la flotte espagnole, rien de moins ! Il s'est présenté comme... oh... j'ai fait et oublié... Ah ! Señor Diego. Son nom était Diego, mais son nom de famille... de Montagna ou de Montoya. Quelque chose comme ça. Il m'écoutait tout comme vous, m'a remercié et est parti. Je ne l'ai jamais revu depuis.";
			if (int(Pchar.money) >= 5000)
			{
				link.l1 = "Je vois. Merci beaucoup pour votre histoire, vous m'avez beaucoup aidé. Acceptez ma gratitude en pièces. Adieu.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Je vois. Merci beaucoup pour votre histoire, vous m'avez beaucoup aidé. Adieu.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
