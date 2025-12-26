// диалог освобожденных каторжников рудника
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
			dialog.text = NPCStringReactionRepeat("Você de novo, señor?","Ouça, senhor, é melhor o senhor ir embora...","Não me incomode, senhor! Peço-lhe com gentileza.","Ah, eu não aguento isso... Até remar numa galé era melhor.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim, sou eu de novo.","Não me diga o que fazer.","E se eu continuar incomodando?","Então volte para a cozinha!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "O que você quer, señor?";
				link.l1 = "De você? Nada, imagino. Só queria cumprimentar.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Não desafie o destino, camarada! Guarde sua arma!","Ouça, eu sou cidadão desta cidade e estou pedindo que guarde sua espada.");
			link.l1 = LinkRandPhrase("Tudo bem...","Como quiser...","Como quiser...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
