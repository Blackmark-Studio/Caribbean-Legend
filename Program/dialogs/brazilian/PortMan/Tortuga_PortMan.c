// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já levantou essa questão pela terceira vez hoje...","Olha, se você não tem nada para me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não me interesso pelos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "Bom dia. Estou procurando por Francois Gontier. A corveta dele '"+pchar.questTemp.Slavetrader.ShipName+"' deve ter estado aqui no seu porto.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("Hm... Tenho que te decepcionar. A corveta '"+pchar.questTemp.Slavetrader.ShipName+" nunca esteve aqui, e Francois Gontier também não se registrou aqui.","Você já perguntou sobre isso e eu já respondi.","Eu já disse, você já perguntou sobre esse Gontier.","Por favor, não me distraia do meu trabalho!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Obrigado. Vou continuar procurando.","Hum, bem...","Sim, eu realmente perguntei ...","Com licença, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
