// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","Durante todo este dia, essa já é a terceira vez que você faz essa pergunta...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar a minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "Ouvi dizer que os padres vieram de uma colônia francesa com uma delegação, para acertar alguma coisa? Provavelmente para trocar prisioneiros depois daquele massacre sangrento na Martinica?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "Não senhor, essa história foi resolvida há muito tempo, sem nenhum clérigo envolvido. Veja só, você deve estar vivendo debaixo de um coqueiro, já que não ficou sabendo que o Papa Inocêncio X e o Cardeal Mazarin finalmente chegaram a um acordo. A Europa com suas guerras é uma coisa, mas todos os cristãos deveriam se unir para lutar contra a escuridão pagã no fim do mundo. E sim, os come-sapos vieram até nós. Mas não chegaram a acordo nenhum – nossos ilustres hóspedes estão sentados na mansão do governador, sob guarda, tomando café e esquentando cadeira. Já faz quase um mês! O povo fofocou, comentou bastante e acabou se acostumando – veja só, o abade francês faz oração na igreja toda noite. Quase um espetáculo, ahah!";
			link.l1 = "Interessante! Acho que vou dar uma olhada naquele francês, pelo menos é mais divertido do que ficar encarando uma caneca.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
