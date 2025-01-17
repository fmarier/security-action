v8::Local<v8::Promise> uaf(v8::Isolate* isolate) {
  if (!EnsureConnected()) {
    return v8::Local<v8::Promise>();
  }

  v8::MaybeLocal<v8::Promise::Resolver> resolver =
      v8::Promise::Resolver::New(isolate->GetCurrentContext());
  if (resolver.IsEmpty()) {
    return v8::Local<v8::Promise>();
  }

  auto global_context(
      v8::Global<v8::Context>(isolate, isolate->GetCurrentContext()));
  auto promise_resolver(
      v8::Global<v8::Promise::Resolver>(isolate, resolver.ToLocalChecked()));
	// chromium-bind-uaf
  DistillPageText(
      render_frame(),
      base::BindOnce(&PageContentExtractor::OnDistillResult,
                     weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
	// ok: chromium-bind-uaf
  DistillPageText(
      render_frame(),
      base::BindOnce(&PageContentExtractor::OnDistillResult,
                     base::Unretained(this), std::move(callback)));
}