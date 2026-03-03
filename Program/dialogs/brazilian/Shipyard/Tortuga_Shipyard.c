// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas perguntas?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas com tanta curiosidade no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos cuidar disso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Hm, bem...","Pode prosseguir...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "Estou procurando por Gaius Marchais. A última coisa que ouvi sobre ele foi que ele atracou seu galeão, 'Santa Margarita', aqui para você consertar...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "O próprio galeão dele? Ha-ha, essa é boa, capitão. Gaius Marchais só tinha uma chalupa caindo aos pedaços... ele capturou um galeão como prêmio depois que decidiu virar corsário. Sortudo, logo na primeira incursão já conseguiu um troféu desses\nOfereci um bom dinheiro por ele, mas ele recusou, acredita? Em vez disso, vendeu aquela chalupa miserável por uma ninharia e usou o dinheiro pra consertar o galeão! Velas novas, pintura nova e um novo nome, o que normalmente não é um bom sinal\nÉ verdade que o nome era católico demais, mas minha filha também se chama Margarita, então acho que tudo bem... Ele disse que já tinha visto violência demais, que agora queria ser comerciante. E teve a sorte...";
			link.l1 = "Comércio, eu diria, seria tranquilo, mas galeões papistas não costumam ser capturados por escunas. E qual é o novo nome do navio dele agora?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Admirável'... Não me surpreende! Ele estava correndo pelo novo galeão como se estivesse atrás de uma noiva, não conseguia parar de admirá-lo.";
			link.l1 = "Entendi. O Gaius está em Tortuga agora?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Não. Ele partiu com seu novo navio e ainda não voltou para Tortuga. Não sei para onde ele foi, então não posso te ajudar com isso.";
			link.l1 = "Que inconveniente... Eu realmente preciso dele. Devíamos até brindar ao navio 'admirável' dele. De qualquer forma, obrigado pela informação.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ah, sem problema. Passe aqui de novo, capitão. E não se esqueça, sempre tem um lugar para o seu navio aqui se precisar de reparos!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
