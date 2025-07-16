// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Скажите, "+GetAddress_FormToNPC(NPChar)+", в вашу колонию в последнее время не заходил галеон под названием 'Санта-Маргарита'? Быть может, в качестве каперского приза?";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Я ищу капитана Ренье. Вы случайно не встречали его?";
                link.l1.go = "UV_DialogCitizen";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Я что, работаю на тайную агентурную сеть для "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ну ладно... тогда пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Я вам что справочная? Не знаю. Ничего не ведаю.";

            link.l1 = "Вот бестолочь! Пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Нет, галеона с таким названием что-то не припомню. Да и вообще крупный корабль у нас нечасто увидишь.","Простите, но я вообще не понимаю, о чём вы говорите. Какой галеон? Понятия не имею.","Нет, сударь, такой корабль у нас в порту не причаливал, во всяком случае - я не помню.");
			link.l1 = LinkRandPhrase("Ясно...","Больше вопросов не имею...","Понятно. Жаль...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
		
		case "UV_DialogCitizen":
			dialog.text = "Никогда о таком не слышал"+NPCharSexPhrase(NPChar,"","а")+". Но, знаете, капитанов обычно за уши из таверны не вытащишь. Думаю, вам стоит начать поиски именно оттуда.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

