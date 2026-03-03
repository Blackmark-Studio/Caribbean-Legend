//Jason общий диалог индейцев на улицах
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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Rostinho Pálido","Índia branca")+" quer conversar?","Você de novo, "+GetSexPhrase("cara-pálida","squaw branca")+".",""+GetSexPhrase("Rostinho pálido adora falar. Igual a uma índia.","Índia branca adora conversar.")+"","O Grande Espírito trouxe o rosto-pálido"+GetSexPhrase("irmão","irmã")+" para mim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim.","Sim, sou eu de novo.","Muito poético.","Também estou feliz em te ver.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Olá, irmão branco. Você quer conversar com o índio?";
				link.l1 = "Saudações, filho da selva. Fico feliz em te ver, mas preciso ir.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Não provoque os espíritos, cara-pálida! Guarde essa faca comprida!","Não corra para a morte, cara-pálida! Guarde essa faca comprida!");
			link.l1 = LinkRandPhrase("Certo.","Como quiser.","Como quiser.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
