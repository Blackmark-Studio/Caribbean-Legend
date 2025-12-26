// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já levantou essa questão pela terceira vez hoje...","Olha, se você não tem nada pra me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Bom dia. O capitão François Gontier já se registrou aqui? Ele estava vindo de Porto Bello em uma corveta chamada '"+pchar.questTemp.Slavetrader.ShipName+"'.";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("Não, ele não fez isso. E a corveta '"+pchar.questTemp.Slavetrader.ShipName+"' não foi visto em Port Royal.","Você já perguntou sobre isso e eu já respondi.","Eu já disse que você já perguntou sobre esse tal de Gontier.","Por favor, não me distraia do meu trabalho!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Obrigado. Vou continuar procurando.","Hum, bem...","Sim, eu realmente perguntei ...","Com licença, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
