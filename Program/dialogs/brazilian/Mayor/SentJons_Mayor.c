// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo, qual é a sua pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados"),"Verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "Vossa Excelência, gostaria de informar que possuo certas informações sobre o desaparecimento do Mercury.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "Informação? Sobre o quê, mesmo?";
			link.l1 = "O brigantim, sua Excelência. Transportando correspondências. Documentos de grande importância e afins. Ouvi falar da investigação e, naturalmente, como um leal amigo da Coroa Britânica, gostaria de ajudar.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "Excelente! O baronete Cortney ficará encantado em recebê-lo! Vou providenciar o encontro imediatamente.";
			link.l1 = "Obrigado, senhor. Estou com pressa e agradeceria se isso pudesse ser resolvido rapidamente.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "Não se preocupe, você terá todo o tempo do mundo. Guardas! Prendam-no!";
			link.l1 = "Obrigado... espere, o quê? Isso é uma piada?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
