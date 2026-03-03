// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "O que deseja, senhor? Oh... espere! Você é o capitão francês que salvou minha filha das mãos imundas dos servos de Levasseur! ";
				link.l1 = "Vejo que Catherine já lhe falou sobre mim...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "O que deseja, senhor?";
				link.l1 = "Bom dia, Coronel. Vim procurá-lo para tratar de um assunto um tanto 'incomum'. Poderia me conceder um momento do seu tempo?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Se não me engano, você é o "+GetSexPhrase("capitão","capitã")+" quem ajudou meus homens a cumprir a missão em Sint Maarten? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", Coronel. Sim, sou eu mesmo.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "O que deseja, senhor?";
			link.l1 = "Nada, Coronel. Vou me retirar.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Então desembucha logo, já que você veio até aqui...";
			link.l1 = "Você recentemente abordou uma escuna comandada por Rollie, o Cap, um pirata holandês, e trouxe o capitão aqui, para St. John's.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Capitão? Ah, não me faça rir! Esse canalha criminoso não tem direito de ser chamado por esse título honrado. Eu capturei um maldito pirata, líder de uma alcateia, que roubou e matou comerciantes e mercadores ingleses. E garanti que ele e seus degenerados tivessem o que mereciam – toda St. John's assistiu ao enforcamento deles no cais!";
			link.l1 = "Acho que agora não vou conseguir interrogar esse canalha... Coronel, talvez o senhor possa me ajudar? O pirata tinha algo com ele que não lhe pertencia – o turíbulo de ouro. Encontrou algo assim com ele?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Não, nós revistamos ele e aquele canalha não tinha nenhum pertence. Além disso, tudo o que ele tinha certamente foi roubado de comerciantes honestos! E quanto à sua preocupação... hmm, não, não encontramos nada. E o que um turíbulo estaria fazendo em um navio pirata? Você realmente acha que havia um padre entre eles?";
			link.l1 = "Não, não tenho. Rollie, o Capitão, comprou isso do agiota em Willemstad, que por sua vez havia comprado de outro pirata. O turíbulo é valioso e caro, e estou tentando devolvê-lo aos seus verdadeiros donos. Imagino que Rollie ficou de olho nele como uma gralha.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Na verdade, o Rollie tinha os porões vazios e só alguns baús com dobrões quando abordamos e capturamos o navio dele. Nada além de tralha. Nenhum objeto de valor, nenhum turíbulo de ouro. Eu lembraria de um item tão estranho para um pirata.\nSuspeito que aquele maldito pirata escondeu suas economias em Dominica. Chegamos a desembarcar lá e vasculhar a área, mas não encontramos nada. Só que não ficamos na ilha nem exploramos seu interior por causa da quantidade de selvagens por lá.";
			link.l1 = "Hm... O pirata pode ter escondido o turíbulo junto com o resto das coisas roubadas em algum lugar de Dominica... Que pena. Você interrogou o pirata antes da execução?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Eu fiz... e ele simplesmente começou a rir na minha cara. Mas eu realmente não ligava para os esconderijos dele. Rollie, o Capitão, foi enforcado e isso é o que mais importa.";
			link.l1 = "Entendo. Obrigado pela sua história e pelo seu tempo, Coronel. Até logo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GuardOT_Fox_DlgExit");
		break;
		
		case "terrapin":
			dialog.text = "Várias vezes, capitão! Sua atitude honrada e corajosa era algo que dificilmente se esperaria de um francês. Devo-lhe minha gratidão, como soldado e como pai. Não há nada mais valioso para mim neste mundo inteiro do que minha filha...";
			link.l1 = "Fico feliz por ter podido ajudar, e espero que, com o tempo, minhas ações mudem seu coração em relação aos franceses.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "A presença de um cavalheiro tão honrado e generoso como você, que arriscou a vida por uma jovem inglesa desconhecida, certamente fará com que meus sentimentos pelos seus compatriotas se tornem muito mais calorosos!";
			link.l1 = "Há pessoas honestas entre os ratos de qualquer nação, coronel...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "E você provou isso! Uma recompensa está esperando por você, capitão. Claro, a vida de uma filha não tem preço, mas Jonathan Fox sempre paga suas dívidas, eu juro! Você é um verdadeiro soldado, então meu presente para você é digno de um soldado. Aqui, veja só.\nIsto é uma bacamarte, um excelente mosquete naval, e pode ser usado com uma só mão. Você pode carregá-lo com dardos especiais que atravessam até a couraça mais resistente. Também dispara chumbo grosso, e sua estrutura robusta permite até carregar pregos como munição. Aqui, pegue, agora é seu.";
			link.l1 = "Um presente excelente para um soldado, muito obrigado, Coronel!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received instructions for creating the harpoon arrows");
			Log_Info("You have received instructions for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Também lhe entrego um pequeno lote de munição e instruções para fabricá-las. Seria uma pena se você não aproveitasse todo o potencial desse poder!";
			link.l1 = "Obrigado, Coronel. Não vou recusar um presente desses, mas quero que saiba que não salvei Catherine por recompensa. Eu simplesmente não poderia deixar que uma moça indefesa sofresse algum mal.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Eu sei disso, capitão. Isso te honra em dobro. Catherine ficou realmente impressionada com você, e não é fácil causar uma boa impressão nela. Mais uma vez, lhe devemos nossa gratidão por tê-la resgatado. Eu te devo essa!";
			link.l1 = "Bem, agradeço pelo presente, Coronel. Envie meus cumprimentos à Catherine e diga que espero que da próxima vez ela escute o pai.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Vou sim, Capitão! Adeus, e boa viagem!";
			link.l1 = "Adeus, Coronel.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Li o relatório. Suas ações são muito valorizadas, por isso você merece uma recompensa. Trinta mil pesos pelos serviços prestados na expedição e armas pelo heroísmo como soldado. Aceite esta espada e esta arcabuz. Agora são todos seus!";
			link.l1 = "Obrigado, senhor.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Sem dúvida, Capitão. Você também recebe o amor e o respeito das colônias britânicas, das autoridades e de mim, pessoalmente. Obrigado por não abandonar meus homens e por ajudá-los em sua missão!";
			link.l1 = "É um prazer, Coronel...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Agora, por favor, me dê licença – tenho outros assuntos a tratar. Que Deus o acompanhe, Capitão "+pchar.lastname+".";
			link.l1 = "Adeus, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
