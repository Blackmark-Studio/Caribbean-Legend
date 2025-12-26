// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pergunte o que quiser.","Estou ouvindo, qual é a pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, desculpe.","Agora não. Lugar e hora errados."),"É verdade, não tenho nada a dizer no momento, desculpe.","Vou perguntar depois.","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Vossa Excelência, havia uma fragata sob o comando de Miguel Dichoso em abril de 1654. Desde então, ele desapareceu. O senhor se lembra de algo sobre ele? Talvez ele tenha lhe visitado, conversado com o senhor...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sim, eu me lembro desse homem. Mas não me recordo de nenhum detalhe sobre ele. Ele veio aqui e depois simplesmente foi embora. Não posso te ajudar.";
			link.l1 = "Entendo. Desculpe incomodar você.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
