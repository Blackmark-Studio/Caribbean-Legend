// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Já é a terceira vez hoje que você faz essa pergunta...","Você está repetindo as mesmas coisas feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Você sabe onde eu poderia encontrar o Francois Gontier, por acaso?";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Escute, chegou algum alquimista nesta cidade, um médico? Ele é italiano, tem cerca de trinta anos, se chama Gino Gvineili. Ouviu falar dele?";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("Eu não faço a menor ideia. Nunca ouvi esse nome antes.","Você já perguntou sobre isso e eu já te respondi.","Eu já te disse, você já perguntou sobre isso, Gontier.","Escuta, vai embora e para de me incomodar! Você perdeu completamente o juízo?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Então tá, vou continuar procurando.","Hum, acho que sim...","Sim, é isso mesmo, eu pedi isso...","Desculpe, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Não, nunca ouvi falar. Temos herbalistas e médicos, mas ninguém com esse nome.","É a primeira vez que ouço um nome tão estranho. Não, nunca recebemos a visita do homem de quem você fala.","Nem temos alquimistas aqui, de jeito nenhum. Temos médicos, mas nenhum com um nome estranho desses.");
			link.l1 = "Entendi. Que pena. Vou continuar procurando!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
