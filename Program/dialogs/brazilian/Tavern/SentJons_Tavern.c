// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso te ajudar, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","No decorrer deste dia inteiro, esta é a terceira vez que você toca nesse assunto...","Mais perguntas, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "Estou procurando por Raymond Baker, um ex-carrasco. Você sabe se ele está vivo e onde posso encontrá-lo?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Estou procurando o Sr. Jones. Pode me ajudar nessa busca, amigo?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Escute, chegou algum alquimista nesta cidade, um médico? Ele é italiano, tem cerca de trinta anos, se chama Gino Gvineili. Você ouviu algo sobre ele?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "O nosso querido gorducho ficou mais famoso que o Coronel Fox! Ele está vivo, o coitado. Mas não está na cidade agora. Depois que o Raymond soube que gente importante como você estava atrás dele, ele se apressou, vendeu o casebre por uma ninharia e sumiu feito vento.";
			link.l1 = "Sumiu com o vento, pra onde?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Ah, vai saber. Ele foi servir como médico de bordo no primeiro navio que apareceu. Só que esse navio voltou hoje e ninguém viu o Baker desembarcar ainda.";
			link.l1 = "Como posso encontrar o capitão?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Por que você acha que precisa procurá-lo? Aposto que ele já está bêbado como sempre, trancado na cabine dele. O balde furado dele se chama 'Callow Meggy'. Tal capitão, tal nome...";
			link.l1 = "Valeu pela ajuda, amigo!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Sr. Jones? Você está brincando comigo, amigo. Sabe quantos malditos Jones existem nesta ilha? Vai ter que ser mais específico do que isso.";
			link.l1 = "Ele tem uma irmã mais velha, Molly. Dizem que ela é de uma beleza impressionante.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Não. Nada disso me vem à cabeça. Desculpe, camarada...";
			link.l1 = "Certo, se você não sabe, não sabe...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Não, não ouvi falar. E só temos um alquimista na cidade, o farmacêutico John Murdock. Ele tem poções incríveis - curam qualquer enfermidade.";
			link.l1 = "Você acha que ele mesmo prepara essas poções?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Boa pergunta. Eu me faço essa mesma pergunta de vez em quando. O John não tem nada de conhecedor de frascos de remédio, ervas e pós. Ele parece mais um ex-soldado, um mercenário... isso está mais perto da verdade.";
			link.l1 = "Bem, suponho que o homem seja mais do que qualificado...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Talvez seja mesmo. Mas tem uma coisa que eu sei com certeza: alguém mora no segundo andar dele. A janela está sempre coberta. Mesmo quando o John está lá embaixo, dá pra ouvir um tilintar de frascos e garrafas, além do cheiro de ervas fervendo, e à noite a luz nunca se apaga. Por isso eu suspeito que quem mora naquele quarto é quem prepara os remédios do John pra vender.";
			link.l1 = "Hm. Observação interessante. Valeu, camarada!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
