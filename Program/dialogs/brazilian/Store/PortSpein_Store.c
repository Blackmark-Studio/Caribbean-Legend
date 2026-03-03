// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Acabamos de falar sobre isso. Você deve ter esquecido...","Esta é a terceira vez hoje que você vem com alguma pergunta...","Olha, aqui é uma loja. As pessoas vêm para comprar. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez na próxima vez.","Certo, por algum motivo eu me esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Me diga, o nome Juan significa algo para você?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Em abril de 1654, uma fragata atracou no seu porto sob o comando do capitão Miguel Dichoso, e depois disso ele sumiu. Esse nome lhe é familiar? Talvez ele tenha comprado alguma mercadoria com você ou dito algo...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Ah, tenha paciência, capitão! Hoje mesmo já passaram dois Juans pela minha loja, e outro ontem. Quer que eu lembre de cada um?";
			link.l1 = "Tudo bem. Desculpe incomodar...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Oh, capitão, já vi tantas fragatas e galeões indo e vindo nesse tempo, Miguéis e Carloses...";
			link.l1 = "Entendi. Então, você não pode ajudar em nada...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
